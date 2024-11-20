#include "forward-iterator-bst.hpp"
#include <iostream>

int main()
{
    Bst<int> b;
    b.insert(1);
    b.insert(2);
    b.insert(3);
    b.insert(0);
    b.insert(4);
    b.insert(5);
    b.insert(6);

    for(int x : b)
    {
        std::cout << x << " ";
    }
}