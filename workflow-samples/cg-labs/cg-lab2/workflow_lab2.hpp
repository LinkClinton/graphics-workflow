#pragma once

#include "../../../workflow-graphics/clipping/workflow_clipping_sutherland_hodgman.hpp"
#include "../../../workflow-graphics/rendering/workflow_line.hpp"

#include "../cg-lab0/workflow_lab.hpp"

#include "clipping_rectangle.hpp"
#include "polygon.hpp"

namespace workflows::labs {

	class Lab2Workflow final : public LabWorkflow {
	public:
		Lab2Workflow(const LabWorkflowStatus& status);

		~Lab2Workflow() = default;
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

		std::vector<Polygon> mPolygons;
		std::vector<Polygon> mClippedPolygons;

		std::shared_ptr<clipping::SutherlandHodgmanClippingWorkflow<Polygon>> mClippingWorkflow;
		std::shared_ptr<rendering::LineWorkflow> mLineWorkflow;
	};
	
}
