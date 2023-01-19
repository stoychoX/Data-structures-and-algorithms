#ifndef SEPARATE_CHAINING_HASH
#define SEPARATE_CHAINING_HASH

#include<functional> // std::hash
#include<list>
#include<vector>

template<class Key, class Value, class Hash = std::hash<Key>>
class SCHash {
private:
	using pair_type = std::pair<Key, Value>;
	using bucket = std::list<pair_type>;
	using container = std::vector<bucket>;
	using bucketIterator = typename container::iterator;
	using bucketConstIterator = typename container::const_iterator;

	container table;
	size_t elementsCount;
	Hash hash;

	size_t getIndex(const Key& key) const {
		return hash(key) % table.size();
	}

	bool shouldResize() const {
		return ((float)(elementsCount) / table.size()) > 0.7f;
	}

	bucketIterator getBucket(const Key& k) {
		return (table.begin() + getIndex(k));
	}

	bucketConstIterator getBucket(const Key& k) const {
		return (table.begin() + getIndex(k));
	}

	void resize() {
		container newTable(2 * table.size());
		table.swap(newTable);

		for (bucket& currentBucket : newTable) {
			for (pair_type& element : currentBucket) {
				getBucket(element.first)->push_back({ element.first, element.second });
			}

			// Освобождаваме паметта от кофата, вече няма да ни трябва.
			currentBucket.clear();
		}
	}

public:

	SCHash(Hash h = Hash()) : elementsCount{ 0 }, table(32), hash(h) {}

	void clear() {
		elementsCount = 0;
		table = container(32);
	}

	void insert(const Key& k, const Value& v) {
		if (shouldResize()) {
			resize();
		}

		bucketIterator currentBucket = getBucket(k);

		++elementsCount;

		for (auto& currentPair : *currentBucket) {
			if (currentPair.first == k) {
				currentPair.second = v;
				return;
			}
		}
		currentBucket->insert(currentBucket->end(), { k, v });
	}

	Value find(const Key& k) const {
		const auto& currentBucket = getBucket(k);

		for (const auto& currentPair : *currentBucket) {
			if (currentPair.first == k) {
				return currentPair.second;
			}
		}

		throw "Key not found!";
	}

	void erase(const Key& k) {
		auto currentBucket = getBucket(k);

		for (auto it = currentBucket->begin(); it != currentBucket->end(); ++it) {
			if (it->first == k) {
				currentBucket->erase(it);
				return;
			}
		}
	}

	size_t size() const {
		return elementsCount;
	}

    bool empty() const {
        return elementsCount == 0;
    }
};

#endif