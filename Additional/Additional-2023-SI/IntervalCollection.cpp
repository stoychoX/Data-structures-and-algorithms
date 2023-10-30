#include <iostream>
#include <vector>
#include <algorithm>

class IntervalCollection
{
	using Iterator = std::vector<std::pair<int, int>>::iterator;
	using ConstIterator = std::vector<std::pair<int, int>>::const_iterator;

	Iterator getRightmostInterval(int x)
	{
		std::pair<int, int> searcher = { x, x };
		return std::lower_bound(
			intervals.begin(),
			intervals.end(),
			searcher,
			[](const std::pair<int, int>& first, const std::pair<int, int>& second) -> bool
			{
				return first.second < second.second;
			}
		);
	}
	
	ConstIterator getRightmostIntervalConst(int x) const
	{
		std::pair<int, int> searcher = { x, x };
		return std::lower_bound(
			intervals.begin(),
			intervals.end(),
			searcher,
			[](const std::pair<int, int>& first, const std::pair<int, int>& second) -> bool
			{
				return first.second < second.second;
			}
		);
	}

public:
	void insert(int x)
	{
		Iterator right = getRightmostInterval(x);
		bool begin = (right == intervals.begin());

		Iterator left = begin ? intervals.end() : right - 1;

		bool needLeftMerge = !begin && (x - 1 == left->second);
		bool needRightMerge = (right != intervals.end()) && (x + 1 == right->first);

		if (right != intervals.end() && x >= right->first && x <= right->second)
		{
			return;
		}

		if (needLeftMerge && needRightMerge)
		{
			left->second = right->second;
			intervals.erase(right);
		}
		else if (needLeftMerge)
		{
			left->second = x;
		}
		else if (needRightMerge)
		{
			right->first = x;
		}
		else
		{
			intervals.insert(right, { x, x });
		}
	}

	bool contains(int x) const
	{
		ConstIterator right = getRightmostIntervalConst(x);
		return (right != intervals.end() && x >= right->first && x <= right->second);
	}

	void print() const
	{
		for (const auto& x : intervals)
		{
			std::cout << x.first << " " << x.second << std::endl;
		}
	}
private:
	std::vector<std::pair<int, int>> intervals;
};

int main()
{
	IntervalCollection ic;

	ic.insert(1);
	ic.insert(3);
	ic.insert(2);
	ic.insert(5);
	ic.insert(7);
	ic.insert(4);
	ic.insert(6);

	std::cout << ic.contains(1) << " " << ic.contains(10);
}