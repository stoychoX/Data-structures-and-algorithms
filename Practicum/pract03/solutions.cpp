#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

//Task 1
void orderByFirstLetter(vector<string>& words)
{
	auto first = words.begin();
	auto last = words.end();

	for (char letter = 'a'; letter <= 'z'; letter++)
	{
		auto new_beg = partition(first, last, [letter](const string& str) { return str[0] == letter; });
		first = new_beg;
	}
}

//Task 2
bool isEven(int n)
{
	return n % 2 == 0;
}

bool isOdd(int n)
{
	return n % 2;
}

template <class Pred>
void mergeSortedPred(vector<int>& res, const vector<int>& first, const vector<int>& second, Pred p)
{
	auto beg1 = first.begin();
	auto beg2 = second.begin();

	auto end1 = first.end();
	auto end2 = second.end();

	while (beg1 != end1 && beg2 != end2)
	{
		if (p(*beg1) && p(*beg2))
		{
			if (*beg1 <= *beg2)
			{
				res.push_back(*beg1);
				++beg1;
			}
			else
			{
				res.push_back(*beg2);
				++beg2;
			}
		} 
		else
		{
			if (!p(*beg1))
				++beg1;

			if (!p(*beg2))
				++beg2;
		}
	}

	while (beg1 != end1)
	{
		if (p(*beg1))
			res.push_back(*beg1);

		++beg1;
	}

	while (beg2 != end2)
	{
		if (p(*beg2))
			res.push_back(*beg2);

		++beg2;
	}
}
vector<int> mergeSortedEvensAndOdds(const vector<int>& first, const vector<int>& second)
{
	vector<int> res;
	mergeSortedPred(res, first, second, isEven);
	mergeSortedPred(res, first, second, isOdd);

	return res;
}

int main()
{
	//task 1
	vector<string> v = { "banana", "apple", "alpaca", "cat", "biscuit", "elephant", "string", "house", "progress", "trousers", "mouse" };
	orderByFirstLetter(v);

	for (auto it = v.begin(); it != v.end(); ++it)
		cout << *it << " ";

	//task 2
	vector<int> v1 = { 1, 2, 3, 4, 5 };
	vector<int> v2 = { 5, 17, 32, 80, 81, 82, 83 };

	vector<int> res = mergeSortedEvensAndOdds(v1, v2);

	for (auto it = res.begin(); it != res.end(); ++it)
		std::cout << *it << " ";
}
