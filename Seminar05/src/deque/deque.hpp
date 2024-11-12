#pragma once
#include <memory>
#include <stdexcept>

template <class T, class Allocator = std::allocator<T>>
class deque
{
  private:
	T* _data = nullptr;

	size_t _size = 0;
	size_t _capacity = 0;

	size_t _head = 0;
	size_t _tail = 0;

	Allocator _allocator;

	void move_index(size_t& idx, bool forward) const;
	size_t calculate_capacity() const;

	void move(deque&& other) noexcept;
	void copy(const deque& other);
	void free();

  public:
	deque() = default;
	deque(const deque& other);
	deque(deque&& other) noexcept;

	deque& operator=(const deque& other);
	deque& operator=(deque&& other) noexcept;

	void push_back(const T& element);
	void push_front(const T& element);

	void pop_back();
	void pop_front();

	T& front();
	T& back();

    void shrink_to_fit();

	T& operator[](size_t idx);
	const T& operator[](size_t idx) const;

	void resize(size_t new_capacity);

	const T& front() const;
	const T& back() const;

	template <class... Args>
	void emplace_front(Args&&... args);

	template <class... Args>
	void emplace_back(Args&&... args);

	size_t size() const;
	size_t capacity() const;

	bool empty() const;

	class iterator
	{
		friend class deque;
		deque<T, Allocator>& _deque;
		size_t _index; // (not in the physical array)

		iterator(deque& deque, size_t index)
			: _deque(deque)
			, _index(index)
		{}

	  public:
		iterator& operator++(int)
		{
			_index++;
			return *this;
		}

		iterator operator++()
		{
			iterator old = *this;
			_index++;
			return old;
		}

		iterator& operator--(int)
		{
			_index--;
			return *this;
		}

		iterator operator--()
		{
			iterator old = *this;
			_index--;
			return old;
		}

		iterator operator+(int n)
		{
			return iterator(_deque, _index + n);
		}

		iterator operator-(int n)
		{
			return iterator(_deque, _index - n);
		}

		T& operator*()
		{
			return _deque[_index];
		}

		bool operator==(const iterator& other)
		{
			return _index == other._index;
		}
		bool operator!=(const iterator& other)
		{
			return _index != other._index;
		}
	};

	class const_iterator
	{
		friend class deque;
		const deque<T, Allocator>& _deque;
		size_t _index; // semantic index (not in the physical array)

		const_iterator(const deque<T, Allocator>& deque, int index)
			: _deque(deque)
			, _index(index)
		{}

	  public:
		const_iterator& operator++(int)
		{
			_index++;
			return *this;
		}

		const_iterator operator++()
		{
			const_iterator old = *this;
			_index++;
			return old;
		}

		const_iterator& operator--(int)
		{
			_index--;
			return *this;
		}

		const_iterator operator--()
		{
			const_iterator old = *this;
			_index--;
			return old;
		}

		const_iterator operator+(int n)
		{
			return const_iterator(_deque, _index + n);
		}

		const_iterator operator-(int n)
		{
			return const_iterator(_deque, _index - n);
		}

		const T& operator*() const
		{
			return _deque[_index];
		}

		bool operator==(const const_iterator& other)
		{
			return _index == other._index;
		}
		bool operator!=(const const_iterator& other)
		{
			return _index != other._index;
		}
	};

	deque::iterator begin()
	{
		return iterator(*this, 0);
	}

	deque::iterator end()
	{
		return iterator(*this, size());
	}

	deque::const_iterator begin() const
	{
		return const_iterator(*this, 0);
	}

	deque::const_iterator end() const
	{
		return const_iterator(*this, size());
	}

	~deque();
};

template <class T, class Allocator>
void deque<T, Allocator>::move_index(size_t& idx, bool forward) const
{
	if (forward)
	{
		++idx;
		idx %= _capacity;
	}
	else
	{
		idx = (idx == 0) ? (_capacity - 1) : idx - 1;
	}
}

template <class T, class Allocator>
deque<T, Allocator>::deque(const deque<T, Allocator>& other)
{
	copy(other);
}

template <class T, class Allocator>
deque<T, Allocator>::deque(deque<T, Allocator>&& other) noexcept
{
	move(std::move(other));
}

template <class T, class Allocator>
deque<T, Allocator>& deque<T, Allocator>::operator=(const deque<T, Allocator>& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}
	return *this;
}

template <class T, class Allocator>
deque<T, Allocator>& deque<T, Allocator>::operator=(deque<T, Allocator>&& other) noexcept
{
	if (this != &other)
	{
		free();
		move(std::move(other));
	}
	return *this;
}

template <class T, class Allocator>
void deque<T, Allocator>::push_back(const T& element)
{
	if (size() == capacity())
		resize(calculate_capacity());

	_allocator.construct(_data + _tail, element);
	move_index(_tail, true);
	++_size;
}

