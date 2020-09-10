#pragma once

#include <concepts>

namespace workflows::core {

	struct null {};

	template <typename T>
	concept is_workflow = requires(T workflow, typename T::input_type input)
	{
		{ T::output_type };
		{ T::input_type };
		{ workflow.start(input) } -> std::convertible_to<typename T::output_type>;
	};
}
