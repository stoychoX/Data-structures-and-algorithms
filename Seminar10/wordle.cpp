#include<iostream>
#include<map>
#include<string>

int determineChar(const std::multimap<char, int>& mp, size_t idx, char currChar) {
    // find връща end ако не го намери
	auto currentIterator = mp.find(currChar);

	if (currentIterator == mp.end())
		return 0;

    // Докато не стигнем края, което е възможно, 
    // и докато все още сме на този символ
	while (currentIterator != mp.end() && currentIterator->first == currChar) {
		if (currentIterator->second == idx)
			return 2;
		++currentIterator;
	}

	return 1;
}

int main() {
	std::string word;
	std::cout << "Enter word to guess: " << std::endl;
	
    std::getline(std::cin, word, '\n');
	std::multimap<char, int> wordle;

	for (size_t i = 0; i < word.size(); i++)
		wordle.insert({ word[i], i });
	
	bool guessed = false;

	while (!guessed) {
		std::cout << "Enter guess with length: " << wordle.size() << std::endl;
		std::getline(std::cin, word, '\n');

		if (word.length() != wordle.size()) {
			std::cout << "Invalid length" << std::endl;
			continue;
		}

		guessed = true;

		for (size_t i = 0; i < word.size(); i++) {
			int result = determineChar(wordle, i, word[i]);
			
			std::cout << word[i] << " " << result << std::endl;

			if (result != 2)
				guessed = false;
		}
	}
}