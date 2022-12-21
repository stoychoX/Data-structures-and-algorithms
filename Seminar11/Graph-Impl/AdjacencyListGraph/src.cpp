#include<iostream>
#include<list>
#include<algorithm>
#include"AdjListGraph.h"

int main() {
    AdjListGraph g(10);

    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 1);
    g.addEdge(0, 3, 1);
    g.addEdge(0, 4, 1);

    auto res = g.adjacent(1);

    for(auto i : res) {
        std::cout << i.to << " ";
    }
}