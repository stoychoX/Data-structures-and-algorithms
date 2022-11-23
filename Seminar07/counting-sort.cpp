#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>

const int ELEMENTS_RANGE = 1000;

void countingSort(std::vector<int>& v) {
	std::vector<int> count(ELEMENTS_RANGE, 0);
	std::vector<int> result(v.size());

	for (size_t i = 0; i < v.size(); i++)
		count[v[i]]++;

	for (size_t i = 1; i < ELEMENTS_RANGE; i++)
		count[i] += count[i - 1];

	for (int i = v.size() - 1; i >= 0; i--) {
		result[count[v[i]] - 1] = v[i];
		count[v[i]]--;
	}

	v = std::move(result);
}

int main() {
	std::vector<int> v;
	const int length = 100000;

	for (size_t i = 0; i < length; i++)
		v.push_back(rand() % ELEMENTS_RANGE);

	countingSort(v);
	
	assert(std::is_sorted(v.begin(), v.end()));
	
	// for (int x : v) {
	// 	std::cout << x << " ";
	// }
}