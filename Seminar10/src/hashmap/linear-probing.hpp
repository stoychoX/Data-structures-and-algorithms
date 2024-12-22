#pragma once
#include <stdexcept>
#include <vector>

template <class Key, class Value, class Hash = std::hash<Key>>
class linear_probing_hashmap
{
  private:
	using pair_type = std::pair<Key, Value>;

	struct node
	{
		pair_type data;
		bool empty = true;
		bool deleted = false;

		// TODO: This might be wasteful.
		node() = default;

		node(const Key& key, const Value& value)
			: data(std::make_pair(key, value))
		{}
	};

	std::vector<node> _data;
	Hash _hash;
	double _load_factor;
	size_t _size = 0;
	size_t _jump_value = 1;

	size_t get_hash_index(const Key& key) const
	{
		return _hash(key) % bucket_count();
	}

	void increment_index(size_t& index, size_t max_size) const
	{
		index += _jump_value;

		// TODO: empty?
		if (index >= max_size)
			index %= max_size;
	}

	size_t get_iterations_needed() const
	{
		return _data.size();
	}

  public:
	linear_probing_hashmap(size_t initial_capacity, double load_factor, size_t jump_value = 1)
		: _data(initial_capacity)
		, _load_factor(load_factor)
		, _jump_value(jump_value)
	{}

	linear_probing_hashmap()
		: linear_probing_hashmap(10, 0.75)
	{}

	void insert(const Key& key, const Value& value);

	const Value& find(const Key& key) const;
	Value& modify(const Key& key);

	void erase(const Key& key);

	void resize(size_t count);

	size_t size() const
	{
		return _size;
	}

	bool empty() const
	{
		return _size == 0;
	}

	size_t bucket_count() const
	{
		return _data.size();
	}

	double max_load_factor() const
	{
		return _load_factor;
	}
};

template <class Key, class Value, class Hash>
void linear_probing_hashmap<Key, Value, Hash>::insert(const Key& key, const Value& value)
{
	size_t current_index = get_hash_index(key);
	size_t iterations_needed = get_iterations_needed();

	for (size_t i = 0; i < iterations_needed; i++)
	{
		node& current_node = _data[current_index];

		// Element is contained in the collection.
		if (!current_node.empty && !current_node.deleted && current_node.data.first == key)
		{
			current_node.data.second = value;
			return;
		}

		// We don't need to check for deleted flag here.
		if (current_node.empty)
		{
			current_node = node(key, value);
			current_node.empty = false;
			current_node.deleted = false;

			++_size;

			if (size() >= bucket_count() * max_load_factor())
			{
				resize(2 * bucket_count());
			}

			return;
		}
		increment_index(current_index, _data.size());
	}
	throw std::runtime_error("Numbers are not co-prime!");
}

template <class Key, class Value, class Hash>
const Value& linear_probing_hashmap<Key, Value, Hash>::find(const Key& key) const
{
	size_t current_index = get_hash_index(key);
	size_t iterations_needed = get_iterations_needed();

	for (size_t i = 0; i < iterations_needed; i++)
	{
		const node& current_node = _data[current_index];

		if (current_node.empty && !current_node.deleted)
		{
			break;
		}

		if (!current_node.empty && !current_node.deleted && current_node.data.first == key)
		{
			return current_node.data.second;
		}

		increment_index(current_index, _data.size());
	}

	throw std::out_of_range("[linear_probing_hashmap]: Element not found.");
}

template <class Key, class Value, class Hash>
Value& linear_probing_hashmap<Key, Value, Hash>::modify(const Key& key)
{
	size_t current_index = get_hash_index(key);
	size_t iterations_needed = get_iterations_needed();

	for (size_t i = 0; i < iterations_needed; i++)
	{
		node& current_node = _data[current_index];

		if (current_node.empty && !current_node.deleted)
		{
			break;
		}

		if (!current_node.empty && !current_node.deleted && current_node.data.first == key)
		{
			return current_node.data.second;
		}

		increment_index(current_index, _data.size());
	}

	throw std::out_of_range("[linear_probing_hashmap]: Element not found.");
}

template <class Key, class Value, class Hash>
void linear_probing_hashmap<Key, Value, Hash>::erase(const Key& key)
{
	size_t current_index = get_hash_index(key);
	size_t iterations_needed = get_iterations_needed();

	for (size_t i = 0; i < iterations_needed; i++)
	{
		node& current_node = _data[current_index];
		
		if (current_node.empty && !current_node.deleted)
		{
			break;
		}

		if (current_node.data.first == key)
		{
			current_node.deleted = true;
			current_node.empty = true;
			break;
		}

		increment_index(current_index, _data.size());
	}
}

template <class Key, class Value, class Hash>
void linear_probing_hashmap<Key, Value, Hash>::resize(size_t count)
{
	// TODO: Ensure count is big enough.
	std::vector<node> new_data(count);

	for (const auto& current_element : _data)
	{
		if (current_element.empty)
			continue;

		size_t current_index = _hash(current_element.data.first) % new_data.size();
		size_t iterations_needed = new_data.size();

		for (size_t i = 0; i < iterations_needed; i++)
		{
			node& current_node = new_data[current_index];

			if (current_node.empty)
			{
				current_node = current_element;
				break;
			}

			increment_index(current_index, new_data.size());
		}
	}

	_data = std::move(new_data);
}
