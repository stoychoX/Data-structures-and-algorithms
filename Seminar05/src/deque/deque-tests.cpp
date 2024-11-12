#include "deque.hpp"
#include <iostream>

bool testPushBack()
{
	deque<int> deque;
	deque.push_back(10);
	deque.push_back(20);
	deque.push_back(30);

	return deque.size() == 3 && deque[0] == 10 && deque[1] == 20 && deque[2] == 30;
}

bool testPushFront()
{
	deque<int> deque;
	deque.push_front(10);
	deque.push_front(20);
	deque.push_front(30);

	return deque.size() == 3 && deque[0] == 30 && deque[1] == 20 && deque[2] == 10;
}

bool testPopBack()
{
	deque<int> deque;
	deque.push_back(10);
	deque.push_back(20);
	deque.push_back(30);
	deque.pop_back();

	return deque.size() == 2 && deque[0] == 10 && deque[1] == 20;
}

bool testPopFront()
{
	deque<int> deque;
	deque.push_back(10);
	deque.push_back(20);
	deque.push_back(30);
	deque.pop_front();

	return deque.size() == 2 && deque[0] == 20 && deque[1] == 30;
}

bool testEmplaceBack()
{
	deque<std::string> deque;
	deque.emplace_back(3, 'a'); // Adds "aaa" to the back

	return deque.size() == 1 && deque[0] == "aaa";
}

bool testEmplaceFront()
{
	deque<std::string> deque;
	deque.emplace_front(3, 'b'); // Adds "bbb" to the front

	return deque.size() == 1 && deque[0] == "bbb";
}

bool testFrontBackAccess()
{
	deque<int> deque;
	deque.push_back(10);
	deque.push_back(20);
	deque.push_front(5);

	return deque.front() == 5 && deque.back() == 20;
}

bool testIsEmpty()
{
	deque<int> deque;
	return deque.empty();
}

bool testResize()
{
	deque<int> deque;
	for (int i = 0; i < 20; ++i)
	{
		deque.push_back(i);
	}
	bool success = true;
	for (int i = 0; i < 20; ++i)
	{
		success = success && deque[i] == i;
	}
	return success && deque.size() == 20;
}

bool testShrinkToFit()
{
	deque<int> deque;

	// Step 1: Add elements to exceed the initial currCapacity and trigger resize
	for (int i = 0; i < 20; ++i)
	{
		deque.push_back(i);
	}

	// Step 2: Remove a few elements to create extra currCapacity
	for (int i = 0; i < 10; ++i)
	{
		deque.pop_front();
	}

	// Step 3: Call shrink_to_fit to reduce currCapacity to match the current size
	size_t sizeBeforeShrink = deque.size();
	deque.shrink_to_fit();

	// Step 4: Check if the currCapacity matches the current size
	bool capacityMatchesSize = (deque.size() == sizeBeforeShrink && deque.capacity() == deque.size());

	// Step 5: Verify elements are in the correct order after shrinking
	bool elementsIntact = true;
	for (size_t i = 0; i < deque.size(); ++i)
	{
		if (deque[i] != i + 10) // Elements should be [10, 11, ..., 19] after popping
		{
			elementsIntact = false;
			break;
		}
	}

	if (!(capacityMatchesSize && elementsIntact))
		return false;

	// Step 6: Empty the whole deque then try shrink_to_fit
	// on an empty container.
	while (deque.size())
	{
		deque.pop_front();
	}
	deque.shrink_to_fit();
	if (deque.size() != 0)
		return false;

	deque.push_back(1);
	deque.push_back(2);
	deque.push_back(3);
	deque.push_back(4);

	if (deque.size() != 4 || deque.front() != 1 || deque.back() != 4)
		return false;

	return true;
}

bool testIteratorIncrement()
{
	deque<int> deque;
	deque.push_back(1);
	deque.push_back(2);
	deque.push_back(3);

	auto it = deque.begin();
	if (*it != 1)
		return false;

	it++;
	if (*it != 2)
		return false;

	++it;
	if (*it != 3)
		return false;

	return it == deque.end() - 1;
}

bool testIteratorDecrement()
{
	deque<int> deque;
	deque.push_back(1);
	deque.push_back(2);
	deque.push_back(3);

	auto it = deque.end() - 1;
	if (*it != 3)
		return false;

	it--;
	if (*it != 2)
		return false;

	--it;
	if (*it != 1)
		return false;

	return it == deque.begin();
}

bool testIteratorEquality()
{
	deque<int> deque;
	deque.push_back(10);
	deque.push_back(20);

	auto it1 = deque.begin();
	auto it2 = deque.begin();
	if (it1 != it2)
		return false;

	++it2;
	if (it1 == it2)
		return false;

	return true;
}

bool testConstIterator()
{
	deque<int> f_deque;
	f_deque.push_back(5);
	f_deque.push_back(15);
	f_deque.push_back(25);

	const deque<int>& constDeque = f_deque;
	auto it = constDeque.begin();

	if (*it != 5)
		return false;
	++it;
	if (*it != 15)
		return false;
	++it;
	if (*it != 25)
		return false;

	return it == constDeque.end() - 1;
}

