#pragma once

#include "workflow.hpp"

namespace workflows::core {

	template <typename Input, typename Output, typename Status>
	class status_workflow {
	public:
		status_workflow() = default;

		virtual ~status_workflow() = default;
		
		virtual Output start(const Input& input) = 0;

		using status_type = Status;
		using output_type = Output;
		using input_type = Input;
	};
	
}