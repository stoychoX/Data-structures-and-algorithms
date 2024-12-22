#include "linear-probing.hpp"
#include "separate-chaining.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <map>

std::vector<std::string> get_words(const std::string& file)
{
	std::vector<std::string> words;
	std::ifstream ifs("harry.txt");

	if (!ifs.is_open())
	{
		std::cout << "File retrieval failed" << std::endl;
		return {};
	}

	while (!ifs.eof())
	{
		std::string word;
		ifs >> word;
		words.emplace_back(word);
	}

	return words;
}

void test_hashmap_separate_chaining(size_t initial_capacity, double lf)
{
	std::cout << "[Separate chaining tests]: Running test for " << initial_capacity << " initial capacity and " << lf
			  << " load factor." << std::endl;

	separate_chaining_hashmap<std::string, int> mp;
	std::vector<std::string> words = get_words("harry.txt");

	std::cout << "[Separate chaining tests]: Parsed " << words.size() << " words in std::vector." << std::endl;

    unsigned dict_size = 0;
	auto begin = std::chrono::high_resolution_clock::now();
	for (const auto& word : words)
	{
		try
		{
			++mp.modify(word);
		}
		catch (...)
		{
            ++dict_size;
			mp.insert(word, 1);
		}
	}

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

	std::cout << "[Separate chaining tests]: Parsed " << words.size() << " words in separate_chaining_hashmap<std::string, int>."
			  << std::endl;
	std::cout << "[Separate chaining tests]: Dict size: " << dict_size << std::endl;
	std::cout << "[Separate chaining tests]: Buckets count: " << mp.bucket_count() << std::endl;
	std::cout << "[Separate chaining tests]: Size: " << mp.size() << std::endl;
	std::cout << "[Separate chaining tests]: Time: " << duration << " ms." << std::endl;
}

void test_hashmap_linear_probing(size_t jump_value, size_t initial_capacity, double lf)
{
    std::cout << "[Linear probing tests]: Running test for " << initial_capacity << " initial capacity and " << lf
			  << " load factor and " << jump_value << " as jump value." << std::endl;

	linear_probing_hashmap<std::string, int> mp(initial_capacity, lf, jump_value);
	std::vector<std::string> words = get_words("harry.txt");

	std::cout << "[Linear probing tests]: Parsed " << words.size() << " words in std::vector." << std::endl;

    int dict_size = 0;
	auto begin = std::chrono::high_resolution_clock::now();
	for (const auto& word : words)
	{
		try
		{
			++mp.modify(word);
		}
		catch (...)
		{
            ++dict_size;
			mp.insert(word, 1);
		}
	}

	auto end = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

	std::cout << "[Linear probing tests]: Parsed " << words.size() << " words in linear_probing_hashmap<std::string, int>."
			  << std::endl;
	std::cout << "[Linear probing tests]: Dict size: " << dict_size << std::endl;
	std::cout << "[Linear probing tests]: Buckets count: " << mp.bucket_count() << std::endl;
	std::cout << "[Linear probing tests]: Size: " << mp.size() << std::endl;
	std::cout << "[Linear probing tests]: Time: " << duration << " ms." << std::endl;
}


void test_hashmap_std()
{
	std::unordered_map<std::string, int> mp;
	std::vector<std::string> words = get_words("harry.txt");

	std::cout << "[std::unordered_map tests]: Parsed " << words.size() << " words in std::vector." << std::endl;

	auto begin = std::chrono::high_resolution_clock::now();
	for (const auto& word : words)
	{
		++mp[word];
	}

	auto end = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

	std::cout << "[std::unordered_map tests]: Parsed " << words.size() << " words in std::unordered_map<std::string, int>."
			  << std::endl;

	std::cout << "[std::unordered_map tests]: Buckets count: " << mp.bucket_count() << std::endl;
	std::cout << "[std::unordered_map tests]: Size: " << mp.size() << std::endl;
	std::cout << "[std::unordered_map tests]: Time: " << duration << " ms." << std::endl;
}

void test_map_std()
{
	std::map<std::string, int> mp;
	std::vector<std::string> words = get_words("harry.txt");

	std::cout << "[std::map tests]: Parsed " << words.size() << " words in std::vector." << std::endl;

	auto begin = std::chrono::high_resolution_clock::now();
	for (const auto& word : words)
	{
		++mp[word];
	}

	auto end = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

	std::cout << "[std::map tests]: Parsed " << words.size() << " words in std::map<std::string, int>."
			  << std::endl;

	std::cout << "[std::map tests]: Size: " << mp.size() << std::endl;
	std::cout << "[std::map tests]: Time: " << duration << " ms." << std::endl;
}

int main()
{
	test_hashmap_separate_chaining(1000, 0.7);

	std::cout << std::endl;

	test_hashmap_linear_probing(1, 997, 0.7);

	std::cout << std::endl;

    test_hashmap_std();

	std::cout << std::endl;

	test_map_std();
}