#pragma once

#include "../../../workflow-graphics/clipping/workflow_clipping_liang_barsky.hpp"
#include "../../../workflow-graphics/rendering/workflow_line.hpp"

#include "../cg-lab0/workflow_lab.hpp"

#include "workflow_generate_line.hpp"
#include "clipping_rectangle.hpp"

namespace workflows::labs {

	class Lab1Workflow final : public LabWorkflow {
	public:
		Lab1Workflow(const LabWorkflowStatus& status);

		~Lab1Workflow() = default;
	protected:
		void update(float delta) override;
		
		void render(float delta) override;
	private:
		void initialize_graphics_components();
		
		directx12::device mDevice;

		directx12::graphics_command_list mCommandList;
		directx12::command_allocator mCommandAllocator;
		directx12::command_queue mCommandQueue;

		directx12::descriptor_heap mRenderTargetViewHeap;
		directx12::descriptor_heap mImGuiDescriptorHeap;

		directx12::swap_chain mSwapChain;
		directx12::fence mFence;

		ClippingRectangle mClippingRectangle;

		std::shared_ptr<GenerateLineWorkflow> mGenerateLineWorkflow;
		std::shared_ptr<clipping::LiangBarskyClippingWorkflow<Line>> mClippingWorkflow;
		std::shared_ptr<rendering::LineWorkflow> mLineWorkflow;

		std::vector<rendering::LineWorkflowDrawCall> mLineDrawCalls;

		std::vector<Line> mLinesClipped;
		std::vector<Line> mLines;

		std::string mSelectedLine;
		int mSelectedIndex = -1;

		size_t mMaxLineID;

		bool mRenderClippedLine = true;
	};
	
}