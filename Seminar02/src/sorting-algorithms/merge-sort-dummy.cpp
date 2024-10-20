#include <iostream>

template<typename T>
void merge(T* arr1, unsigned len1, 
           T* arr2, unsigned len2)
{
	T* resultArray = new T[len1 + len2];

	unsigned cursor1 = 0;
	unsigned cursor2 = 0;
	unsigned resultCursor = 0;

	while (cursor1 < len1 && cursor2 < len2)
	{
		if (arr1[cursor1] <= arr2[cursor2])
			resultArray[resultCursor++] = arr1[cursor1++];
		else
			resultArray[resultCursor++] = arr2[cursor2++];
	}

	while (cursor1 < len1)
		resultArray[resultCursor++] = arr1[cursor1++];
    
	while (cursor2 < len2)
		resultArray[resultCursor++] = arr2[cursor2++];

	for (size_t i = 0; i < len1 + len2; i++)
		arr1[i] = resultArray[i];
    
	delete[] resultArray;
}

template <typename T>
void mergeSort(T* arr, unsigned len)
{
	if (len < 2)
		return;

	unsigned mid = len / 2;

	mergeSort(arr, mid);
	mergeSort(arr + mid, len - mid);

	merge<T>(arr, mid, arr + mid, len - mid);
}

int main()
{
	int arr[4] = { 9, 6, 5, 8 };
	mergeSort(arr, 4);

	for (int i = 0; i < 4; i++)
		std::cout << arr[i] << " ";
}