#pragma once

#include "../cores/workflow_independent.hpp"

#include <vector>

namespace workflows::clipping {

	using namespace cores;

	enum class SutherlandHodgmanClippingWorkflowEdgeType : uint32 {
		left, top, right, bottom
	};

	template <typename Polygon>
	struct SutherlandHodgmanClippingWorkflowInput {
		std::vector<Polygon> polygons;

		float left = 0, top = 0, right = 0, bottom = 0;
	};

	template <typename Polygon>
	struct SutherlandHodgmanClippingWorkflowOutput {
		std::vector<Polygon> polygons;
	};

	template <typename Polygon>
	using SHCWInput = SutherlandHodgmanClippingWorkflowInput<Polygon>;

	template <typename Polygon>
	using SHCWOutput = SutherlandHodgmanClippingWorkflowOutput<Polygon>;

	using SHCWEdgeType = SutherlandHodgmanClippingWorkflowEdgeType;

	template <typename Polygon>
	class SutherlandHodgmanClippingWorkflow final : public IndependentWorkflow<SHCWInput<Polygon>, SHCWOutput<Polygon>> {
	public:
		SutherlandHodgmanClippingWorkflow() = default;

		~SutherlandHodgmanClippingWorkflow() = default;

		SHCWOutput<Polygon> start(const SHCWInput<Polygon>& input) const override;
	private:
		Polygon clipping_with_edge(const Polygon& polygon, const SHCWEdgeType& type, float value) const;

		vector2 intersect(const vector2& begin, const vector2& end, const SHCWEdgeType& type, float value) const;

		bool inside(const vector2& vertex, const SHCWEdgeType& type, float value) const;

		vector2 lerp(const vector2& s, const vector2& t, float x) const;
	};

	template <typename Polygon>
	SHCWOutput<Polygon> SutherlandHodgmanClippingWorkflow<Polygon>::start(const SHCWInput<Polygon>& input) const
	{
		SHCWOutput<Polygon> output;

		for (size_t index = 0; index < input.polygons.size(); index++) {
			Polygon polygon = input.polygons[index];
			
			polygon = clipping_with_edge(polygon, SHCWEdgeType::left, input.left);
			polygon = clipping_with_edge(polygon, SHCWEdgeType::top, input.top);
			polygon = clipping_with_edge(polygon, SHCWEdgeType::right, input.right);
			polygon = clipping_with_edge(polygon, SHCWEdgeType::bottom, input.bottom);

			output.polygons.push_back(polygon);
		}

		return output;
	}

	template <typename Polygon>
	Polygon SutherlandHodgmanClippingWorkflow<Polygon>::clipping_with_edge(const Polygon& polygon, 
		const SHCWEdgeType& type, float value) const
	{
		Polygon ret;

		for (size_t index = 0; index < polygon.size(); index++) {
			const auto& this_vertex = polygon[index];
			const auto& next_vertex = polygon[(index + 1) % polygon.size()];

			if (inside(this_vertex, type, value)) {
				ret.push_back(this_vertex);

				if (!inside(next_vertex, type, value))
					ret.push_back(intersect(this_vertex, next_vertex, type, value));
			}
			else {
				if (inside(next_vertex, type, value)) 
					ret.push_back(intersect(this_vertex, next_vertex, type, value));
			}
		}

		return ret;
	}

	template <typename Polygon>
	vector2 SutherlandHodgmanClippingWorkflow<Polygon>::intersect(const vector2& begin, const vector2& end, 
		const SHCWEdgeType& type, float value) const
	{
		if (type == SHCWEdgeType::left || type == SHCWEdgeType::right)
			return vector2(value, lerp(begin, end, (value - begin.x) / (end.x - begin.x)).y);

		if (type == SHCWEdgeType::top || type == SHCWEdgeType::bottom)
			return vector2(lerp(begin, end, (value - begin.y) / (end.y - begin.y)).x, value);

		return vector2(0);
	}

	template <typename Polygon>
	bool SutherlandHodgmanClippingWorkflow<Polygon>::inside(const vector2& vertex, const SHCWEdgeType& type, float value) const
	{
		switch (type) {
		case SHCWEdgeType::left: return vertex.x >= value;
		case SHCWEdgeType::top: return vertex.y >= value;
		case SHCWEdgeType::right: return vertex.x <= value;
		case SHCWEdgeType::bottom: return vertex.y <= value;
		default: return false;
		}
	}

	template <typename Polygon>
	vector2 SutherlandHodgmanClippingWorkflow<Polygon>::lerp(const vector2& s, const vector2& t, float x) const
	{
		return s + (t - s) * x;
	}
}