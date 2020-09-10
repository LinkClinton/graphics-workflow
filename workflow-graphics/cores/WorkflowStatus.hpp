#pragma once

#include "Workflow.hpp"

namespace workflows::cores {

	template <typename Input, typename Output, typename Status>
	class StatusWorkflow {
	public:
		StatusWorkflow() = default;

		virtual ~StatusWorkflow() = default;

		using status_type = Status;
		using output_type = Output;
		using input_type = Input;
		
		virtual output_type start(const input_type& input) = 0;
	};
	
}