#include "../../Seminar12/src/graph_impl/weighted_graph/weighted_graph.h"
#include "../../Seminar12/src/graph_impl/graph/graph.h"
#include <iostream>
#include <algorithm>

using vertex_t = weighted_graph::vertex_t;
using vertex_index_t = weighted_graph::vertex_index_t;
using weight_t = weighted_graph::weight_t;
using union_find_t = std::vector<vertex_index_t>;

vertex_index_t find(union_find_t& uf, vertex_index_t v)
{
    if(uf[v] != v)
        uf[v] = find(uf, uf[v]);
    
    return uf[v];
}

void my_union(union_find_t& uf, vertex_index_t parent, vertex_index_t child)
{
    uf[find(uf, child)] = uf[find(uf, parent)];
}

struct mst_info
{
    weighted_graph tree;
    int cost = 0;

    mst_info(const weighted_graph& g) :
        tree(g.vertex_count(), g.is_oriented()) {}
};

mst_info kruskal(const weighted_graph& g)
{
    mst_info result(g);

    union_find_t uf(g.vertex_count());
    
    for (size_t i = 0; i < g.vertex_count(); i++)
        uf[i] = i;

    // weight, from, to
    std::vector<std::tuple<weight_t, vertex_index_t, vertex_index_t>> edges;

    for (size_t i = 0; i < g.vertex_count(); i++)
    {
        const auto& adjacent = g.adjacent(i);

        for(const auto& vertex : adjacent)
        {
            if(i > vertex.first)
                edges.emplace_back(vertex.second, i, vertex.first);
        }
    }

    std::sort(edges.begin(), edges.end());

    size_t added_edges = 0;

    for(const auto& edge : edges)
    {
        weight_t current_weight = std::get<0>(edge);
        vertex_index_t current_from = std::get<1>(edge);
        vertex_index_t current_to = std::get<2>(edge);

        if(find(uf, current_from) != find(uf, current_to))
        {
            my_union(uf, current_from, current_to);
            result.cost += current_weight;
            result.tree.add_edge(current_from, current_to, current_weight);
            ++added_edges;
        }

        if(added_edges == g.vertex_count() - 1)
            break;
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

    auto result = kruskal(g);

    std::cout << "Total cost of MST: " << result.cost << '\n';

    std::cout << "Tree structure (graph representation): " << std::endl;
    
    for(size_t current = 0; current < result.tree.vertex_count(); current++)
    {
        const auto& adj = result.tree.adjacent(current);
        for(const auto& vertex : adj)
        {
            if(current < vertex.first)
                std::cout << "Tree edge from " << current << " to " << vertex.first <<
                    " with weight " << vertex.second << std::endl;
        }
    }

    std::cout << '\n';

    return 0;
}