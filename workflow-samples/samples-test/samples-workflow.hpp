#pragma once

#include "../../references/directx-wrapper/directx12-wrapper/descriptors/descriptor_heap.hpp"
#include "../../references/directx-wrapper/directx12-wrapper/swap_chain.hpp"
#include "../../workflow-core/workflows/status_workflow.hpp"

#include <string>

using namespace wrapper;

namespace workflows::core {

	struct samples_workflow_status {
		std::string name = "samples-workflow";

		int width = 0, height = 0;

		void* handle = nullptr;

		bool living = false;
	};
	
	class samples_workflow final : public status_workflow<null, null, samples_workflow_status> {
	public:
		explicit samples_workflow(const samples_workflow_status& status);

		~samples_workflow();

		null start(const null& input) override;
	private:
		void update(float delta);

		void render(float delta);

		void initialize_imgui_components();
		
		void initialize_graphics_components();
		
		samples_workflow_status mStatus;

		directx12::device mDevice;

		directx12::graphics_command_list mCommandList;
		directx12::command_allocator mCommandAllocator;
		directx12::command_queue mCommandQueue;

		directx12::descriptor_heap mRenderTargetViewHeap;
		directx12::descriptor_heap mImGuiDescriptorHeap;
		
		directx12::swap_chain mSwapChain;
		directx12::fence mFence;
	};
	
}
