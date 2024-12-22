#pragma once
#include <algorithm>
#include <list>
#include <vector>
#include <stdexcept>

template <class Key, class Value, class Hash = std::hash<Key>>
class separate_chaining_hashmap
{
  private:
	using pair_type = std::pair<Key, Value>;
	using pair_iterator_type = typename std::list<pair_type>::iterator;
	using bucket_type = std::list<pair_iterator_type>;

	// Keeps all the data inserten in the hashmap;
	std::list<pair_type> _data;
	std::vector<bucket_type> _hash_map;
	Hash _hash;
	double _load_factor;

	size_t get_hash_index(const Key& key) const
	{
		return _hash(key) % _hash_map.size();
	}

  public:
	separate_chaining_hashmap()
		: separate_chaining_hashmap(10, 0.75)
	{}

	separate_chaining_hashmap(size_t initial_capacity, double load_factor)
		: _hash_map(initial_capacity)
		, _load_factor(load_factor)
	{}

	void insert(const Key& key, const Value& value);

	const Value& find(const Key& key) const;
	Value& modify(const Key& key);

	void erase(const Key& key);

	// Return the number of elements in the hashmap.
	size_t size() const
	{
		return _data.size();
	}

	// Returns the load factor.
	double load_factor() const
	{
		return _load_factor;
	}

	// Return the number of buckets.
	size_t bucket_count() const
	{
		return _hash_map.size();
	}

	bool empty() const
	{
		return size() == 0;
	}

	void resize(size_t count);
};

template <class Key, class Value, class Hash>
void separate_chaining_hashmap<Key, Value, Hash>::insert(const Key& key, const Value& value)
{
	size_t current_index = get_hash_index(key);
	bucket_type& current_bucket = _hash_map[current_index];

	auto equal_key_iterator = std::find_if(current_bucket.begin(), current_bucket.end(),
		[&key](const pair_iterator_type& element) -> bool { return element->first == key; });
	
	if(equal_key_iterator != current_bucket.end())
	{
		(*equal_key_iterator)->second = value;
		return;
	}
	
	_data.push_back(std::make_pair(key, value));
	current_bucket.push_back(--_data.end());

	if(size() >= load_factor() * bucket_count())
	{
		resize(2 * bucket_count());
	}
}

template <class Key, class Value, class Hash>
const Value& separate_chaining_hashmap<Key, Value, Hash>::find(const Key& key) const
{
	size_t current_index = get_hash_index(key);
	bucket_type& current_bucket = _hash_map[current_index];

	auto equal_key_iterator = std::find_if(current_bucket.begin(), current_bucket.end(),
		[&key](const pair_iterator_type& element) -> bool { return element->first == key; });

	if(equal_key_iterator != current_bucket.end())
	{
		return (*equal_key_iterator)->second;
	}
	
	throw std::runtime_error("Element not found.");
}

template <class Key, class Value, class Hash>
Value& separate_chaining_hashmap<Key, Value, Hash>::modify(const Key& key)
{
	size_t current_index = get_hash_index(key);
	bucket_type& current_bucket = _hash_map[current_index];

	auto equal_key_iterator = std::find_if(current_bucket.begin(), current_bucket.end(),
		[&key](const pair_iterator_type& element) -> bool { return element->first == key; });

	if(equal_key_iterator != current_bucket.end())
	{
		return (*equal_key_iterator)->second;
	}
	
	throw std::runtime_error("Element not found.");
}

template <class Key, class Value, class Hash>
void separate_chaining_hashmap<Key, Value, Hash>::erase(const Key& key)
{
	size_t current_index = get_hash_index(key);
	bucket_type& current_bucket = _hash_map[current_index];

	auto equal_key_iterator = std::find_if(current_bucket.begin(), current_bucket.end(),
		[&key](const pair_iterator_type& element) -> bool { return element->first == key; });

	if(equal_key_iterator != current_bucket.end())
	{
		_data.erase(*equal_key_iterator);
		current_bucket.erase(equal_key_iterator);
	}
}

template <class Key, class Value, class Hash>
void separate_chaining_hashmap<Key, Value, Hash>::resize(size_t count)
{
	_hash_map.clear();
	_hash_map.resize(count);

	for(auto it = _data.begin(); it != _data.end(); ++it)
	{
		_hash_map[get_hash_index(it->first)].push_back(it);
	}
}
