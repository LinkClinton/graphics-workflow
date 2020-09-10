#pragma once

#include "Workflow.hpp"

namespace workflows::cores {

	template <typename Input, typename Output>
	class IndependentWorkflow {
	public:
		IndependentWorkflow() = default;

		virtual ~IndependentWorkflow() = default;

		using output_type = Output;
		using input_type = Input;
		
		virtual output_type start(const input_type& input) const = 0;
	};
	
}
