#include "graph.h"
#include <stdexcept>

graph::graph(size_t vertex_count, bool is_oriented) :
    _adjacent(vertex_count),
    _oriented(is_oriented) {}

void graph::add_edge(vertex_t from, vertex_t to)
{
    if(from >= _adjacent.size() || to >= _adjacent.size())
        throw std::runtime_error("Invalid vertex passed");
    
    _adjacent[from].push_back(to);
    if(!_oriented)
        _adjacent[to].push_back(from);
}

void graph::add_vertex()
{
    _adjacent.emplace_back();
}

size_t graph::vertex_count() const
{
    return _adjacent.size();
}

bool graph::is_oriented() const
{
    return _oriented;
}

const std::vector<graph::vertex_t>& graph::adjacent(vertex_t vertex) const
{
    if(vertex >= _adjacent.size())
        throw std::runtime_error("Invalid vertex passed");
    
    return _adjacent[vertex];
}

bool graph::are_adjacent(vertex_t v1, vertex_t v2) const
{
    if(v1 >= _adjacent.size() || v2 >= _adjacent.size())
        throw std::runtime_error("Invalid vertex passed");

    for (const auto& v : _adjacent[v1])
    {
        if(v == v2)
            return true;
    }

    return false;
}