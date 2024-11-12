#include "node_utils.h"
#include <cassert>
#include <iostream>

// Implementation is inspired by:
// https://github.com/Angeld55/Data_structures_and_algorithms_FMI/blob/main/Miscellaneous/singlyLinkedList_quickSort.cpp

template <class T>
using list_info = std::pair<node<T>*, node<T>*>;

template <class T, class Predicate>
list_info<T> partition(node<T>* list, Predicate pred)
{
	node<T>* true_begin = nullptr;
	node<T>* true_end = nullptr;

	node<T>* false_begin = nullptr;
	node<T>* false_end = nullptr;

	while (list)
	{
		if (pred(list->data))
		{
			append_back(true_begin, true_end, list);
		}
		else
		{
			append_back(false_begin, false_end, list);
		}
		list = list->next;
	}

	if (true_end)
	{
		true_end->next = nullptr;
	}
	if (false_end)
	{
		false_end->next = nullptr;
	}

	return {true_begin, false_begin};
}

template <class T>
list_info<T> concat_lists(list_info<T> left, list_info<T> right)
{
	if (left.first == nullptr)
		return right;
	if (right.first == nullptr)
		return left;

	left.second->next = right.first;
	return {left.first, right.second};
}

template <class T>
list_info<T> quick_sort_impl(node<T>* list)
{
	if (!list || !list->next)
		return {list, list};

	const T& pivot_element = list->data;
	list_info<T> result = partition(list, [&pivot_element](const T& element) { return element < pivot_element; });

	node<T>* pivot = result.second;

	list_info<T> left_sorted = quick_sort_impl(result.first);

	// Skip the pivot element.
	list_info<T> right_sorted = quick_sort_impl(result.second->next);

	// Attach pivot as the first element.
	pivot->next = right_sorted.first;
	right_sorted.first = pivot;

	if (!right_sorted.second)
		right_sorted.second = pivot;

	return concat_lists(left_sorted, right_sorted);
}

template <class T>
void quick_sort(node<T>*& list)
{
	list_info<T> result = quick_sort_impl(list);
	list = result.first;
}

void tests()
{
	using inode = node<int>;

	// test empty list
	inode* ll = nullptr;
	quick_sort(ll);
	assert(ll == nullptr);

	// One element case
	ll = new inode(1);
	quick_sort(ll);
	assert(ll && ll->data == 1 && !ll->next);

	// Two elements case (sorted & unsorted)
	ll->next = new inode(0);
	quick_sort(ll);
	assert(ll && ll->data == 0 && ll->next && ll->next->data == 1 && !ll->next->next);
	quick_sort(ll);
	assert(ll && ll->data == 0 && ll->next && ll->next->data == 1 && !ll->next->next);

	ll = push_front(ll, 2);
	ll = push_front(ll, 3);

	quick_sort(ll);
	assert(is_sorted(ll) && list_size(ll) == 4);
	quick_sort(ll);
	assert(is_sorted(ll) && list_size(ll) == 4);

	// Random elements
	srand(time(0));

	for (size_t i = 0; i < 1000; i++)
	{
		ll = push_front(ll, rand() % 10000);
	}
	assert(list_size(ll) == 1004);
	quick_sort(ll);
	assert(is_sorted(ll) && list_size(ll) == 1004);

	free_list(ll);
}

int main()
{
	tests();
}