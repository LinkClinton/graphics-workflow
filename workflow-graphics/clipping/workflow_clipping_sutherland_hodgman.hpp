#pragma once

#include "../cores/workflow_independent.hpp"

#include <vector>

namespace workflows::clipping {

	using namespace cores;

	template <typename T>
	concept is_polygon = requires(T polygon, decltype(polygon.vertices[0]) vertex)
	{
		{ polygon.vertices[0].x } -> std::convertible_to<float>;
		{ polygon.vertices[0].y } -> std::convertible_to<float>;
		{ polygon.size() } -> std::convertible_to<size_t>;
		{ polygon.add(vertex) };
	};

	enum class SutherlandHodgmanClippingWorkflowEdgeType : uint32 {
		left, top, right, bottom
	};

	template <typename Polygon> requires is_polygon<Polygon>
	struct SutherlandHodgmanClippingWorkflowInput {
		std::vector<Polygon> polygons;

		float left = 0, top = 0, right = 0, bottom = 0;
	};

	template <typename Polygon> requires is_polygon<Polygon>
	struct SutherlandHodgmanClippingWorkflowOutput {
		std::vector<Polygon> polygons;
	};

	template <typename Polygon> requires is_polygon<Polygon>
	using SHCWInput = SutherlandHodgmanClippingWorkflowInput<Polygon>;

	template <typename Polygon> requires is_polygon<Polygon>
	using SHCWOutput = SutherlandHodgmanClippingWorkflowOutput<Polygon>;

	using SHCWEdgeType = SutherlandHodgmanClippingWorkflowEdgeType;
	
	template <typename Polygon> requires is_polygon<Polygon>
	class SutherlandHodgmanClippingWorkflow final : public IndependentWorkflow<SHCWInput<Polygon>, SHCWOutput<Polygon>> {
	public:
		SutherlandHodgmanClippingWorkflow() = default;

		~SutherlandHodgmanClippingWorkflow() = default;

		SHCWOutput<Polygon> start(const SHCWInput<Polygon>& input) const override;
	private:
		Polygon clipping_with_edge(const Polygon& polygon, const SHCWEdgeType& type, float value);

		vector2 intersect(const vector2& begin, const vector2& end, const SHCWEdgeType& type, float value);
		
		bool inside(const vector2& vertex, const SHCWEdgeType& type, float value);

		vector2 lerp(const vector2& s, const vector2& t, float x);
	};

	template <typename Polygon> requires is_polygon<Polygon>
	SHCWOutput<Polygon> SutherlandHodgmanClippingWorkflow<Polygon>::start(const SHCWInput<Polygon>& input) const
	{
		return {};
	}

	template <typename Polygon> requires is_polygon<Polygon>
	Polygon SutherlandHodgmanClippingWorkflow<Polygon>::clipping_with_edge(const Polygon& polygon, const SHCWEdgeType& type, float value)
	{
		
	}

	template <typename Polygon> requires is_polygon<Polygon>
	vector2 SutherlandHodgmanClippingWorkflow<Polygon>::intersect(const vector2& begin, const vector2& end, const SHCWEdgeType& type, float value)
	{
		if (type == SHCWEdgeType::left || type == SHCWEdgeType::right)
			return vector2(value, lerp(begin, end, (value - begin.x) / (end.x - begin.x)).y);

		if (type == SHCWEdgeType::top || type == SHCWEdgeType::bottom)
			return vector2(lerp(begin, end, (value - begin.y) / (end.y - begin.y)).x, value);

		return vector2(0);
	}

	template <typename Polygon> requires is_polygon<Polygon>
	bool SutherlandHodgmanClippingWorkflow<Polygon>::inside(const vector2& vertex, const SHCWEdgeType& type, float value)
	{
		switch (type) {
		case SHCWEdgeType::left: return vertex.x >= value;
		case SHCWEdgeType::top: return vertex.y >= value;
		case SHCWEdgeType::right: return vertex.x <= value;
		case SHCWEdgeType::bottom: return vertex.y <= value;
		default: return false;
		}
	}

	template <typename Polygon> requires is_polygon<Polygon>
	vector2 SutherlandHodgmanClippingWorkflow<Polygon>::lerp(const vector2& s, const vector2& t, float x)
	{
		return s + (t - s) * x;
	}
}
