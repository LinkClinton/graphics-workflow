#pragma once

#include "../../../workflow-graphics/rendering/workflow_line.hpp"
#include "../../../workflow-graphics/cores/workflow.hpp"

#include <vector>

namespace workflows::labs {

	using namespace cores;

	struct Polygon {
		std::vector<vector2> vertices;

		vector4 color = vector4(0, 0, 0, 1);
		
		size_t size() const noexcept;

		void add(const vector2& vertex);
	};

	std::vector<rendering::LineWorkflowDrawCall> to_lines(const std::vector<Polygon>& polygons);
	
}
