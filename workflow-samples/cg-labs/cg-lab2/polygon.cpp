#include "polygon.hpp"

size_t workflows::labs::Polygon::size() const noexcept
{
	return vertices.size();
}

void workflows::labs::Polygon::add(const vector2& vertex)
{
	vertices.push_back(vertex);
}

std::vector<workflows::rendering::LineWorkflowDrawCall> workflows::labs::to_lines(const std::vector<Polygon>& polygons)
{
	std::vector<rendering::LineWorkflowDrawCall> draw_calls;

	for (const auto& polygon : polygons) {
		assert(polygon.size() > 2);
		
		auto last = polygon.vertices[0];

		for (size_t index = 1; index < polygon.size(); index++) {
			draw_calls.push_back({
				vector3(last, 0), vector3(polygon.vertices[index], 0),
				polygon.color
			});

			last = polygon.vertices[index];
		}

		draw_calls.push_back({
			vector3(last, 0), vector3(polygon.vertices[0], 0),
			polygon.color
		});
	}

	return draw_calls;
}
