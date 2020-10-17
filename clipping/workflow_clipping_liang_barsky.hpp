#pragma once

#include "../cores/workflow_independent.hpp"

#include <vector>

namespace workflows::clipping {

	using namespace cores;

	template <typename Line>
	struct LiangBarskyClippingWorkflowInput {
		std::vector<Line> lines;

		float left = 0, top = 0, right = 0, bottom = 0;
	};

	template <typename Line>
	struct LiangBarskyClippingWorkflowOutput {
		std::vector<Line> lines;
	};

	template <typename Line>
	using LBCWInput = LiangBarskyClippingWorkflowInput<Line>;

	template <typename Line>
	using LBCWOutput = LiangBarskyClippingWorkflowOutput<Line>;

	template <typename Line>
	class LiangBarskyClippingWorkflow final : public IndependentWorkflow<LBCWInput<Line>, LBCWOutput<Line>> {
	public:
		LiangBarskyClippingWorkflow() = default;

		~LiangBarskyClippingWorkflow() = default;

		LBCWOutput<Line> start(const LBCWInput<Line>& input) const override;
	};

	template <typename Line> 
	LBCWOutput<Line> LiangBarskyClippingWorkflow<Line>::start(const LBCWInput<Line>& input) const
	{
		LBCWOutput<Line> output;

		// for each clipping axis, it defined two space indicate the in and out space
		// the order of clipping axes are left, top, right, bottom
		for (const auto& line : input.lines) {

			// for delta value :
			// the delta > 0 means the line is from out space to in space
			// the delta < 0 means the line is from in space to out space
			// the delta = 0 means the line and axis are parallel
			float delta[] = {
				line.end.x - line.begin.x, line.end.y - line.begin.y,
				line.begin.x - line.end.x, line.begin.y - line.end.y
			};

			// distance indicate the distance from begin point to axis
			// the distance >= 0 means the begin point is in in space
			// the distance < 0 means the begin point is in out space
			float distance[] = {
				line.begin.x - input.left, line.begin.y - input.top,
				input.right - line.begin.x, input.bottom - line.begin.y };

			float u_min = 0, u_max = 1;

			for (size_t index = 0; index < 4; index++) {
				if (delta[index] == 0 && distance[index] < 0) {
					u_max = 0; u_min = 1;

					break;
				}

				// line from out space to in space relative to axis[index]
				if (delta[index] > 0)
					u_min = std::max(u_min, 0 - distance[index] / delta[index]);

				// line from in space to out space relative to axis[index]
				if (delta[index] < 0)
					u_max = std::min(u_max, 0 - distance[index] / delta[index]);
			}

			if (u_min > u_max) continue;

			auto new_line = line;

			new_line.begin.x = line.begin.x + delta[0] * u_min;
			new_line.begin.y = line.begin.y + delta[1] * u_min;
			new_line.end.x = line.begin.x + delta[0] * u_max;
			new_line.end.y = line.begin.y + delta[1] * u_max;

			output.lines.push_back(new_line);
		}

		return output;
	}
	
}
