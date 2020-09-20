#include "workflow_lab1.hpp"

#include "../../../references/directx-wrapper/directx12-wrapper/extensions/imgui.hpp"

workflows::labs::Lab1Workflow::Lab1Workflow(const LabWorkflowStatus& status) : LabWorkflow(status)
{
	initialize_graphics_components();

	mLines.push_back({ "line0", vector2(100, 100), vector2(200, 200) });
	mLines.push_back({ "line1", vector2(100, 200), vector2(200, 100) });

	mMaxLineID = mLines.size();
}

void workflows::labs::Lab1Workflow::update(float delta)
{
	directx12::extensions::imgui_context::new_frame();
	ImGui::NewFrame();

	ImGui::Begin("Clip Helper");
	
	ImGui::BeginChild("Lines", ImVec2(0, 100), true);

	for (size_t index = 0; index < mLines.size(); index++) {
		const auto status = mSelectedLine == mLines[index].name;

		if (ImGui::Selectable(mLines[index].name.c_str(), status)) {
			// if the old selected line is existed, we will reset the color of it
			if (mSelectedIndex != -1) mLines[mSelectedIndex].color = vector4(0, 0, 0, 1);

			mSelectedIndex = static_cast<int>(index);
			mSelectedLine = mLines[index].name;

			mLines[index].color = vector4(1, 0, 0, 1);
		}
	}

	const auto button_width = ImGui::GetWindowWidth();
	
	ImGui::EndChild();

	auto position_begin = mSelectedIndex != -1 ? mLines[mSelectedIndex].begin : vector2(-1);
	auto position_end = mSelectedIndex != -1 ? mLines[mSelectedIndex].end : vector2(-1);

	ImGui::InputFloat2("begin", &position_begin.x);
	ImGui::InputFloat2("end", &position_end.x);
	
	if (mSelectedIndex != -1) mLines[mSelectedIndex].begin = position_begin, mLines[mSelectedIndex].end = position_end;

	if (ImGui::Button("delete", ImVec2(button_width, 0)) && mSelectedIndex != -1) {
		mLines.erase(mLines.begin() + mSelectedIndex);

		// when we remove a line from lines array, we need reset the selected line to the first line
		// if mLines is not empty
		if (!mLines.empty()) mSelectedIndex = 0, mSelectedLine = mLines[mSelectedIndex].name;
		else mSelectedIndex = -1;
	}

	if (ImGui::Button("add", ImVec2(button_width, 0)))
		mLines.push_back({ "line" + std::to_string(mMaxLineID++), position_begin, position_end });
	
	ImGui::Separator();

	ImGui::End();

	mLineDrawCalls.resize(mLines.size());
	
	for (size_t index = 0; index < mLines.size(); index++) 
		mLineDrawCalls[index] = to_draw_call(mLines[index]);
}

void workflows::labs::Lab1Workflow::render(float delta)
{
	mCommandAllocator->Reset();
	mCommandList->Reset(mCommandAllocator.get(), nullptr);

	const auto frame_index = mSwapChain->GetCurrentBackBufferIndex();
	const auto render_target_view = mRenderTargetViewHeap.cpu_handle(frame_index);

	mSwapChain.buffers()[frame_index].barrier(mCommandList,
		D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
	
	mCommandList.clear_render_target_view(render_target_view, { 1,1,1,1 });
	
	mLineWorkflow->start({
		mLineDrawCalls, mCommandList,
		mRenderTargetViewHeap, mSwapChain.buffers()[frame_index],
		glm::transpose(glm::ortho(0.f,
		static_cast<float>(mStatus.width),
		static_cast<float>(mStatus.height), 0.f)),
		frame_index
		});
	
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

void workflows::labs::Lab1Workflow::initialize_graphics_components()
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

	mLineWorkflow = std::make_shared<rendering::LineWorkflow>(
		rendering::LineWorkflowStatus{
			mSwapChain.format(), mDevice
		});
}
