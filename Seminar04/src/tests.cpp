#include <cassert>
#include <iostream>
#include "doubly-linked-list.hpp"

void insert_basic_tests()
{
	doubly_linked_list<int> ll;
	ll.push_back(1);
	assert(ll.front() == ll.back() && ll.front() == 1);

	ll.pop_back();
	assert(ll.empty());

	ll.push_front(2);
	assert(ll.front() == ll.back() && ll.front() == 2);

	ll.pop_back();
	assert(ll.empty());

	ll.push_back(1);
	ll.push_front(2);

	assert(ll.front() == 2 && ll.back() == 1 && ll.size() == 2);
}

void insert_erase_tests()
{
	// push front and back
	doubly_linked_list<int> ll;
	for (size_t i = 10; i < 20; i++)
	{
		ll.push_back(i);
	}

	for (size_t i = 0; i < 10; i++)
	{
		ll.push_front(9 - i);
	}

	int start = 0;
	for (auto it = ll.begin(); it != ll.end(); ++it)
	{
		assert(*it == start++);
	}

	// remove from the middle
	auto it = ll.begin();
	for (size_t i = 0; i < 10; i++)
		++it;

	while (it != ll.end())
	{
		auto prev = it++;
		if (*prev == 19)
			int x = 10;
		ll.remove(prev);
	}

	start = 0;
	for (const auto& x : ll)
	{
		assert(x == start++);
	}

	// insert into the middle
	{
		auto it = ll.begin();
		for (size_t i = 0; i < 5; i++)
			++it;

		for (size_t i = 0; i < 10; i++)
		{
			ll.insert(it, i + 10);
		}
	}

	{
		auto it = ll.begin();
		for (size_t i = 0; i < 5; i++)
		{
			assert(*it == i);
			++it;
		}

		for (size_t i = 0; i < 10; i++)
		{
			assert(*it == i + 10);
			++it;
		}

		for (size_t i = 0; i < 5; i++)
		{
			assert(*it == i + 5);
			++it;
		}

		assert(it == ll.end());
	}
}

void constructor_tests()
{
	doubly_linked_list<int> ll;

	for (size_t i = 0; i < 100; i++)
	{
		ll.push_back(i);
	}

	doubly_linked_list<int> copy(ll);
	assert(copy.size() == ll.size());

	auto it = ll.begin();
	for (const auto& x : copy)
	{
		assert(x == *it);
		++it;
	}

	doubly_linked_list<int> move(std::move(copy));
	assert(copy.empty());

	assert(move.size() == ll.size());

	auto it1 = ll.begin();
	for (const auto& x : move)
	{
		assert(x == *it1);
		++it1;
	}
}

int main()
{
	std::cout << "Starting tests..." << std::endl;
	insert_basic_tests();
	insert_erase_tests();
	constructor_tests();
	std::cout << "No assertions failed" << std::endl;
}