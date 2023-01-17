#include<iostream>
#include<string>
#include<map>
#include<vector>

bool canRead(const std::multimap<char, char>& graph, const std::string& word, size_t at) {
    if(at == word.length() - 1)
        return true;

    auto successors = graph.find(word[at]); // Може ли да си спестим това търсене?

    if(successors == graph.end())
        return false;
    
    while(successors != graph.end() && (*successors).first == word[at]) {
        if((*successors).second == word[at + 1]) {
            return canRead(graph, word, at + 1);
        }

        ++successors;
    }

    return false;
}

int main() {
    std::multimap<char, char> graph;

    graph.insert({'a', 'c'});
    graph.insert({'a', 'd'});
    graph.insert({'c', 'b'});
    graph.insert({'b', 'd'});
    graph.insert({'d', 'k'});
    graph.insert({'d', 'c'});
    graph.insert({'d', 'a'});
    
    std::map<char, bool> visited;
    std::string word = "adaz";

    std::cout << canRead(graph, word, 0);
}