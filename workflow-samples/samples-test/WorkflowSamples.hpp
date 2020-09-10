#pragma once

#include "../../references/directx-wrapper/directx12-wrapper/descriptors/descriptor_heap.hpp"
#include "../../references/directx-wrapper/directx12-wrapper/swap_chain.hpp"

#include "../../workflow-graphics/cores/WorkflowStatus.hpp"

#include <string>

using namespace wrapper;

namespace workflows::samples {

	using namespace cores;
	
	struct SamplesWorkflowsStatus {
		std::string name = "samples-workflow";

		int width = 0, height = 0;

		void* handle = nullptr;

		bool living = false;
	};
	
	class SamplesWorkflow final : public StatusWorkflow<null, null, SamplesWorkflowsStatus> {
	public:
		explicit SamplesWorkflow(const SamplesWorkflowsStatus& status);

		~SamplesWorkflow();

		null start(const null& input) override;
	private:
		void update(float delta);

		void render(float delta);

		void initialize_imgui_components();
		
		void initialize_graphics_components();
		
		SamplesWorkflowsStatus mStatus;

		directx12::device mDevice;

		directx12::graphics_command_list mCommandList;
		directx12::command_allocator mCommandAllocator;
		directx12::command_queue mCommandQueue;

		directx12::descriptor_heap mRenderTargetViewHeap;
		directx12::descriptor_heap mImGuiDescriptorHeap;
		
		directx12::swap_chain mSwapChain;
		directx12::fence mFence;

		directx12::buffer mCpuFrameBuffer;

		std::vector<byte> mCpuFrameData;
	};
	
}
