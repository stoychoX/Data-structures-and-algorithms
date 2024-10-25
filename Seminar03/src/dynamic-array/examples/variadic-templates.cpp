#include <iostream>

// std::forward example - preserve the value category (lvalue or rvalue)
void f(const int& x)
{
    std::cout << "lvalue" << std::endl;
}

void f(const int&& x)
{
    std::cout << "rvalue" << std::endl;
}

template<class T>
void g(T&& x)
{
    f(std::forward<T>(x));
}

struct printer
{
    static void print()
    {
        std::cout << std::endl;
    }

    template<class T, class... Args>
    static void print(const T& first, const Args&... args)
    {
        std::cout << first << " ";
        print(std::forward<const Args&>(args)...);
    }
};

struct Entity
{
    int x;
    friend std::ostream& operator<<(std::ostream& os, const Entity& e);

    Entity(int x_) : x(x_) {}

    Entity(Entity&)
    {
        std::cout << "Copied " << x << std::endl;
    }
};

std::ostream& operator<<(std::ostream& os, const Entity& e)
{
    os << e.x;
    return os;
}

int main()
{
    int x = 10;
    g(x);

    g(std::move(x));

}