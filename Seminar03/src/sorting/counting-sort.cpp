#include <algorithm>
#include <iostream>
#include <vector>

void counting_sort(std::vector<int>& data)
{
	if (data.empty())
		return;

	auto min_max_pair = std::minmax_element(data.begin(), data.end());
	unsigned count_buffer_size = *min_max_pair.second - *min_max_pair.first + 1;

	// All elements are the same.
	if (count_buffer_size == 1)
		return;

	int lower = *min_max_pair.first;
	std::vector<int> count(count_buffer_size, 0);
	std::vector<int> copy(data);

	for (int number : data)
	{
		count[number - lower]++;
	}

	for (size_t i = 1; i < count.size(); i++)
	{
		count[i] += count[i - 1];
	}

	for (int i = copy.size() - 1; i >= 0; i--)
	{
		data[count[copy[i] - lower] - 1] = copy[i];
		--count[copy[i] - lower];
	}
}

int main()
{
	std::vector<int> numbers;
	unsigned size = rand() % 2000;
	numbers.resize(size);

	for (size_t i = 0; i < size; i++)
	{
		numbers[i] = rand() % 100;
	}

	counting_sort(numbers);

	std::cout << std::is_sorted(numbers.begin(), numbers.end()) << std::endl;
}