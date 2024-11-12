#include "node_utils.h"
#include <iostream>

template <class T>
node<T>* merge(node<T>* lhs, node<T>* rhs)
{
	// result linked list
	node<T>* head = nullptr;
	node<T>* tail = nullptr;

	while (lhs && rhs)
	{
		if (lhs->data < rhs->data)
		{
			append_back(head, tail, lhs);
			lhs = lhs->next;
		}
		else
		{
			append_back(head, tail, rhs);
			rhs = rhs->next;
		}
	}

	if (lhs)
	{
		tail->next = lhs;
	}

	if (rhs)
	{
		tail->next = rhs;
	}

	return head;
}

template <class T>
node<T>* get_middle(node<T>* list)
{
	if (!list || !list->next)
		return list;

	node<T>* fast = list->next;
	node<T>* slow = list;

	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}

template <class T>
node<T>* merge_sort(node<T>* list)
{
	if (!list || !list->next)
		return list;

	node<T>* middle = get_middle(list);

	node<T>* right_part = middle->next;
	middle->next = nullptr;

	node<T>* left_sorted = merge_sort(list);
	node<T>* right_sorted = merge_sort(right_part);

	return merge(left_sorted, right_sorted);
}

int main()
{
	node<int>* ll = new node(1, new node(0, new node(2, new node(-1, new node(10)))));
	ll = merge_sort(ll);
	if (is_sorted(ll) && list_size(ll) == 5)
		std::cout << "passed";
	else
		std::cout << "failed";
    free_list(ll);
}