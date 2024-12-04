#include "indexable-bst.hpp"

int main()
{
    Bst<int> bst;

    for (size_t i = 0; i < 100; i++)
    {
        bst.insert(i);
    }

    for (size_t i = 0; i < bst.getSize(); i++)
    {
        std::cout << bst.index(i) << " ";
    }

    std::cout << std::endl;

    for (size_t i = 0; i < 50; i++)
    {
        bst.remove(i);
    }

    for (size_t i = 0; i < bst.getSize(); i++)
    {
        std::cout << bst.index(i) << " ";
    }
}