#include <iostream>

struct E
{
    E()
    {
        std::cout << "constr" << std::endl;
    }

    ~E()
    {
        std::cout << "destr" << std::endl;
    }
};

int main()
{
    std::cout << "operator new called" << std::endl;
    E* e = static_cast<E*>(operator new(sizeof(E)));
    std::cout << "placement new called" << std::endl;
    new (e) E();

    std::cout << "destructor manually called" << std::endl;
    e->~E();
    std::cout << "operator delete called" << std::endl;
    operator delete(e, sizeof(E));
}