bool testIteratorDereference()
{
	deque<int> deque;
	deque.push_back(100);
	deque.push_back(200);
	deque.push_back(300);

	auto it = deque.begin();
	if (*it != 100)
		return false;

	++it;
	if (*it != 200)
		return false;

	it++;
	if (*it != 300)
		return false;

	return true;
}

bool testCopyConstructor()
{
	deque<int> f_deque;
	f_deque.push_back(1);
	f_deque.push_back(2);
	f_deque.push_back(3);

	deque<int> copy(f_deque);

	if (f_deque.size() != copy.size())
		return false;

	while (copy.size())
	{
		if (copy.front() != f_deque.front())
			return false;
		copy.pop_front();
		f_deque.pop_front();
	}

	if (f_deque.size() != copy.size())
		return false;

	return true;
}

bool testMoveAndAssignment()
{
	constexpr size_t SIZE = 4;

	deque<int> d;

	for (size_t i = 0; i < SIZE; i++)
		d.push_back(i);

	deque<int> d1;
	d1 = d;

	for (size_t i = 0; i < d1.size(); i++)
		if (d1[i] != d[i])
			return false;

	deque<int> moved(std::move(d1));

	if (moved.size() != SIZE || d1.size() != 0)
		return false;

	d1 = std::move(moved);
	moved = std::move(d1);

	if (moved.size() != SIZE || d1.size() != 0)
		return false;

	for (size_t i = 0; i < d1.size(); i++)
		if (moved[i] != d[i])
			return false;

	while (moved.size())
	{
		if (moved.front() != d.front() || moved.back() != d.back())
			return false;
		moved.pop_back();
		d.pop_back();

		if (moved.empty() || d.empty())
			break;

		moved.pop_front();
		d.pop_front();
	}

	if (!moved.empty() || !d.empty())
		return false;

	return true;
}

bool resize_tests()
{
	deque<int> d;

	d.resize(10);

	d.resize(20);
	d.resize(15);

	d.emplace_back(1);
	d.emplace_back(2);
	d.emplace_back(3);
    d.emplace_front(0);

	if (d.size() != 4 || d.front() != 0 || d.back() != 3)
	{
		return false;
	}

    d.resize(30);

    if (d.size() != 4 || d.front() != 0 || d.back() != 3)
	{
		return false;
	}

    d.resize(4);

    if (d.size() != 4 || d.front() != 0 || d.back() != 3)
	{
		return false;
	}

    for (size_t i = 0; i < 100; i++)
    {
        d.push_back(i);
    }
    
    if(d.back() != 99 || d.size() != 104)
    {
        return false;
    }

    d.resize(10);

	return true;
}

int main()
{
	std::cout << "Test Push Back: " << (testPushBack() ? "PASSED" : "FAILED") << "\n";
	std::cout << "Test Push Front: " << (testPushFront() ? "PASSED" : "FAILED") << "\n";
	std::cout << "Test Pop Back: " << (testPopBack() ? "PASSED" : "FAILED") << "\n";
	std::cout << "Test Pop Front: " << (testPopFront() ? "PASSED" : "FAILED") << "\n";
	std::cout << "Test Emplace Back: " << (testEmplaceBack() ? "PASSED" : "FAILED") << "\n";
	std::cout << "Test Emplace Front: " << (testEmplaceFront() ? "PASSED" : "FAILED") << "\n";
	std::cout << "Test Front and Back Access: " << (testFrontBackAccess() ? "PASSED" : "FAILED") << "\n";
	std::cout << "Test Is Empty: " << (testIsEmpty() ? "PASSED" : "FAILED") << "\n";
	std::cout << "Test Resize: " << (testResize() ? "PASSED" : "FAILED") << "\n";
	std::cout << "Test Shrink To Fit: " << (testShrinkToFit() ? "PASSED" : "FAILED") << "\n";
	std::cout << "Test Iterator Increment: " << (testIteratorIncrement() ? "PASSED" : "FAILED") << "\n";
	std::cout << "Test Iterator Decrement: " << (testIteratorDecrement() ? "PASSED" : "FAILED") << "\n";
	std::cout << "Test Iterator Equality: " << (testIteratorEquality() ? "PASSED" : "FAILED") << "\n";
	std::cout << "Test Const Iterator: " << (testConstIterator() ? "PASSED" : "FAILED") << "\n";
	std::cout << "Test Iterator Dereference: " << (testIteratorDereference() ? "PASSED" : "FAILED") << "\n";
	std::cout << "Test Copy Cnstructor: " << (testCopyConstructor() ? "PASSED" : "FAILED") << "\n";
	std::cout << "Test Move Constructor And Assignment: " << (testMoveAndAssignment() ? "PASSED" : "FAILED") << "\n";
	std::cout << "Test resize: " << (resize_tests() ? "PASSED" : "FAILED") << "\n";

	return 0;
}