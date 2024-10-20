#include <iostream>
#include <algorithm> // std::is_sorted
#include <vector>    // std::vector

/// @brief Reorders the elements in such a way that all elements for which are less than pivot 
// precede all elements which are greater or equal to pivot. Relative order of the elements is not preserved.
// TODO: remove copy somehow???
template <class T>
size_t partition(T* pArr, size_t len)
{
    if (pArr[0] > pArr[len - 1])
        std::swap(pArr[0], pArr[len - 1]);

    T& partitioningElement = pArr[len - 1];
    size_t left = 0;
    size_t right = len - 1;

    while (true)
    {
        while (pArr[++left] < partitioningElement)
            ;

        while (pArr[--right] > partitioningElement)
        {
            if (left == right)
                break;
        }

        if (left >= right)
            break;

        std::swap(pArr[left], pArr[right]);
    }

    std::swap(pArr[left], partitioningElement);
    return left;
}

template<class T>
void quickSort(T* arr, unsigned size)
{
    if(size < 2)
        return;
    
    unsigned pivotPos = partition(arr, size);

    quickSort(arr, pivotPos);
    quickSort(arr + pivotPos + 1, size - pivotPos - 1);
}

int main()
{
    std::vector<int> numbers;
    unsigned size = rand() % 10000;
    numbers.resize(size);

    for (size_t i = 0; i < size; i++)
    {
        numbers[i] = rand() % 10000;
    }

    quickSort(numbers.data(), numbers.size());

    std::cout << std::is_sorted(numbers.begin(), numbers.end());
}