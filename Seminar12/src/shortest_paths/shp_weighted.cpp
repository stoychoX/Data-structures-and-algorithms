#include "../graph_impl/weighted_graph/weighted_graph.h"
#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <unordered_map>

using vertex_t       = weighted_graph::vertex_t;
using vertex_index_t = weighted_graph::vertex_index_t;
using weight_t       = weighted_graph::weight_t;

// A structure representind information which we
// obtained using dijkstra's algorithm
struct shp_info
{
	std::vector<vertex_index_t> path;
	size_t cost = 0;
};

bool relax(std::vector<int>& distance, 
           const weighted_graph& g,
           vertex_index_t reached,
           vertex_index_t current_vertex)
{
	if (distance[reached] > distance[current_vertex] + g.get_weight(current_vertex, reached))
	{
		distance[reached] = distance[current_vertex] + g.get_weight(current_vertex, reached);
		return true;
	}
	return false;
}

shp_info dijkstra_shortest_path(const weighted_graph& g, vertex_index_t from, vertex_index_t to)
{
	std::vector<int> distances(g.vertex_count(), INT_MAX);
	std::vector<vertex_index_t> parent(g.vertex_count(), -1);

	struct vertex_comparator
	{
		bool operator()(const vertex_t& lhs, const vertex_t& rhs) const
		{
			return lhs.second > rhs.second;
		}
	};

	std::priority_queue<vertex_t, std::vector<vertex_t>, vertex_comparator> q;

	q.push({from, 0});
	distances[from] = 0;
	bool found_path = false;

	while(!q.empty() && !found_path)
	{
		auto current_vertex = q.top();
		q.pop();

		if (current_vertex.first == to)
		{
			found_path = true;
			continue;
		}

		const auto& adjacent = g.adjacent(current_vertex.first);

		for(const auto& vertex : adjacent)
		{
			if(relax(distances, g, vertex.first, current_vertex.first))
			{
				q.push({vertex.first, distances[vertex.first]});
				parent[vertex.first] = current_vertex.first;
			}
		}
	}

	shp_info result;

	if(!found_path)
		return result;

	vertex_index_t it = to;
	while (true)
	{
		vertex_index_t it_parent = parent[it];
		result.path.push_back(it);
		it = it_parent;

		if(it_parent == -1)
		{
			break;
		}
	}

	result.cost = distances[to];
	std::reverse(result.path.begin(), result.path.end());

	return result;
}

int main()
{
	weighted_graph g(6, false);
	g.add_edge(0, 1, 2);
	g.add_edge(0, 2, 1);
	g.add_edge(2, 3, 6);
	g.add_edge(1, 4, 3);
	g.add_edge(3, 5, 1);
	g.add_edge(4, 5, 2);
	g.add_edge(2, 5, 4);

	auto result = dijkstra_shortest_path(g, 0, 5);

	if (result.path.empty())
	{
		std::cout << "No path found from 0 to 5.\n";
	}
	else
	{
		std::cout << "Shortest path cost: " << result.cost << "\n";
		std::cout << "Path: ";
		for (int vertex : result.path)
		{
			std::cout << vertex << " ";
		}
		std::cout << "\n";
	}

	return 0;
}