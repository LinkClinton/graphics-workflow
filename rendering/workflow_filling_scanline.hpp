#pragma once

#include "./../cores/workflow_independent.hpp"

#include <algorithm>
#include <vector>
#include <list>

namespace workflows::rendering {

	using namespace cores;

	struct ScanlineFillingWorkflowScanline {
		vector2 begin = vector2(0);
		vector2 end = vector2(0);

		ScanlineFillingWorkflowScanline() = default;
	};

	using ScanlineFillingWorkflowPolygon = std::vector<ScanlineFillingWorkflowScanline>;
		
	template <typename Polygon>
	struct ScanlineFillingWorkflowInput {
		std::vector<Polygon> polygons;

		ScanlineFillingWorkflowInput() = default;
	};

	template <typename Polygon>
	struct ScanlineFillingWorkflowOutput {
		std::vector<ScanlineFillingWorkflowPolygon> polygons;

		ScanlineFillingWorkflowOutput() = default;
	};

	template <typename Polygon>
	using SFWOutput = ScanlineFillingWorkflowOutput<Polygon>;

	template <typename Polygon>
	using SFWInput = ScanlineFillingWorkflowInput<Polygon>;

	template <typename Polygon>
	class ScanlineFillingWorkflow final : public IndependentWorkflow<SFWInput<Polygon>, SFWOutput<Polygon>> {
	public:
		ScanlineFillingWorkflow() = default;

		~ScanlineFillingWorkflow() = default;

		SFWOutput<Polygon> start(const SFWInput<Polygon>& input) const override;
	private:
		ScanlineFillingWorkflowPolygon filling_polygon(const Polygon& polygon) const;
	};

	template <typename Polygon>
	SFWOutput<Polygon> ScanlineFillingWorkflow<Polygon>::start(const SFWInput<Polygon>& input) const
	{
		ScanlineFillingWorkflowOutput<Polygon> output;
		
		for (const auto& polygon : input.polygons) 
			output.polygons.push_back(filling_polygon(polygon));

		return output;
	}

	template <typename Polygon>
	ScanlineFillingWorkflowPolygon ScanlineFillingWorkflow<Polygon>::filling_polygon(const Polygon& polygon) const
	{
		ScanlineFillingWorkflowPolygon output;
		
		struct line_node {
			float point_x = 0;
			float delta_x = 0;

			vector2 vertex0; //low  y vertex of edge
			vector2 vertex1; //high y vertex of edge
			vector2 vertex2; //next vertex of high y vertex of edge in polygon
			vector2 vertex3; //pre  vertex of low y vertex of edge in polygon
			
			line_node() = default;
		};
		
		int min_y = std::numeric_limits<int>::max();
		int max_y = std::numeric_limits<int>::min();

		// find min and max of y
		for (size_t index = 0; index < polygon.size(); index++) {
			min_y = std::min(min_y, static_cast<int>(polygon[index].y));
			max_y = std::max(max_y, static_cast<int>(polygon[index].y));
		}

		std::vector<std::vector<line_node>> edge_list(max_y - min_y + 1);

		// build edge list 
		for (int index = 0; index < polygon.size(); index++) {
			auto this_vertex = polygon[index];
			auto next_vertex = polygon[(index + 1) % polygon.size()];
			auto next_next_vertex = polygon[(index + 2) % polygon.size()];
			auto this_this_vertex = polygon[(index - 1 + polygon.size()) % polygon.size()];

			// if y of next vertex > this vertex y, we will swap two vertex groups(this, next) and (this_this, next_next)
			if (next_vertex.y < this_vertex.y) {
				std::swap(this_vertex, next_vertex);
				std::swap(this_this_vertex, next_next_vertex);
			}

			float delta_x = (next_vertex.y - this_vertex.y) != 0 ? (next_vertex.x - this_vertex.x) / (next_vertex.y - this_vertex.y) : 0;
			
			edge_list[static_cast<int>(this_vertex.y) - min_y].push_back(line_node{
				this_vertex.x, delta_x, this_vertex, next_vertex, next_next_vertex, this_this_vertex
				});	
		}

		std::vector<line_node> list;
		
		for (int y = min_y; y <= max_y; y++) {
			list.insert(list.end(), edge_list[y - min_y].begin(), edge_list[y - min_y].end());

			std::sort(list.begin(), list.end(), [](const line_node& lhs, const line_node& rhs)
				{
					return lhs.point_x < rhs.point_x;
				});

			std::vector<float> points;
			
			for (size_t index = 0; index < list.size(); index++) {
				// if the edge.begin.y and edge.end.y are y, we can think we has two intersect points of scanline
				// the two intersect points are two vertex of this edge
				// so we test vertex2.y and vertex3.y(because for the intersect point, the other two vertices' y are equal to y)
				if (static_cast<int>(list[index].vertex1.y) == y && static_cast<int>(list[index].vertex0.y) == y) {
					// because we do not need detect the edge and content of polygon
					// we can fill polygon with scanline cover the edge
					if (list[index].vertex2.y > y) points.push_back(list[index].point_x);
					if (list[index].vertex3.y > y) points.push_back(list[index].point_x);
					
					continue;
				}

				// if the high y vertex of edge is intersect with scanline
				// we think we find a vertex of polygon
				if (static_cast<int>(list[index].vertex1.y) == y) {
					if (list[index].vertex0.y > y) points.push_back(list[index].point_x);
					if (list[index].vertex2.y > y) points.push_back(list[index].point_x);
				}
				// to avoid process the same vertex of polygon
				// we just process the vertex produce by high y vertex of edge
				// so if the vertex0.y(low vertex of edge) == y, we ignore the vertex
				else if (static_cast<int>(list[index].vertex0.y) != y) points.push_back(list[index].point_x);
			}

			// connect points and build scanline to outputs
			for (size_t index = 0; index < points.size(); index += 2) {
				output.push_back({
					vector2(points[index + 0], y),
					vector2(points[index + 1], y)
					});
			}
			
			std::vector<line_node> new_list;

			// remove old edges and update point_x
			for (size_t index = 0; index < list.size(); index++) {
				if (static_cast<int>(list[index].vertex1.y) <= y) continue;

				list[index].point_x = list[index].point_x + list[index].delta_x;
				
				new_list.push_back(list[index]);
			}

			list = new_list;
		}

		return output;
	}
}
