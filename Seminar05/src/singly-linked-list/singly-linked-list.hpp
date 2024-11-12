#pragma once
#include <cstddef>
#include <utility>

template <typename T>
class singly_linked_list
{
private:
	struct node
	{
		T data;
		node* next;

		node(const T& data_, node* next_ = nullptr) :
            data(data_),
            next(next_) {}
	};

	node* _head = nullptr;
	node* _tail = nullptr;
	size_t _size = 0;
public:
	singly_linked_list() = default;
	singly_linked_list(const singly_linked_list<T>& other);
	singly_linked_list(singly_linked_list<T>&& other);
	singly_linked_list<T>& operator=(const singly_linked_list<T>& other);
	singly_linked_list<T>& operator=(singly_linked_list<T>&& other);
	~singly_linked_list();

	void push_front(const T& el);
	void push_back(const T& el);

	void pop_front();

	const T& front() const;
	const T& back() const;
	
	T& front(); 
	T& back();
	
	size_t size() const;
	bool empty() const;
	
	template <typename U>
	friend singly_linked_list<U> concat(singly_linked_list<U>& lhs, singly_linked_list<U>& rhs);
	
	class sll_iterator
	{
		node* currentElementPtr;

		friend class singly_linked_list;
	public:

		sll_iterator(node* currentElementPtr = nullptr) : currentElementPtr(currentElementPtr) {}

		T& operator*()
		{
			return currentElementPtr->data;
		}

		T* operator->()
		{
			return &currentElementPtr->data;
		}

		sll_iterator& operator++()
		{
			if (currentElementPtr)
				currentElementPtr = currentElementPtr->next;
			return *this;
		}

		sll_iterator operator++(int)
		{
			sll_iterator copy(*this);
			++(*this);
			return copy;
		}

		sll_iterator& operator+=(size_t s)
		{

			while (s--)
				++(*this);

			return *this;
		}

		sll_iterator operator+(int i) const
		{

			sll_iterator res(*this);
			return res += i;
		}

		bool operator==(const sll_iterator& rhs) const { return currentElementPtr == rhs.currentElementPtr; }
		bool operator!=(const sll_iterator& rhs) const { return !(rhs == *this); }

	};
	
	class const_sll_iterator
	{
		node* currentElementPtr;

		friend class singly_linked_list;
	public:		
		const_sll_iterator(const sll_iterator& nonConstIter) : currentElementPtr(nonConstIter.currentElementPtr) {}
		const_sll_iterator(node* currentElementPtr = nullptr) : currentElementPtr(currentElementPtr) {}

		const T& operator*() const
		{
			return currentElementPtr->data;
		}

		const T* operator->() const
		{
			return &currentElementPtr->data;
		}

		const_sll_iterator& operator++()
		{
			if (currentElementPtr)
				currentElementPtr = currentElementPtr->next;
			return *this;
		}

		const_sll_iterator operator++(int)
		{
			const_sll_iterator copy(*this);
			++(*this);
			return copy;
		}

		const_sll_iterator& operator+=(size_t s)
		{

			while (s--)
				++(*this);

			return *this;
		}

		const_sll_iterator operator+(int i) const
		{

			const_sll_iterator res(*this);
			return res += i;
		}

		bool operator==(const const_sll_iterator& rhs) const { return currentElementPtr == rhs.currentElementPtr; }
		bool operator!=(const const_sll_iterator& rhs) const { return !(rhs == *this); }

	};
	
	const_sll_iterator begin()
	{
		return sll_iterator(_head);
	}
	sll_iterator end()
	{
		return sll_iterator(nullptr);
	}
	
	const_sll_iterator cbegin() const
	{
		return const_sll_iterator(_head);
	}
	const_sll_iterator cend() const
	{
		return const_sll_iterator(nullptr);
	}
	
	sll_iterator insert_after(const T& element, const const_sll_iterator& it);
	sll_iterator remove_after(const const_sll_iterator& it);

private:
	void copy(const singly_linked_list<T>& other);
	void move(singly_linked_list<T>&& other);
	void free();
};

template <typename T>
void singly_linked_list<T>::push_front(const T& el)
{
	node* new_node = new node(el);

	if (empty())
	{
		_head = _tail = new_node;
	}
	else
	{
	 	new_node->next = _head;
	 	_head = new_node;   
	}
	_size++;

}
template <typename T>
void singly_linked_list<T>::push_back(const T& el)
{
	node* new_node = new node(el);

	if (empty())
	{
		_head = _tail = new_node;
	}
	else
	{
	    _tail->next = new_node;
	    _tail = new_node;
	}
	_size++;

}

