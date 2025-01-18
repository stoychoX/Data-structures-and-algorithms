#include "../../Seminar12/src/graph_impl/weighted_graph/weighted_graph.h"
#include <queue>
#include <iostream>
#include <limits.h>

using vertex_t = weighted_graph::vertex_t;
using vertex_index_t = weighted_graph::vertex_index_t;
using weight_t = weighted_graph::weight_t;

struct mst_info
{
    std::vector<vertex_index_t> tree;
    int cost = 0;
};

mst_info prim(const weighted_graph& g, vertex_index_t start = 0)
{
    mst_info result;

    if(g.vertex_count() == 0)
        return result;
    
    std::vector<bool> visited(g.vertex_count(), false);
    result.tree.resize(g.vertex_count(), -1);
    // min_cost[i] = minimum cost found!
    std::vector<weight_t> min_cost(g.vertex_count(), INT_MAX);

    struct vertex_comparator
    {
        bool operator()(const vertex_t& lhs, const vertex_t& rhs) const
        {
            return lhs.second > rhs.second;
        }
    };

    std::priority_queue<vertex_t, std::vector<vertex_t>, vertex_comparator> p;

    // initialize structures:
    p.push({start, 0});
    min_cost[start] = 0;

    size_t found_edges = 0;

    while(found_edges != g.vertex_count())
    {
        vertex_index_t current_vertex = p.top().first;
        weight_t current_weight       = p.top().second;

        p.pop();

        if(visited[current_vertex])
            continue;
        
        visited[current_vertex] = true;
        result.cost += current_weight;
        ++found_edges;

        const auto& adjacent = g.adjacent(current_vertex);

        for(const vertex_t& vertex : adjacent)
        {
            vertex_index_t found_index = vertex.first;
            weight_t found_weight      = vertex.second;

            if(!visited[found_index] && found_weight < min_cost[found_index])
            {
                result.tree[found_index] = current_vertex;
                p.push({found_index, found_weight});
                min_cost[found_index] = found_weight;
            }
        }
    }

    return result;
}

int main()
{
    // Create a weighted graph with 7 vertices, undirected
    weighted_graph g(7, false);

    // Add edges with weights
    g.add_edge(0, 1, 4);
    g.add_edge(0, 2, 3);
    g.add_edge(1, 2, 1);
    g.add_edge(1, 3, 2);
    g.add_edge(2, 4, 5);
    g.add_edge(3, 4, 6);
    g.add_edge(3, 5, 7);
    g.add_edge(4, 6, 8);
    g.add_edge(5, 6, 4);

    // g.add_edge(0, 1, 10);
    // g.add_edge(0, 2, 5);
    // g.add_edge(1, 2, 1);
    // g.add_edge(1, 3, 2);
    // g.add_edge(2, 3, 3);

    // Run Prim's algorithm
    auto result = prim(g);

    // Print the total cost of the MST
    std::cout << "Total cost of MST: " << result.cost << '\n';

    // Print the tree structure
    std::cout << "Tree structure (parent array): ";
    for (const auto x : result.tree)
    {
        std::cout << x << " ";
    }

    std::cout << '\n';

    return 0;
}