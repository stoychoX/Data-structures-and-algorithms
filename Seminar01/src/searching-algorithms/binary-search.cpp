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

int main()
{
    
}