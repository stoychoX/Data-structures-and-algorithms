#include "../graph_impl/graph/graph.h"
#include <queue>
#include <unordered_map>
#include <iostream>
#include <algorithm>

using vertex_t = graph::vertex_t;

std::vector<vertex_t> shortest_path(const graph& g, vertex_t from, vertex_t to)
{
    std::queue<vertex_t> q;
    q.push(from);

    std::unordered_map<vertex_t, vertex_t> parent;
    bool found_path = false;

    while(!q.empty() && !found_path)
    {
        vertex_t current = q.front();
        q.pop();

        if(current == to)
        {
            found_path = true;
            continue;
        }

        const auto& adjacent = g.adjacent(current);

        for(const auto& vertex : adjacent)
        {
            if(parent.find(vertex) == parent.end())
            {
                // This means the vertex is yet to be visited...
                q.push(vertex);
                parent[vertex] = current;
            }
        }
    }

    if(!found_path)
        return {};

    std::vector<vertex_t> path;
    vertex_t it = to;

    while (true)
    {
        auto child_it = parent.find(it);
        
        if(child_it == parent.end())
            break;
        
        path.push_back(it);
        it = child_it->second;
    }

    path.push_back(from);
    std::reverse(path.begin(), path.end());

    return path;
}

int main()
{
    graph g(6, false);

    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 2);
    g.add_edge(1, 3);
    g.add_edge(2, 4);
    g.add_edge(3, 4);
    g.add_edge(4, 5);

    auto path = shortest_path(g, 0, 5);

    for(auto vertex : path)
    {
        std::cout << vertex << " ";
    }
}