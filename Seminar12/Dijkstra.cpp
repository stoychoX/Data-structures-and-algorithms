#include"../Seminar11/Graph-Impl/MatrixGraph/MatrixGraph.h"
#include<queue>
#include<iostream>
#include<list>

using vertex_t = MatrixGraph::vertex_t;
using weight_t = MatrixGraph::weight_t;

bool relax(std::vector<weight_t>& distance, const MatrixGraph& g, vertex_t reached, vertex_t currentVertex) {
    if (distance[reached] > distance[currentVertex] + g.getWeight(currentVertex, reached)) {
        distance[reached] = distance[currentVertex] + g.getWeight(currentVertex, reached);
        return true;
    }
    return false;
}

// Намиране на най - къс път между два върха
int Dijkstra(const MatrixGraph& g, vertex_t start, vertex_t end) {
    std::vector<vertex_t> parent(g.vertexCount(), -1);
    std::vector<weight_t> distances(g.vertexCount(), INT_MAX);

    struct VertexDistancePair {
        vertex_t vertex;
        weight_t distanceFromStart;

        bool operator<(const VertexDistancePair& other) const {
            return distanceFromStart > other.distanceFromStart;
        }
    };

    std::priority_queue<VertexDistancePair> q;

    distances[start] = 0;
    q.push({ start, 0 });

    while (!q.empty()) {
        auto currentPair = q.top();
        q.pop();

        if (currentPair.vertex == end) {
            auto currentVertex = currentPair.vertex;

            std::list<vertex_t> path;

            while (currentVertex != start) {
                path.insert(path.begin(), currentVertex);
                currentVertex = parent[currentVertex];
            }

            path.insert(path.begin(), start);

            for (const auto& v : path)
                std::cout << v << std::endl;

            return distances[currentPair.vertex];
        }

        const auto& adjacent = g.adjacent(currentPair.vertex);

        for (auto reached : adjacent) {
            if (relax(distances, g, reached, currentPair.vertex)) {
                parent[reached] = currentPair.vertex;
                q.push({ reached, distances[reached] });
            }
        }
    }

    return INT_MAX;
}

int main() {
    MatrixGraph g(8);

    g.addEdge(0, 1, 23);
    g.addEdge(0, 2, 74);
    g.addEdge(0, 3, 24);

    g.addEdge(1, 2, 35);
    g.addEdge(1, 4, 23);

    g.addEdge(2, 4, 24);
    g.addEdge(2, 3, 26);

    g.addEdge(3, 6, 32);

    g.addEdge(4, 5, 51);
    g.addEdge(4, 7, 17);

    g.addEdge(5, 7, 15);

    g.addEdge(6, 7, 32);


    int sp = Dijkstra(g, 0, 7);

    std::cout << std::endl << sp;
}