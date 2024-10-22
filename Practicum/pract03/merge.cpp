#include <iostream>
#include <vector>

// V. 1
template<class RandomIt>
void merge(RandomIt first1, RandomIt last1,
    RandomIt first2, RandomIt last2,
    RandomIt buff)
{
    for (; first1 != last1; ++buff)
    {
        if (first2 == last2)
        {
            for (; first1 != last1; ++first1, ++buff)
                *buff = *first1;
            
            return;
        }

        if (*first2 < *first1)
        {
            *buff = *first2;
            ++first2;
        }
        else
        {
            *buff = *first1;
            ++first1;
        }
    }

    for (; first2 != last2; ++first2, ++buff)
        *buff = *first2;
}

// V. 2
template <class RandomIt>
void merge(RandomIt first1, RandomIt last1,
    RandomIt first2, RandomIt last2,
    RandomIt buff)
{
    while (first1 != last1 && first2 != last2)
    {
        if (*first1 <= *first2)
        {
            *buff = *first1;
            ++first1;
        }
        else
        {
            *buff = *first2;
            ++first2;
        }

        ++buff;
    }

    while (first1 != last1)
    {
            *buff = *first1;
            ++first1;
            ++buff;
    }

    while (first2 != last2)
    {
        *buff = *first2;
        ++first2;
        ++buff;
    }
}

int main()
{
    std::vector<int> v1;
    for (int i = 1; i <= 5; i++)
        v1.push_back(i);

    for (int i = 3; i <= 8; i++)
        v1.push_back(i);

    std::vector<int> v(11);

    merge(v1.begin(), v1.begin() + 5, v1.begin() + 5, v1.end(), v.begin());

    for (int i = 0; i < 11; i++)
        std::cout << v[i] << " ";
}
