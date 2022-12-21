/*
Тегловен неориентиран граф представен чрез списъци на съседство.

Предимства:
* Паметта която използваме е вече O(|V| + |E|)
* Вземането на всички съседи е по - бързо

Недостатъци:
* Да проверим дали има ребро между два върха вече не е O(1)

*/
#ifndef ADJ_LIST_GRAPH_IMPL
#define ADJ_LIST_GRAPH_IMPL

#include<vector>
#include<list>
#include<algorithm>

class AdjListGraph {
    public:
    using vertex_t = unsigned int;
    using weight_t = unsigned int;

    private:
    struct Edge {
        vertex_t to;
        weight_t weight;
    };

    std::vector<std::list<Edge>> data;

    public:
    AdjListGraph(size_t n);

    void addVertex();
    void removeVertex(vertex_t);
    bool validVertex(vertex_t) const;

    void addEdge(vertex_t, vertex_t, weight_t);
    void removeEdge(vertex_t, vertex_t);

    weight_t getWeight(vertex_t, vertex_t) const;
    bool hasEdge(vertex_t, vertex_t) const;

    size_t vertexCount() const;

    std::vector<Edge> adjacent(vertex_t) const;
};

#endif