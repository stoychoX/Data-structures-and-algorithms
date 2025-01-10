#pragma once
#include <vector>

class graph
{
public:
    using vertex_t = int;
private:
    std::vector<std::vector<vertex_t>> _adjacent;
    bool _oriented;

public:
    graph(size_t vertex_count, bool is_oriented);

    void add_edge(vertex_t from, vertex_t to);
    void add_vertex();

    size_t vertex_count() const;
    bool is_oriented() const;

    const std::vector<vertex_t>& adjacent(vertex_t vertex) const;
    bool are_adjacent(vertex_t v1, vertex_t v2) const;
};