#include<iostream>
#include"Graph-Impl/AdjacencyListGraph/AdjListGraph.h"
#include"Graph-Impl/MatrixGraph/MatrixGraph.h"
#include<queue>

void BFS(const MatrixGraph& g, MatrixGraph::vertex_t start) {
    std::vector<bool> visited(g.vertexCount(), false);

    std::queue<MatrixGraph::vertex_t> q;

    q.push(start);

    while(!q.empty()) {
        MatrixGraph::vertex_t current = q.front();
        q.pop();

        if(visited[current])
            continue;
        
        visited[current] = true;

        std::cout << current << " ";

        auto successors = g.getSuccessors(current);

        for(const auto& currentVertex : successors) {
            if(!visited[currentVertex])
                q.push(currentVertex);
        }
    }
}

void DFSRec(std::vector<bool>& visited, const AdjListGraph& g, AdjListGraph::vertex_t start) {
    visited[start] = true;

    auto child = g.adjacent(start);

    std::cout << "Visited " << start << std::endl;

    for(const auto& currChild : child) {
        if(!visited[currChild.to]) {
            DFSRec(visited, g, currChild.to);
        }
    }
}

void DFS(const AdjListGraph& g, AdjListGraph::vertex_t start) {
    std::vector<bool> visited(g.vertexCount(), false);
    DFSRec(visited, g, start);
}


int main() {
    // MatrixGraph g(5);
    AdjListGraph g(5);
    g.addEdge(0, 2, 1);
    g.addEdge(0, 3, 1);
    g.addEdge(0, 1, 1);
    g.addEdge(2, 3, 1);
    g.addEdge(1, 4, 1);
    g.addEdge(3, 4, 1);
    g.addEdge(1, 3, 1);

    DFS(g, 0);
}