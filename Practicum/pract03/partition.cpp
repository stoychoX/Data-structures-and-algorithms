#include <iostream>
#include <vector>

bool isEven(int n) {
    return !(n % 2);
}

template <class RandomIt, class Predicate>
RandomIt partition(RandomIt first, RandomIt last, Predicate p)
{
    RandomIt beg = first;
    for (; beg != last; ++beg)
    {
        if (!p(*beg))
            break;
    }
    if (beg == last)
        return beg;

    for (RandomIt it = std::next(beg); it != last; ++it)
    {
        if (p(*it))
        {
            std::swap(*it, *beg);
            ++beg;
        }
    }

    return beg;
}

int main()
{
    std::vector<int> v;
    for (int i = 1; i <= 10; i++)
        v.push_back(i);

    partition(v.begin(), v.end(), isEven);

    for (int i = 0; i < 10; i++)
        std::cout << v[i] << " ";
}
