#include"Linked-Queue.hpp"
#include<cassert>
#include<iostream>

void runTest() {
    LinkedQueue<int> q;

    for (size_t i = 0; i < 1000; i++)
        q.push(i);

    std::cout << "Passed size test" << std::endl;
    assert(q.size() == 1000);

    for (size_t i = 0; i < 1000; i++) {
        assert(q.front() == i);
        q.pop();
    }

    std::cout << "Push, pop and top working as expected" << std::endl;

    assert(q.empty() && q.size() == 0);

    std::cout << "Passed empty test" << std::endl;
}

int main() {
    runTest();
}
