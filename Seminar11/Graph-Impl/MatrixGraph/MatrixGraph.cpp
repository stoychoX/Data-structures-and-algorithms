#include"MatrixGraph.h"

using vertex_t = MatrixGraph::vertex_t;
using weight_t = MatrixGraph::weight_t;

MatrixGraph::MatrixGraph(size_t v) {
    data = std::vector<std::vector<weight_t>>(v, std::vector<weight_t>(v, 0));
}

bool MatrixGraph::validVertex(vertex_t v) const {
    return v < data.size();
}

bool MatrixGraph::adjacent(vertex_t from, vertex_t to) const {
    if(!validVertex(from) || !validVertex(to))
        throw "Invalid vertex";
    
    return data[from][to] > 0;
}

void MatrixGraph::addDirectedEdge(vertex_t from, vertex_t to, weight_t w) {
    if(!validVertex(from) || !validVertex(to))
        throw "Invalid vertex";
    
    data[from][to] = w;
}

void MatrixGraph::addEdge(vertex_t from, vertex_t to, weight_t w) {
    addDirectedEdge(from, to, w);
    addDirectedEdge(to, from, w);
}

void MatrixGraph::addVertex() {
    for(auto& v : data)
        v.push_back(0);
    
    data.push_back(std::vector<weight_t>());
}

void MatrixGraph::removeEdge(vertex_t from, vertex_t to) {
    if(!validVertex(from) || !validVertex(to))
        throw "Invalid vertex";
    
    data[from][to] = 0;
}

void MatrixGraph::removeVertex(vertex_t v) {
    if(!validVertex(v))
        throw "Invalid vertex";
    
    data.erase(data.begin() + v);

    for(auto& vertex : data)
        vertex.erase(vertex.begin() + v);
}

weight_t MatrixGraph::getWeight(vertex_t from, vertex_t to) const {
    if(!validVertex(from) || !validVertex(to))
        throw "Invalid vertex";
    
    return data[from][to];
}

std::vector<vertex_t> MatrixGraph::getSuccessors(vertex_t from) const {
    if(!validVertex(from))
        throw "Invalid vertex";

    std::vector<vertex_t> result;

    for (size_t i = 0; i < data.size(); i++)
        if(data[from][i] > 0) 
            result.push_back(i);

    return result;
}

std::vector<vertex_t> MatrixGraph::getPredecessors(vertex_t from) const {
    if(!validVertex(from))
        throw "Invalid vertex";

    std::vector<vertex_t> result;

    for (size_t i = 0; i < data.size(); i++)
        if(data[i][from] > 0) 
            result.push_back(i);

    return result;
}

std::vector<vertex_t> MatrixGraph::adjacent(vertex_t from) const {
    return getSuccessors(from);
}


size_t MatrixGraph::vertexCount() const {
    return data.size();
}