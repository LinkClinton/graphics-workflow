#pragma once

#include "../../../references/directx-wrapper/directx12-wrapper/descriptors/descriptor_heap.hpp"
#include "../../../references/directx-wrapper/directx12-wrapper/swap_chain.hpp"

#include "../../../workflow-graphics/rendering/workflow_line.hpp"
#include "../../../workflow-graphics/cores/workflow_status.hpp"

#include <string>

using namespace wrapper;

namespace workflows::labs {

	using namespace cores;

	struct LabWorkflowStatus {
		std::string name = "lab-workflow";

		int width = 0, height = 0;

		void* handle = nullptr;

		bool living = false;
	};

	class LabWorkflow : public StatusWorkflow<null, null, LabWorkflowStatus> {
	public:
		explicit LabWorkflow(const LabWorkflowStatus& status);

		~LabWorkflow();

		output_type start(const input_type& input) override;
	protected:
		virtual void update(float delta) = 0;

		virtual void render(float delta) = 0;

		LabWorkflowStatus mStatus;
	};
	
}
