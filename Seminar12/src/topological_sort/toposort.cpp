#include "../graph_impl/graph/graph.h"
#include <algorithm>

using vertex_t = graph::vertex_t;

void tsort_visit(const graph& g,
                 vertex_t vertex,
                 std::vector<bool>& visited,
                 std::vector<vertex_t>& result)
{
    visited[vertex] = true;

    const auto& adjacent = g.adjacent(vertex);

    for (const auto& v : adjacent)
    {
        if(!visited[v])
        {
            tsort_visit(g, v, visited, result);
        }
    }

    result.push_back(vertex);
}

std::vector<vertex_t> topological_sort(const graph& g)
{
    std::vector<bool> visited(g.vertex_count(), false);
    std::vector<vertex_t> result(g.vertex_count());

    for (int i = 0; i < g.vertex_count(); i++)
    {
        if(!visited[i])
            tsort_visit(g, i, visited, result);
    }
    
    std::reverse(result.begin(), result.end());

    return result;
}

void tsort_visit_dummy(const graph& g,
                 vertex_t vertex,
                 std::vector<int>& finalized,
                 std::vector<bool>& visited,
                 int& time)
{
    visited[vertex] = true;

    const auto& adjacent = g.adjacent(vertex);

    for (const auto& v : adjacent)
    {
        if(!visited[v])
        {
            tsort_visit_dummy(g, v, finalized, visited, time);
        }
    }

    finalized[vertex] = time++;
}

std::vector<vertex_t> topological_sort_dummy(const graph& g)
{
    std::vector<int> finalized(g.vertex_count(), -1);
    std::vector<bool> visited(g.vertex_count(), false);
    int time = 0;

    // Подобно обхождане е лошо, но върши работа за примера.
    // Трябва да се имплементира итератор
    // за вектора в противен случай разчитаме върховете да са числа...
    for (int i = 0; i < g.vertex_count(); i++)
    {
        if(!visited[i])
            tsort_visit_dummy(g, i, finalized, visited, time);
    }
    
    std::vector<vertex_t> result(g.vertex_count());
    
    for (size_t i = 0; i < g.vertex_count(); i++)
    {
        result[i] = i;
    }
    
    std::sort(result.begin(), 
              result.end(), 
              [&finalized](const vertex_t& lhs, const vertex_t& rhs)
              {
                return finalized[lhs] < finalized[rhs];
              });
    
    return result;
}

int main()
{

}