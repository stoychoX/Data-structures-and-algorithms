#pragma once
#include <stddef.h>
#include <utility>

template <class T>
class doubly_linked_list
{
  private:
	struct node
	{
		T data;
		node* prev;
		node* next;

		node(const T& data_, node* prev_ = nullptr, node* next_ = nullptr)
			: data(data_)
			, prev(prev_)
			, next(next_)
		{}

		node(T&& data_, node* prev_ = nullptr, node* next_ = nullptr)
			: data(std::move(data_))
			, prev(prev_)
			, next(next_)
		{}
	};

	class const_dll_iterator
	{
	  public:
		const_dll_iterator(const doubly_linked_list& list, node* node)
			: _node(node)
			, _list(list)
		{}

		const_dll_iterator& operator++()
		{
			_node = _node->next;
			return *this;
		}

		const_dll_iterator operator++(int)
		{
			const_dll_iterator copy(*this);
			++(*this);
			return copy;
		}

		const_dll_iterator& operator--()
		{
			// --end()
			if (_node == nullptr)
			{
				_node = _list._tail;
			}
			else
			{
				_node = _node->prev;
			}
			return *this;
		}

		const_dll_iterator operator--(int)
		{
			const_dll_iterator copy(*this);
			--(*this);
			return copy;
		}

		const T& operator*() const
		{
			return _node->data;
		}

		const T* operator->() const
		{
			return &_node->data;
		}

		bool operator!=(const const_dll_iterator& other) const
		{
			return (_node != other._node);
		}

		bool operator==(const const_dll_iterator& other) const
		{
			return !(*this != other);
		}

	  private:
		node* _node;
		const doubly_linked_list& _list;

		friend class doubly_linked_list;
	};

	class dll_iterator
	{
	  public:
		dll_iterator(doubly_linked_list& list, node* node)
			: _node(node)
			, _list(list)
		{}

		dll_iterator& operator++()
		{
			_node = _node->next;
			return *this;
		}

		dll_iterator operator++(int)
		{
			dll_iterator copy(*this);
			++(*this);
			return copy;
		}

		dll_iterator& operator--()
		{
			// --end()
			if (_node == nullptr)
			{
				_node = _list._tail;
			}
			else
			{
				_node = _node->prev;
			}
			return *this;
		}

		dll_iterator operator--(int)
		{
			dll_iterator copy(*this);
			--(*this);
			return copy;
		}

		T& operator*()
		{
			return _node->data;
		}

		T* operator->()
		{
			return &_node->data;
		}

		bool operator!=(const dll_iterator& other) const
		{
			return (_node != other._node);
		}

		bool operator==(const dll_iterator& other) const
		{
			return !(*this != other);
		}

		operator const_dll_iterator() const
		{
			return const_dll_iterator(_list, _node);
		}

	  private:
		node* _node;
		doubly_linked_list& _list;

		friend class doubly_linked_list;
	};

  public:
	using iterator = dll_iterator;
	using const_iterator = const_dll_iterator;

	doubly_linked_list() = default;

	doubly_linked_list(const doubly_linked_list& other);
	doubly_linked_list(doubly_linked_list&& other) noexcept;

	void push_back(const T& data);
	void push_front(const T& data);
	iterator insert(const_iterator position, const T& value);
	iterator remove(const_iterator position);

	void pop_back();
	void pop_front();

	doubly_linked_list& operator=(const doubly_linked_list& other);
	doubly_linked_list& operator=(doubly_linked_list&& other) noexcept;

	size_t size() const
	{
		return _size;
	}
	bool empty() const
	{
		return _size == 0;
	}

	T& front()
	{
		return _head->data;
	}
	const T& front() const
	{
		return _head->data;
	}

	T& back()
	{
		return _tail->data;
	}
	const T& back() const
	{
		return _tail->data;
	}

	// iterators
	iterator begin()
	{
		return iterator(*this, _head);
	}
	iterator end()
	{
		return iterator(*this, nullptr);
	}

	const_iterator begin() const
	{
		return conmnst_iterator(*this, _head);
	}
	const_iterator end() const
	{
		return const_iterator(*this, nullptr);
	}

