#include "line.hpp"

workflows::rendering::LineWorkflowDrawCall workflows::labs::to_draw_call(const Line& line)
{
	return {
		vector3(line.begin, 0),
		vector3(line.end, 0),
		line.color
	};
}
