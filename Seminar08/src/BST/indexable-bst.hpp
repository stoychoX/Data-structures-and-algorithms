#pragma once
#include <functional>
#include <iostream>
#include <stack>
#include <vector>

template <class T, typename Compare = std::less<T>>
class Bst
{
  private:
	struct Node
	{
		T data;
		Node* left;
		Node* right;
        size_t size;
		Node(const T& data, Node* left = nullptr, Node* right = nullptr)
			: data(data)
			, left(left)
			, right(right)
            , size(1)
		{}
	};

	Node* root = nullptr;
	Compare comp; // comparator instance

	Node** findMinNode(Node** root, std::stack<Node*>& toDecrease);
	void free(Node* current);
	Node* copy(Node* current);

    const T& indexRec(Node* root, unsigned idx) const;
  public:
	Bst() = default;
	explicit Bst(const Compare& comparator)
		: comp(comparator)
	{}
	Bst(const Bst<T, Compare>& other);
	Bst<T, Compare>& operator=(const Bst<T, Compare>& other);
	~Bst();

	bool insert(const T& data);
	bool contains(const T& data) const;
	bool remove(const T& data);

	size_t getSize() const;
	bool isEmpty() const;

    const T& index(unsigned idx) const;

	class ForwardIterator
	{
	  private:
		std::stack<Node*> nodeStack;

		void pushLeft(Node* node)
		{
			while (node)
			{
				nodeStack.push(node);
				node = node->left;
			}
		}

	  public:
		ForwardIterator(Node* root = nullptr)
		{
			pushLeft(root);
		}

		T& operator*() const
		{
			return nodeStack.top()->data;
		}

		ForwardIterator& operator++()
		{
			Node* node = nodeStack.top();
			nodeStack.pop();
			if (node->right)
			{
				pushLeft(node->right);
			}
			return *this;
		}
		ForwardIterator operator++(int)
		{
			ForwardIterator old = *this;
			++(*this);
			return old;
		}

		bool operator!=(const ForwardIterator& other) const
		{
			return nodeStack != other.nodeStack;
		}

		bool operator==(const ForwardIterator& other) const
		{
			return nodeStack == other.nodeStack;
		}
	};

	ForwardIterator begin() const
	{
		return ForwardIterator(root);
	}

	ForwardIterator end() const
	{
		return ForwardIterator(nullptr);
	}
};

template <class T, typename Compare>
bool Bst<T, Compare>::insert(const T& data)
{
	Node** current = &root;
    std::stack<Node*> toIncrease;
	while (*current)
	{
        toIncrease.push(*current);

		if (comp(data, (*current)->data))
			current = &(*current)->left;
		else if (comp((*current)->data, data))
			current = &(*current)->right;
		else
			return false; // Data already exists
	}
	*current = new Node(data);

    while (toIncrease.size())
    {
        Node* currentNode = toIncrease.top();
        currentNode->size++;
        toIncrease.pop();
    }
    
	return true;
}

template <class T, typename Compare>
bool Bst<T, Compare>::contains(const T& data) const
{
	Node* current = root;

	while (current)
	{
		if (comp(data, current->data))
			current = current->left;
		else if (comp(current->data, data))
			current = current->right;
		else
			return true;
	}
	return false;
}

template <class T, typename Compare>
typename Bst<T, Compare>::Node** Bst<T, Compare>::findMinNode(Node** root, std::stack<Node*>& toDecrease)
{
	Node** current = root;

	while ((*current)->left)
	{
        toDecrease.push(*current);
		current = &(*current)->left;
	}
	return current;
}

template <class T, typename Compare>
bool Bst<T, Compare>::remove(const T& data)
{
	Node** current = &root;
    std::stack<Node*> toDecrease;

	while (*current)
	{
		if (comp(data, (*current)->data))
			current = &(*current)->left;
		else if (comp((*current)->data, data))
			current = &(*current)->right;
		else
			break;
        
        toDecrease.push(*current);
	}

	if (!(*current))
		return false; // Data not found

	Node* toDelete = *current;

	if (!(*current)->left && !(*current)->right)
		*current = nullptr; // Node has no children
	else if (!(*current)->right)
		*current = (*current)->left; // Node has only left child
	else if (!(*current)->left)
		*current = (*current)->right; // Node has only right child
	else
	{
		Node** rightMin = findMinNode(&(*current)->right, toDecrease);

		*current = *rightMin;
		*rightMin = (*rightMin)->right;

		(*current)->left = toDelete->left;
		(*current)->right = toDelete->right;
	}
	delete toDelete;

    while (toDecrease.size())
    {
        Node* currentNode = toDecrease.top();
        toDecrease.pop();
        --currentNode->size;
    }
    
	return true;
}

template <class T, typename Compare>
size_t Bst<T, Compare>::getSize() const
{
	return root ? root->size : 0;
}

template <class T, typename Compare>
bool Bst<T, Compare>::isEmpty() const
{
	return getSize() == 0;
}

template <class T, typename Compare>
typename Bst<T, Compare>::Node* Bst<T, Compare>::copy(Node* current)
{
	if (!current)
		return nullptr;
	Node* res = new Node(current->data);
	res->left = copy(current->left);
	res->right = copy(current->right);
    res->size = current->size;
	return res;
}

template <class T, typename Compare>
const T& Bst<T, Compare>::indexRec(Node* root, unsigned idx) const
{
    size_t currentIndex = root->left ? root->left->size : 0;

    if(currentIndex == idx)
    {
        return root->data;
    }

    if(currentIndex > idx)
    {
        return indexRec(root->left, idx);
    }

    return indexRec(root->right, idx - currentIndex - 1);
}

template <class T, typename Compare>
const T& Bst<T, Compare>::index(unsigned idx) const
{
    if(idx >= getSize())
        throw std::runtime_error("Out of bound");
    
    return indexRec(root, idx);
}

template <class T, typename Compare>
void Bst<T, Compare>::free(Node* current)
{
	if (!current)
		return;
	free(current->left);
	free(current->right);
	delete current;
}

template <class T, typename Compare>
Bst<T, Compare>::Bst(const Bst<T, Compare>& other)
	: comp(other.comp)
{
	root = copy(other.root);
}

template <class T, typename Compare>
Bst<T, Compare>& Bst<T, Compare>::operator=(const Bst<T, Compare>& other)
{
	if (this != &other)
	{
		free(root);
		root = copy(other.root);
		comp = other.comp;
	}
	return *this;
}

template <class T, typename Compare>
Bst<T, Compare>::~Bst()
{
	free(root);
}

void treeSort(std::vector<int>& v)
{
	Bst<int> bst;
	for (int i = 0; i < v.size(); i++)
		bst.insert(v.at(i));

	unsigned index = 0;
	for (auto it = bst.begin(); it != bst.end(); it++)
		v.at(index++) = *it;
}