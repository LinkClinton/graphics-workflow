#include "workflow_samples.hpp"

#include "../../references/directx-wrapper/directx12-wrapper/extensions/imgui.hpp"

#include "../../workflow-graphics/workflow_copy.hpp"

#include "imgui_impl_win32.hpp"

#include <Windows.h>
#include <chrono>


using time_point = std::chrono::high_resolution_clock;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT DefaultWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
		return true;

	switch (message)
	{
	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}
	default:
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

workflows::samples::SamplesWorkflow::SamplesWorkflow(const SamplesWorkflowsStatus& status) :
	mStatus(status)
{
	const auto hInstance = GetModuleHandle(nullptr);
	const auto class_name = mStatus.name;
	
	WNDCLASS appInfo;

	appInfo.style = CS_DBLCLKS;
	appInfo.lpfnWndProc = DefaultWindowProc;
	appInfo.cbClsExtra = 0;
	appInfo.cbWndExtra = 0;
	appInfo.hInstance = hInstance;
	appInfo.hIcon = static_cast<HICON>(LoadImage(nullptr, "", IMAGE_ICON, 0, 0, LR_LOADFROMFILE));
	appInfo.hCursor = LoadCursor(nullptr, IDC_ARROW);
	appInfo.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	appInfo.lpszMenuName = nullptr;
	appInfo.lpszClassName = &class_name[0];

	RegisterClass(&appInfo);

	RECT rect;

	rect.top = 0;
	rect.left = 0;
	rect.right = static_cast<UINT>(mStatus.width);
	rect.bottom = static_cast<UINT>(mStatus.height);

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	mStatus.handle = CreateWindow(&class_name[0], &class_name[0], WS_OVERLAPPEDWINDOW ^
		WS_SIZEBOX ^ WS_MAXIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT,
		rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, hInstance, nullptr);

	mStatus.living = true;

	ShowWindow(static_cast<HWND>(mStatus.handle), SW_SHOW);

	initialize_imgui_components();
	initialize_graphics_components();
}

workflows::samples::SamplesWorkflow::~SamplesWorkflow()
{
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

workflows::cores::null workflows::samples::SamplesWorkflow::start(const null& input)
{
	auto current = time_point::now();

	while (mStatus.living == true) {
		MSG message;

		message.hwnd = static_cast<HWND>(mStatus.handle);

		while (PeekMessage(&message, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessage(&message);

			if (message.message == WM_QUIT) mStatus.living = false;
		}

		if (mStatus.living == false) break;

		auto duration = std::chrono::duration_cast<
			std::chrono::duration<float>>(time_point::now() - current);

		ImGui_ImplWin32_NewFrame();
		
		update(duration.count());
		render(duration.count());
		
		current = time_point::now();
	}
	
	return null();
}

void workflows::samples::SamplesWorkflow::update(float delta)
{
	directx12::extensions::imgui_context::new_frame();
	ImGui::NewFrame();
}

void workflows::samples::SamplesWorkflow::render(float delta)
{
	mCommandAllocator->Reset();
	mCommandList->Reset(mCommandAllocator.get(), nullptr);

	const auto frame_index = mSwapChain->GetCurrentBackBufferIndex();
	const auto render_target_view = mRenderTargetViewHeap.cpu_handle(frame_index);
	
	mSwapChain.buffers()[frame_index].barrier(mCommandList,
		D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_COPY_DEST);
	
	const CopyWorkflow<CpuMemory, GpuTexture2D> copy_workflow;

	copy_workflow.start({
		mCommandList, mSwapChain.buffers()[frame_index],
		mCpuFrameBuffer, mCpuFrameData.size(), mCpuFrameData.data()
	});

	mSwapChain.buffers()[frame_index].barrier(mCommandList,
		D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_RENDER_TARGET);
	
	mCommandList.set_render_targets({ render_target_view });
	
	mCommandList.set_descriptor_heaps({ mImGuiDescriptorHeap.get() });
	
	ImGui::Render();
	directx12::extensions::imgui_context::render(mCommandList, ImGui::GetDrawData());

	mSwapChain.buffers()[frame_index].barrier(mCommandList,
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
	
	mCommandList->Close();
	
	mCommandQueue.execute({ mCommandList });

	mSwapChain.present(true);

	mCommandQueue.wait(mFence);
}

void workflows::samples::SamplesWorkflow::initialize_imgui_components()
{
	ImGui::CreateContext();
	ImGui_ImplWin32_Init(mStatus.handle);
}

void workflows::samples::SamplesWorkflow::initialize_graphics_components()
{
	mDevice = directx12::device::create(D3D_FEATURE_LEVEL_11_0);

	mCommandAllocator = directx12::command_allocator::create(mDevice);
	mCommandQueue = directx12::command_queue::create(mDevice);
	mCommandList = directx12::graphics_command_list::create(mDevice, mCommandAllocator);

	mSwapChain = directx12::swap_chain::create(mCommandQueue, mStatus.width,
		mStatus.height, static_cast<HWND>(mStatus.handle));

	mFence = directx12::fence::create(mDevice, 0);

	mRenderTargetViewHeap = directx12::descriptor_heap::create(mDevice, D3D12_DESCRIPTOR_HEAP_TYPE_RTV, 2);
	mImGuiDescriptorHeap = directx12::descriptor_heap::create(mDevice, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, 1);

	for (size_t index = 0; index < mSwapChain.buffers().size(); index++) {
		D3D12_RENDER_TARGET_VIEW_DESC desc;

		desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
		desc.Format = mSwapChain.format();
		desc.Texture2D.MipSlice = 0;
		desc.Texture2D.PlaneSlice = 0;

		mDevice->CreateRenderTargetView(mSwapChain.buffers()[index].get(), &desc, mRenderTargetViewHeap.cpu_handle(index));
	}
	
	directx12::extensions::imgui_context::initialize(
		mDevice, mImGuiDescriptorHeap,
		mImGuiDescriptorHeap.cpu_handle(), mImGuiDescriptorHeap.gpu_handle(),
		mSwapChain.format(), 2);

	directx12::extensions::imgui_context::set_multi_sample(1);

	mCpuFrameBuffer = directx12::buffer::create(mDevice, directx12::resource_info::upload(),
		mSwapChain.buffers()[0].alignment() * mSwapChain.buffers()[0].height());

	mCpuFrameData = std::vector<byte>(mStatus.width * mStatus.height * directx12::size_of(mSwapChain.format()));
}