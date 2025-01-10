#include "../graph_impl/graph/graph.h"
#include <iostream>

void dfs_visit(const graph& g, graph::vertex_t from, std::vector<bool>& visited)
{
    visited[from] = true;

    const auto& adjacent = g.adjacent(from);

    for(const auto& vertex : adjacent)
    {
        if(!visited[vertex])
        {
            dfs_visit(g, vertex, visited);
        }
    }
}

size_t count_cc(const graph& g)
{
    std::vector<bool> visited(g.vertex_count(), false);
    size_t cnt = 0;

    for (int i = 0; i < g.vertex_count(); i++)
    {
        if(!visited[i])
        {
            ++cnt;
            dfs_visit(g, i, visited);
        }
    }

    return cnt;
}

int main()
{
    graph g(6, false);

	g.add_edge(0, 1);
	g.add_edge(0, 2);
	g.add_edge(2, 3);
	g.add_edge(1, 4);
	g.add_edge(3, 5);
	g.add_edge(4, 5);
	g.add_edge(2, 5);

    g.add_vertex();

    std::cout << count_cc(g);
}