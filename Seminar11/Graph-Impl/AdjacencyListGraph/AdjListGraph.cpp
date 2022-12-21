#include"AdjListGraph.h"

using vertex_t = AdjListGraph::vertex_t;
using weight_t = AdjListGraph::weight_t;

AdjListGraph::AdjListGraph(size_t vertexCount) {
    data = std::vector<std::list<Edge>>(vertexCount, std::list<Edge>());
}

void AdjListGraph::addVertex() {
    data.push_back(std::list<Edge>());
}

void AdjListGraph::removeVertex(vertex_t v) {
    if(!validVertex(v))
        throw "Invalid vertex";

    // Премахва самия връх
    data.erase(data.begin() + v);

    // За всеки от останалите върхове ако
    // има елемент, който сочи към него трябва да се изтрие
    // ако има елемент, който е по -  голям от него трябва да се намали с 1

    for(auto& vertexList : data) {
        vertexList.remove_if([&](Edge e) -> bool { return e.to == v; });

        for(Edge& e : vertexList)
            if(e.to > v) 
                e.to--;
    }
}

bool AdjListGraph::validVertex(vertex_t v) const {
    return v < data.size();
}

void AdjListGraph::addEdge(vertex_t from, vertex_t to, weight_t w) {
    if(!validVertex(from) || !validVertex(to))
        throw "Invalid vertex";

    data[from].push_back( {to, w} );
    data[to].push_back( {from, w} );
}

void AdjListGraph::removeEdge(vertex_t from, vertex_t to) {
    if(!validVertex(from) || !validVertex(to))
        throw "Invalid vertex";

    data[from].remove_if([&](Edge e) -> bool {return e.to == to; });   
    data[to].remove_if([&](Edge e) -> bool {return e.to == from; });   
}

bool AdjListGraph::hasEdge(vertex_t from, vertex_t to) const {
    if(!validVertex(from) || !validVertex(to))
        throw "Invalid vertex";
    
    for(const Edge& e : data[from])
        if(e.to == to)
            return true;
    
    return false;
}

weight_t AdjListGraph::getWeight(vertex_t from, vertex_t to) const {
     if(!validVertex(from) || !validVertex(to))
        throw "Invalid vertex";
    
    for(const Edge& e : data[from])
        if(e.to == to)
            return e.weight;
    
    return 0;
}

std::vector<AdjListGraph::Edge> AdjListGraph::adjacent(vertex_t v) const {
    return std::vector<Edge>(data[v].begin(), data[v].end());
}

size_t AdjListGraph::vertexCount() const {
    return data.size();
}