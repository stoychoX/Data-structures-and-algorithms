// Малко допълнителни неща покрай дфс ако ви е интересно.
#include<iostream>
#include"Graph-Impl/AdjacencyListGraph/AdjListGraph.h"
#include"Graph-Impl/MatrixGraph/MatrixGraph.h"
#include<vector>
#include<algorithm>

using std::vector;
using vertex_t = AdjListGraph::vertex_t; // Типа представящ връх в графа

class DFSExamples {
private:
    vector<size_t> in;
    vector<size_t> out;
    vector<vertex_t> parent;

public:

void DFS_Visit(const AdjListGraph& g, size_t& time, vertex_t s) {
    in[s] = time;
    time++;

    const auto& adj = g.adjacent(s);

    for(const auto& v : adj) {
        if(in[v.to] == -1) {
            parent[v.to] = s;
            DFS_Visit(g, time, v.to);
        }
    }

    time++;
    out[s] = time;
}

void DFS(const AdjListGraph& g, bool showDetails) {
    // Нека си представим, че имаме време. Всяка стъпка на алгоритъма отнема една единица време.
    size_t time = 0;

    // Всеки връх бива открит в някакво време. Нека в този масив записваме кога е бил открит всеки връх.
    in = vector(g.vertexCount(), (size_t)(-1));

    // С всеки връх приключваме по някое време. Той няма повече непосетени съседи и спираме да се интересуваме от него.
    // Нека в този масив записваме кога се случва това.
    out = vector(g.vertexCount(), (size_t)(-1));

    // std::vector<bool> visited(g.vertexCount(), false); 
    // - от този масив вече нямаме нужда. Връх v e посетен когато in[v] != -1.

    // Също така в примера видяхме, че DFS прави дърво. Нека си запазим това дърво.
    // Тук стандартното представяне на дърво е неудобно, затова ще представяме дървото като масив от бащите.
    // Примомняне: Ако v e връх parent[v] е бащата на v или -1 ако v e корен.
    parent = vector(g.vertexCount(), (vertex_t)(-1));

    // За всеки връх
    for (vertex_t i = 0; i < g.vertexCount(); i++)
        if(in[i] == -1) // Ако не е посетен
            DFS_Visit(g, time, i); // Посети го и посети всички върхове достижими от него
    
    // Да видим какво имаме
    if(showDetails) {
        for (vertex_t i = 0; i < g.vertexCount(); i++) {
            std::cout << "Vertex " << i << std::endl;
            std::cout 
             << "Discovered at: " << in[i] << std::endl
             << "Finished at: "   << out[i] << std::endl 
             << "Parent: "        << parent[i] << std::endl << std::endl;
        }
    }
}

void DFS_Visit_Tsort(const MatrixGraph g, size_t& time, vertex_t s) {
    in[s] = time;
    time++;

    const auto& adj = g.adjacent(s);

    for(const auto& v : adj) {
        if(in[v] == -1) {
            parent[v] = s;
            DFS_Visit_Tsort(g, time, v);
        }
    }

    time++;
    out[s] = time;
}

// Топологически сортировки, Job scheduling
// Защо са ни тези масиви in и out? Те ни дават информация, която можем да използваме за други интересни алгоритми.
// Ще оставим подробното им разглеждане на други курсове, тук само ще разгледаме един бърз пример.

// Нека си представим, че имаме някакви задачи за вършене. Абсолютно вероятно е някои от тези задачи да зависят от други.
// Примерно, не мога да кандидатствам за университет ако преди това нямам диплома за завършен 12 клас
// (въпреки, че май е възможно в някои нови български университети).
// 
// Можем да си представим задачите като върхове, а това, че задача А трябва да се изпълни преди задача Б да 
// бележим чрез ориентирано ребро А -> Б.
// 
// Искам така да си подредя задачите, че да ги изпълня без да нарушавам зависимостите.
// 
// Твърдя, че ако пусна DFS, и сортирам върховете по out стойности в намаляващ ред това решава задачата ми.
//
// Накратко, защо това е вярно?
// Нека имам V -> U. Има два случая, или да открия V преди U или да открия U преди V.
//
// 1. Откривам V преди U. Да де, но имам ребро от V към U, Следователно ще открия и финализирам U преди да финализирам V.
// Сега out[U] > out[V] и не нарушавам зависимостите.
// 2. Ако открия U преди V, ще финализирам U преди да стигна до V. В графа няма цикли и ако имаше път от U -> V това би затворило цикъл.
// Тоест ще финализирам U преди да открия V. От тук следва, че out[U] > in[V] > out[V], което отново влече наредба, която не нарушава зависимостите.
// Няма други случаи. 

void DFS_Tsort(const MatrixGraph& g) {
    size_t time = 0;

    in = vector(g.vertexCount(), (size_t)(-1));
    out = vector(g.vertexCount(), (size_t)(-1));
    parent = vector(g.vertexCount(), (vertex_t)(-1));

    for (vertex_t i = 0; i < g.vertexCount(); i++)
        if(in[i] == -1)
            DFS_Visit_Tsort(g, time, i);
    
    std::vector<std::pair<vertex_t, size_t>> result(g.vertexCount());

    for (vertex_t i = 0; i < g.vertexCount(); i++)
        result[i] = {i, out[i]};
    
    auto comp = [](std::pair<vertex_t, size_t>& fst, std::pair<vertex_t, size_t>& snd) -> bool {
        return fst.second > snd.second;
    };

    std::sort(result.begin(), result.end(), comp);

    for(const auto& vertexOutPair : result)
        std::cout << vertexOutPair.first << " ";
}

// Използвам матричния, понеже той е ориентиран.
void tsort(const MatrixGraph& g) {
    size_t time = 0;

    // Нулираме масивите
    in = vector(g.vertexCount(), (size_t)(-1));
    out = vector(g.vertexCount(), (size_t)(-1));
    parent = vector(g.vertexCount(), (vertex_t)(-1));

    DFS_Tsort(g);
}
};

int main() {
    DFSExamples d;

    // Нека си вземем графа от примера
    // Там върховете са номерирани от 1 до 12
    // Тук от 0 до 11
    AdjListGraph g(12);

    g.addEdge(0, 2, 1);
    g.addEdge(0, 4, 1);
    g.addEdge(0, 5, 1);
    g.addEdge(0, 8, 1);

    g.addEdge(1, 7, 1);
    g.addEdge(1, 3, 1);

    g.addEdge(2, 4, 1);
    g.addEdge(2, 5, 1);
    g.addEdge(2, 6, 1);
    g.addEdge(2, 7, 1);

    g.addEdge(3, 9, 1);

    g.addEdge(4, 6, 1);

    g.addEdge(8, 11, 1);
    g.addEdge(8, 10, 1);

    g.addEdge(10, 11, 1);

    d.DFS(g, true);

    // Пример за топосортировка
    MatrixGraph tsort(9);


    // https://ocw.mit.edu/courses/6-006-introduction-to-algorithms-fall-2011/resources/mit6_006f11_lec14_orig/
    // Този граф е взет от линка и е на страница 5.
    tsort.addDirectedEdge(5, 3, 1);
    tsort.addDirectedEdge(4, 3, 1);
    tsort.addDirectedEdge(4, 2, 1);
    tsort.addDirectedEdge(2, 1, 1);
    tsort.addDirectedEdge(1, 0, 1);
    tsort.addDirectedEdge(7, 2, 1);
    tsort.addDirectedEdge(7, 6, 1);
    tsort.addDirectedEdge(6, 1, 1);

    d.DFS_Tsort(tsort);
}