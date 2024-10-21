#include <iostream>
#include <vector>
#include <algorithm>

template<class T>
void merge(T* firstArray, unsigned firstSize, 
           T* secondArray, unsigned secondSize,
           T* buffer)
{
    unsigned firstIter = 0;
    unsigned secondIter = 0;
    unsigned resultIter = 0;

    while(firstIter < firstSize && secondIter < secondSize)
    {
        if(firstArray[firstIter] > secondArray[secondIter])
        {
            buffer[resultIter] = secondArray[secondIter];
            secondIter++;
        }
        else
        {
            buffer[resultIter] = firstArray[firstIter];
            firstIter++;
        }
        resultIter++;
    }

    while(firstIter < firstSize)
    {
        buffer[resultIter++] = firstArray[firstIter++];
    }

    while(secondIter < secondSize)
    {
        buffer[resultIter++] = secondArray[secondIter++];
    }
}


template<class T>
void mergeSortStep(T* arr, unsigned size, T* buffer)
{
    if(size < 2)
        return;
    
    unsigned mid = size / 2;
    mergeSortStep(arr, mid, buffer);
    mergeSortStep(arr + mid, size - mid, buffer);

    merge(arr, mid, arr + mid, size - mid, buffer);

    for (size_t i = 0; i < size; i++)
        arr[i] = buffer[i];
}

template<class T>
void mergeSort(T* arr, unsigned size)
{
    if(size < 2)
        return;
    
    T* buffer = new T[size];
    mergeSortStep(arr, size, buffer);
    delete[] buffer;
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

    mergeSort(numbers.data(), numbers.size());

    std::cout << std::is_sorted(numbers.begin(), numbers.end()) << std::endl;
}