template <typename T>
void singly_linked_list<T>::pop_front()
{
	if (empty())
		return;

	if (_head == _tail)
	{
		delete _head;
		_head = _tail = nullptr;
	}
	else
	{
	    node* to_delete = _head;
        _head = _head->next;
	    delete to_delete;
	}
    _size--;
}

template <typename T>
const T& singly_linked_list<T>::front() const
{
	return _head->data;
}

template <typename T>
const T& singly_linked_list<T>::back() const 
{
	return _tail->data;
}

template <typename T>
T& singly_linked_list<T>::front() 
{
	return _head->data;
}

template <typename T>
T& singly_linked_list<T>::back() 
{
	return _tail->data;
}

template <typename T>
singly_linked_list<T> concat(singly_linked_list<T>& lhs, singly_linked_list<T>& rhs)
{
	singly_linked_list<T> result;

	if (!lhs._head)
	{
		result._head = rhs._head;
		result._tail = rhs._tail;
	}
	else if (!rhs._head)
	{
		result._head = lhs._head;
		result._tail = lhs._tail;
	}
	else
	{
		lhs._tail->next = rhs._head;
		result._head = lhs._head;
		result._tail = rhs._tail;
	}
    result._size = rhs._size + lhs._size;
    rhs._size = lhs._size = 0;
	rhs._head = rhs._tail = lhs._head = lhs._tail = nullptr;

	return result;
}

template <typename T>
typename singly_linked_list<T>::sll_iterator singly_linked_list<T>::insert_after(const T& element, const typename singly_linked_list<T>::const_sll_iterator& it)
{
    if(it == end())
        return end();
        
	node* new_node = new node(element);
	node* itNode = it.currentElementPtr;

	new_node->next = itNode->next;
	itNode->next = new_node;
    _size++;
	return singly_linked_list<T>::sll_iterator(new_node);
}


template <typename T>
typename singly_linked_list<T>::sll_iterator singly_linked_list<T>::remove_after(const typename singly_linked_list<T>::const_sll_iterator& it)
{
    if(it == end() || size() == 1)
        return end();
        
	node* to_delete = (it + 1).currentElementPtr;

	node* new_next = to_delete->next;

	it.currentElementPtr->next = new_next;
	_size--;
	
	if(to_delete == _tail)
	{
	    _tail = it.currentElementPtr;
	}
	
	delete to_delete;
	
	return singly_linked_list<T>::sll_iterator(new_next);
}

template <typename T>
bool singly_linked_list<T>::empty() const
{
    return size() == 0;
}

template <typename T>
size_t singly_linked_list<T>::size() const
{
    return _size;
}

template <typename T>
singly_linked_list<T>::singly_linked_list(const singly_linked_list<T>& other) 
{
	copy(other);
}


template <typename T>
singly_linked_list<T>::singly_linked_list(singly_linked_list<T>&& other) 
{
	move(std::move(other));
}

template <typename T>
singly_linked_list<T>& singly_linked_list<T>::operator=(const singly_linked_list<T>& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}

	return *this;
}

template <typename T>
singly_linked_list<T>& singly_linked_list<T>::operator=(singly_linked_list<T>&& other)
{
	if (this != &other)
	{
		free();
		move(std::move(other));
	}

	return *this;
}
template <typename T>
singly_linked_list<T>::~singly_linked_list()
{
	free();
}

template <typename T>
void singly_linked_list<T>::copy(const singly_linked_list<T>& other)
{
	node* iter = other._head;

	while (iter)
	{
		push_back(iter->data);
		iter = iter->next;
	}
}

template <typename T>
void singly_linked_list<T>::move(singly_linked_list<T>&& other)
{
    _head = other._head;
    _tail = other._tail;
	_size = other.size();

    other._head = other._tail = nullptr;
	other._size = 0;
}

template <typename T>
void singly_linked_list<T>::free()
{
	node* iter = _head;

	while (iter)
	{
		node* to_delete = iter;
		iter = iter->next;
		delete to_delete;
	}
	_head = _tail = nullptr;
	_size = 0;
}