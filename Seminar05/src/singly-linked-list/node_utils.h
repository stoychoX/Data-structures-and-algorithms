#pragma once

// We represent a singly linked list
// with an pointer to its first element.
template <class T>
struct node
{
    T data;
    node* next;

    node(const T& data_, node* next_ = nullptr) :
        data(data_),
        next(next_) {}
};

template <class T>
void append_back(node<T>*& head, node<T>*& tail, node<T>* element)
{
    if(head == nullptr)
    {
        head = tail = element;
    }
    else
    {
        tail->next = element;
        tail = tail->next;
    }
}


template <class T>
bool is_sorted(node<T>* list)
{
    if(!list || !list->next)
        return true;
    
    node<T>* prev = list;
    node<T>* next = list->next;

    while(next)
    {
        if(prev->data > next->data) 
        {
            return false;
        }
        prev = prev->next;
        next = next->next;
    }
    return true;
}

template <class T>
void free_list(node<T>* ll)
{
    while(ll)
    {
        node<T>* to_delete = ll;
        ll = ll->next;
        delete to_delete;
    }
}

template <class T>
unsigned list_size(node<T>* list)
{
    unsigned size = 0;
    while(list)
    {
        ++size;
        list = list->next;
    }
    return size;
}

template <class T>
node<T>* push_front(node<T>* head, const T& data)
{
	return new node<T>(data, head);
}