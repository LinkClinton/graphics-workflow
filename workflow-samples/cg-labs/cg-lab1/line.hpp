#pragma once

#include "../../../workflow-graphics/rendering/workflow_line.hpp"

#include <string>

namespace workflows::labs {

	using namespace cores;
	
	struct Line {
		std::string name = "";
		
		vector2 begin = vector2(0);
		vector2 end = vector2(0);
		vector4 color = vector4(0, 0, 0, 1);
	};

	rendering::LineWorkflowDrawCall to_draw_call(const Line& line);
	
}
