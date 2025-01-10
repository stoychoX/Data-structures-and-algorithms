#include "weighted_graph.h"
#include <stdexcept>

weighted_graph::weighted_graph(size_t vertex_count, bool is_oriented) :
    _adjacent(vertex_count),
    _oriented(is_oriented) {}

void weighted_graph::add_edge(vertex_index_t from, vertex_index_t to, weight_t weight)
{
    if(from >= _adjacent.size() || to >= _adjacent.size())
        throw std::runtime_error("Invalid vertex passed");
    
    _adjacent[from].push_back(std::make_pair(to, weight));
    if(!_oriented)
        _adjacent[to].push_back(std::make_pair(from, weight));
}

void weighted_graph::add_vertex()
{
    _adjacent.emplace_back();
}

size_t weighted_graph::vertex_count() const
{
    return _adjacent.size();
}

bool weighted_graph::is_oriented() const
{
    return _oriented;
}

const std::vector<weighted_graph::vertex_t>& weighted_graph::adjacent(vertex_index_t vertex) const
{
    if(vertex >= _adjacent.size())
        throw std::runtime_error("Invalid vertex passed");
    
    return _adjacent[vertex];
}

bool weighted_graph::are_adjacent(vertex_index_t v1, vertex_index_t v2) const
{
    if(v1 >= _adjacent.size() || v2 >= _adjacent.size())
        throw std::runtime_error("Invalid vertex passed");

    for (const auto& v : _adjacent[v1])
    {
        if(v.first == v2)
            return true;
    }

    return false;
}

weighted_graph::weight_t weighted_graph::get_weight(vertex_index_t from, vertex_index_t to) const
{
    if(from >= _adjacent.size() || to >= _adjacent.size())
        throw std::runtime_error("Invalid vertex passed");

    
    for(const auto& vertex : _adjacent[from])
    {
        if(vertex.first == to)
        {
            return vertex.second;
        }
    }

    // TODO: This is ugly, maybe use another invaid edge error handling machanism?
    throw std::runtime_error("No such edge found!");
}
