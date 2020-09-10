#pragma once

#include "workflow.hpp"

namespace workflows::core {

	template <typename Input, typename Output>
	class independent_workflow {
	public:
		independent_workflow() = default;

		virtual ~independent_workflow() = default;
		
		virtual Output start(const Input& input) const = 0;

		using output_type = Output;
		using input_type = Input;
	};
	
}
