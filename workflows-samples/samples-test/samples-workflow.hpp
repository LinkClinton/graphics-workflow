#pragma once

#include "../../workflows-core/core-workflow/workflows/status_workflow.hpp"

#include <string>

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

		~samples_workflow() = default;

		null start(const null& input) override;
	private:
		samples_workflow_status mStatus;
	};
	
}
