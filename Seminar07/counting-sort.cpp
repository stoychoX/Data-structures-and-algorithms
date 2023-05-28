#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>

void countingSort(std::vector<unsigned>& v) {
	unsigned elementRange = *std::max_element(v.begin(), v.end()) + 1;

	std::vector<unsigned> count(elementRange, 0);
	std::vector<unsigned> result(v.size());

	for (size_t i = 0; i < v.size(); i++)
		count[v[i]]++;

	for (size_t i = 1; i < elementRange; i++)
		count[i] += count[i - 1];

	for (int i = v.size() - 1; i >= 0; i--) {
		result[count[v[i]] - 1] = v[i];
		count[v[i]]--;
	}

	v = std::move(result);
}

int main() {
	std::vector<unsigned> v;
	const int length = 10000;

	for (size_t i = 0; i < length; i++)
		v.push_back(rand() * rand());

	countingSort(v);
	
	assert(std::is_sorted(v.begin(), v.end()));
	
	// for (int x : v) {
	// 	std::cout << x << " ";
	// }
}