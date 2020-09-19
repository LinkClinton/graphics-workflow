#pragma once

#include "../cg-lab0/workflow_lab.hpp"

namespace workflows::labs {

	class Lab1Workflow final : public LabWorkflow {
	public:
		Lab1Workflow(const LabWorkflowStatus& status);

		~Lab1Workflow() = default;
	protected:
		void update(float delta) override;
		
		void render(float delta) override;
	private:
	};
	
}
