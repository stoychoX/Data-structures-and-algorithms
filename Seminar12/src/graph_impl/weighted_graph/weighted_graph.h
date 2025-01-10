/*
    A simplistic representation of weighted graph represented by adjacency list.
*/

#pragma once
#include <vector>

class weighted_graph
{
public:
    using weight_t = int;                                       // Type used to represent weight.
    using vertex_index_t = int;                                 // Type used to represent how we index a vertex.
    using vertex_t = std::pair<vertex_index_t, weight_t>;       // Type used to represent a vertex.

private:
    std::vector<std::vector<vertex_t>> _adjacent;
    bool _oriented;

public:
    weighted_graph(size_t vertex_count, bool is_oriented);

    void add_edge(vertex_index_t from, vertex_index_t to, weight_t weight);
    void add_vertex();

    size_t vertex_count() const;
    bool is_oriented() const;

    const std::vector<vertex_t>& adjacent(vertex_index_t vertex) const;
    bool are_adjacent(vertex_index_t v1, vertex_index_t v2) const;

    weight_t get_weight(vertex_index_t from, vertex_index_t to) const;
};