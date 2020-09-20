#pragma once

#include "../../../workflow-graphics/cores/workflow_independent.hpp"

#include "line.hpp"

#include <random>

namespace workflows::labs {

	using namespace cores;
	
	struct GenerateLineWorkflowInput {
		size_t count_of_lines = 0;
		vector4 color = vector4(0, 0, 0, 1);

		vector2 min_point = vector2(0);
		vector2 max_point = vector2(1);
	};

	struct GenerateLineWorkflowOutput {
		std::vector<Line> lines;
	};


	struct GenerateLineWorkflowStatus {
		std::default_random_engine random;

		uint32 seed = 0;
	};

	using GLWInput = GenerateLineWorkflowInput;
	using GLWOutput = GenerateLineWorkflowOutput;
	using GLWStatus = GenerateLineWorkflowStatus;
	
	class GenerateLineWorkflow final : public StatusWorkflow<GLWInput, GLWOutput, GLWStatus> {
	public:
		explicit GenerateLineWorkflow(uint32 seed);

		~GenerateLineWorkflow() = default;

		output_type start(const input_type& input) override;
	private:
		GenerateLineWorkflowStatus mStatus;
	};

	inline GenerateLineWorkflow::GenerateLineWorkflow(uint32 seed)
	{
		mStatus.seed = seed;
		mStatus.random = std::default_random_engine(mStatus.seed);
	}

	inline StatusWorkflow<GenerateLineWorkflowInput, GenerateLineWorkflowOutput, GenerateLineWorkflowStatus>::output_type
		GenerateLineWorkflow::start(const input_type& input)
	{
		GLWOutput output;

		const std::uniform_real_distribution<float> x_distribution(input.min_point.x, input.max_point.x);
		const std::uniform_real_distribution<float> y_distribution(input.min_point.y, input.max_point.y);
		
		for (size_t index = 0; index < input.count_of_lines; index++) {
			Line line = {
				"line" + std::to_string(index),
				vector2(x_distribution(mStatus.random), y_distribution(mStatus.random)),
				vector2(x_distribution(mStatus.random), y_distribution(mStatus.random)),
				input.color
			};

			output.lines.push_back(line);
		}

		return output;
	}

}
