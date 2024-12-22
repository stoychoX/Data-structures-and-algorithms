#include <iostream>
#include <vector>
#include <list>

using graph = std::vector<std::list<int>>;

enum class color : char
{
    white,
    gray,
    black
};

bool has_cycle_cc(const graph& g, int vertex, std::vector<color>& colors)
{
    const auto& adjacent = g[vertex];
    colors[vertex] = color::gray;

    for(int child : adjacent)
    {
        if(colors[child] == color::gray)
            return true;
        
        if(has_cycle_cc(g, child, colors))
            return true;
    }

    colors[vertex] = color::black;
    return false;
}

bool has_cycle(const graph& g)
{
    std::vector<color> colors(g.size(), color::white);

    for(int vertex = 0; vertex < g.size(); vertex++)
    {
        if(colors[vertex] == color::white && has_cycle_cc(g, vertex, colors))
            return true;
    }
    return false;
}

int main()
{
    graph g = {
        /* 0 */ {1, 2},
        /* 1 */ {3, 2},
        /* 2 */ {},
        /* 3 */ {2, 0}
    }; // cycle: 0 -> 1 -> 3 -> 0

    std::cout << has_cycle(g);
}