template <class T, class Allocator>
template <class... Args>
void deque<T, Allocator>::emplace_back(Args&&... args)
{
	if (size() == capacity())
		resize(calculate_capacity());

	_allocator.construct(_data + _tail, std::forward<Args>(args)...);
	move_index(_tail, true);
	++_size;
}

template <class T, class Allocator>
void deque<T, Allocator>::resize(size_t new_capacity)
{
    if(new_capacity == 0) new_capacity = calculate_capacity();

    T* new_data = _allocator.allocate(new_capacity);

    // If the current size is greater than `new_capacity`, 
    // the container is reduced to its first `new_capacity` elements.
    size_t elements_included = std::min(new_capacity, size());
	for (size_t i = 0; i < elements_included; i++)
	{
		_allocator.construct(new_data + i, std::move(operator[](i)));
		_allocator.destroy(_data + ((_head + i) % _capacity));
	}
    
	_allocator.deallocate(_data, _capacity);

	_head = 0;
	_tail = size() % new_capacity;
	_capacity = new_capacity;
	_data = new_data;    
}

template <class T, class Allocator>
void deque<T, Allocator>::shrink_to_fit()
{
    if (_capacity > _size)
	{
		if(_size == 0)
		{
			free();
			return;
		}
		
		resize(_size);
	} 
}

template <class T, class Allocator>
void deque<T, Allocator>::push_front(const T& element)
{
	if (size() == capacity())
		resize(calculate_capacity());

	move_index(_head, false);
	_allocator.construct(_data + _head, element);
	++_size;
}

template <class T, class Allocator>
template <class... Args>
void deque<T, Allocator>::emplace_front(Args&&... args)
{
	if (size() == capacity())
		resize(calculate_capacity());

	move_index(_head, false);
	_allocator.construct(_data + _head, std::forward<Args>(args)...);
	++_size;
}

template <class T, class Allocator>
void deque<T, Allocator>::pop_back()
{
	if (empty())
		throw std::out_of_range("Trying to pop_back on empty deque.");

	move_index(_tail, false);
	_allocator.destroy(_data + _tail);
	--_size;
}

template <class T, class Allocator>
void deque<T, Allocator>::pop_front()
{
	if (empty())
		throw std::out_of_range("Trying to pop_back on empty deque.");

	_allocator.destroy(_data + _head);
	move_index(_head, true);
	--_size;
}

template <class T, class Allocator>
T& deque<T, Allocator>::operator[](size_t idx)
{
	return _data[(_head + idx) % _capacity];
}
template <class T, class Allocator>
const T& deque<T, Allocator>::operator[](size_t idx) const
{
	return _data[(_head + idx) % _capacity];
}

template <class T, class Allocator>
void deque<T, Allocator>::copy(const deque<T, Allocator>& other)
{
	_data = _allocator.allocate(other.capacity());
	_capacity = other.capacity();

	for (size_t i = 0; i < other.size(); i++)
	{
		push_back(other[i]);
	}
}

template <class T, class Allocator>
T& deque<T, Allocator>::front()
{
	return _data[_head];
}

template <class T, class Allocator>
T& deque<T, Allocator>::back()
{
	unsigned last_element_idx = (_tail ? _tail : _capacity) - 1;
	return _data[last_element_idx];
}

template <class T, class Allocator>
const T& deque<T, Allocator>::front() const
{
	return _data[_head];
}

template <class T, class Allocator>
const T& deque<T, Allocator>::back() const
{
	unsigned last_element_idx = (_tail ? _tail : _capacity) - 1;
	return _data[last_element_idx];
}

template <class T, class Allocator>
void deque<T, Allocator>::move(deque<T, Allocator>&& other) noexcept
{
	_data = other._data;
	_size = other._size;
	_capacity = other._capacity;
	_head = other._head;
	_tail = other._tail;

	other._size = other._capacity = 0;
	other._head = other._tail = 0;
	other._data = nullptr;
}

template <class T, class Allocator>
void deque<T, Allocator>::free()
{
	while (_head != _tail)
	{
		_allocator.destroy(_data + _head);
		move_index(_head, true);
	}
	_allocator.deallocate(_data, capacity());
	_size = _capacity = 0;
	_data = nullptr;
}

template <class T, class Allocator>
deque<T, Allocator>::~deque()
{
	free();
}

template <class T, class Allocator>
size_t deque<T, Allocator>::calculate_capacity() const
{
	return empty() ? 1 : 2 * capacity();
}

template <class T, class Allocator>
size_t deque<T, Allocator>::size() const
{
    return _size;
}

template <class T, class Allocator>
size_t deque<T, Allocator>::capacity() const
{
    return _capacity;
}

template <class T, class Allocator>
bool deque<T, Allocator>::empty() const
{
    return _size == 0;
}