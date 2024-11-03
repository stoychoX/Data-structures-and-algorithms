#include <iostream>
#include <vector>

void next_iterators(std::vector<int>& number)
{
    auto it = number.rbegin();
    while(it != number.rend() && *it == 1)
    {
        *it = 0;
        ++it;
    }
    if (it != number.rend())
        *it = 1;
}

void next(std::vector<int>& number)
{
    int idx = number.size() - 1;

    while (idx >= 0 && number[idx] == 1)
        number[idx--] = 0;
    
    if (idx >= 0)
        number[idx] = 1;
}

void print(const std::vector<int>& number)
{
    std::cout << "[ ";
    for(auto it = number.begin(); it != number.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << "]" << std::endl;
}

void generate_boolean_vectors(unsigned n)
{
    std::vector<int> number(n, 0);
    size_t count = 1 << n;

    for (size_t i = 0; i < count; i++)
    {
        print(number);
        next(number);
    }
}

int main()
{
    generate_boolean_vectors(3);
}