	~doubly_linked_list();

  private:
	void copy(const doubly_linked_list& other);
	void move(doubly_linked_list&& other) noexcept;
	void free();

	node* _head = nullptr;
	node* _tail = nullptr;
	size_t _size = 0;
};

template <class T>
doubly_linked_list<T>::doubly_linked_list(const doubly_linked_list& other)
{
	copy(other);
}

template <class T>
doubly_linked_list<T>::doubly_linked_list(doubly_linked_list&& other) noexcept
{
	move(std::move(other));
}

template <class T>
doubly_linked_list<T>& doubly_linked_list<T>::operator=(const doubly_linked_list& other)
{
	if(this != &other)
	{
		free();
		copy(other);
	}
	return *this;
}

template <class T>
doubly_linked_list<T>& doubly_linked_list<T>::operator=(doubly_linked_list&& other) noexcept
{
	if(this != &other)
	{
		free();
		move(std::move(other));
	}
	return *this;
}

template <class T>
void doubly_linked_list<T>::push_back(const T& data)
{
	node* new_tail = new node(data);
	if (empty())
	{
		_head = _tail = new_tail;
	}
	else
	{
		new_tail->prev = _tail;
		_tail->next = new_tail;
		_tail = new_tail;
	}
	++_size;
}

template <class T>
void doubly_linked_list<T>::push_front(const T& data)
{
	node* new_head = new node(data);
	if (empty())
	{
		_head = _tail = new_head;
	}
	else
	{
		new_head->next = _head;
		_head->prev = new_head;
		_head = new_head;
	}
	++_size;
}

template <class T>
typename doubly_linked_list<T>::iterator doubly_linked_list<T>::insert(const_iterator position, const T& data)
{
	node* new_node = new node(data);

	if (position == begin())
	{
		push_front(data);
		return begin();
	}
	if (position == end())
	{
		push_back(data);
		return --end();
	}

	node* current_node = position._node;
	new_node->next = current_node;
	new_node->prev = current_node->prev;

	current_node->prev->next = new_node;
	current_node->prev = new_node;
	++_size;

	return iterator(*this, new_node);
}

template <class T>
void doubly_linked_list<T>::pop_back()
{
	if (empty())
		return;

	--_size;

	if (_head == _tail)
	{
		delete _tail;
		_tail = _head = nullptr;
		return;
	}

	node* old_tail = _tail;
	_tail->prev->next = nullptr;
	_tail = _tail->prev;

	delete old_tail;
}

template <class T>
void doubly_linked_list<T>::pop_front()
{
	if (empty())
		return;

	--_size;

	if (_head == _tail)
	{
		delete _head;
		_tail = _head = nullptr;
		return;
	}

	node* old_head = _head;
	_head->next->prev = nullptr;
	_head = _head->next;

	delete old_head;
}

template <class T>
typename doubly_linked_list<T>::iterator doubly_linked_list<T>::remove(const_iterator position)
{
	if (empty() || position == end())
		return end();

	if (position == begin())
	{
		pop_front();
		return begin();
	}

	if (position == --end())
	{
		pop_back();
		return end();
	}
	--_size;

	node* to_delete = position._node;
	node* to_return = to_delete->next;

	to_delete->prev->next = to_delete->next;
	to_delete->next->prev = to_delete->prev;

	delete to_delete;

	return iterator(*this, to_return);
}

template <class T>
void doubly_linked_list<T>::copy(const doubly_linked_list<T>& other)
{
	node* it = other._head;
	while (it != nullptr)
	{
		push_back(it->data);
		it = it->next;
	}
}

template <class T>
void doubly_linked_list<T>::move(doubly_linked_list<T>&& other) noexcept
{
	_head = other._head;
	_tail = other._tail;
	_size = other.size();

	other._head = other._tail = nullptr;
	other._size = 0;
}

template <class T>
void doubly_linked_list<T>::free()
{
	node* it = _head;
	while (it != nullptr)
	{
		node* to_delete = it;
		it = it->next;
		delete to_delete;
	}
	_size = 0;
	_head = _tail = nullptr;
}

template<class T>
doubly_linked_list<T>::~doubly_linked_list()
{
	free();
}