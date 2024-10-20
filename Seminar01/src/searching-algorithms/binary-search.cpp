#include <iostream>

template <class T>
int binarySearch(const T* arr, size_t size, T elem)
{
    int left = 0;
    int right = size - 1;

    while (right - left >= 0)
    {
        int mid = left + (right - left) / 2;

        if(arr[mid] == elem)
        {
            return mid;
        }
        else if (arr[mid] > elem)
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }

    return -1;
}

constexpr unsigned EXAMPLE_SIZE = 7;

int main()
{
    int example[EXAMPLE_SIZE] = { 1, 2, 4, 8, 16, 32, 64 };
    int needle = 4;

    int index = binarySearch(example, EXAMPLE_SIZE, needle);
    if(index == -1)
    {
        std::cout << "Unable to find the element" << std::endl;
    }
    else
    {
        std::cout << "Element " << needle << " found at " 
            << index << " position: " << example[index] << std::endl; 
    }
}