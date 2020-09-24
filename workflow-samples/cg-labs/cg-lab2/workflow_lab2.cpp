#include "workflow_lab2.hpp"

#include "../../../references/directx-wrapper/directx12-wrapper/extensions/imgui.hpp"

workflows::labs::Lab2Workflow::Lab2Workflow(const LabWorkflowStatus& status) : LabWorkflow(status)
{
	initialize_graphics_components();
	
	mClippingRectangle.set_rectangle(100, 100, mStatus.width - 200.f, mStatus.height - 100.f);

	mClippingWorkflow = std::make_shared<clipping::SutherlandHodgmanClippingWorkflow<Polygon>>();
	
	mPolygons.push_back({
		{
			vector2(10, 10), vector2(10, 200),
			vector2(200, 200), vector2(200, 10)
		}
	});
}

void workflows::labs::Lab2Workflow::update(float delta)
{
	directx12::extensions::imgui_context::new_frame();
	ImGui::NewFrame();

	mClippedPolygons = mClippingWorkflow->start({
		mPolygons,
		mClippingRectangle.left(),
		mClippingRectangle.top(),
		mClippingRectangle.right(),
		mClippingRectangle.bottom()
	}).polygons;
}

void workflows::labs::Lab2Workflow::render(float delta)
{
	mCommandAllocator->Reset();
	mCommandList->Reset(mCommandAllocator.get(), nullptr);

	const auto frame_index = mSwapChain->GetCurrentBackBufferIndex();
	const auto render_target_view = mRenderTargetViewHeap.cpu_handle(frame_index);

	mSwapChain.buffers()[frame_index].barrier(mCommandList,
		D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
	
	mCommandList.clear_render_target_view(render_target_view, { 1,1,1,1 });
	
	mLineWorkflow->start({
		to_lines(mClippedPolygons), mCommandList,
		mRenderTargetViewHeap, mSwapChain.buffers()[frame_index],
		glm::transpose(glm::ortho(0.f,
		static_cast<float>(mStatus.width),
		static_cast<float>(mStatus.height), 0.f)),
		frame_index
		});
	
	mClippingRectangle.draw_self(vector4(0.5, 0, 0, 1));
	
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

void workflows::labs::Lab2Workflow::initialize_graphics_components()
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
		mDevice.create_render_target_view(
			directx12::resource_view::render_target2d(mSwapChain.format()),
			mRenderTargetViewHeap.cpu_handle(index),
			mSwapChain.buffers()[index]);
	}

	ImGui::StyleColorsLight();
	
	directx12::extensions::imgui_context::initialize(
		mDevice, mImGuiDescriptorHeap,
		mImGuiDescriptorHeap.cpu_handle(), mImGuiDescriptorHeap.gpu_handle(),
		mSwapChain.format(), 2);

	directx12::extensions::imgui_context::set_multi_sample(1);

	rendering::LineWorkflowStatus status = {
		mSwapChain.format(), mDevice
	};
	
	mLineWorkflow = std::make_shared<rendering::LineWorkflow>(status);
}
