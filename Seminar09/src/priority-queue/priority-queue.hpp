#pragma once
#include <vector>
#include <stdexcept>

class priority_queue
{
private:
    static size_t left_child(size_t index);
    static size_t right_child(size_t index);
    static int parent(int index);

    void heapify(size_t index);
public:
    priority_queue() = default;

    // build_heap
    priority_queue(const std::vector<int>& data);

    void push(int element);
    int peek() const;
    void pop();

    bool empty() const;
    size_t size() const;

private:
    std::vector<int> _data;
};

size_t priority_queue::left_child(size_t index)
{
    return 2 * index + 1;
}

size_t priority_queue::right_child(size_t index)
{
    return 2 * index + 2;
}

int priority_queue::parent(int index)
{
    return (index - 1) / 2;
}

void priority_queue::heapify(size_t index)
{
    size_t current_index = index;

    while(true)
    {
        size_t left_index = left_child(current_index);
        size_t right_index = right_child(current_index);

        bool go_left  = left_index < _data.size()  && _data[current_index] < _data[left_index];
        bool go_right = right_index < _data.size() && _data[current_index] < _data[right_index];

        if(!go_left && !go_right)
        {
            break;
        }
        
        if(go_left && go_right)
        {
            if(_data[left_index] > _data[right_index])
            {
                std::swap(_data[current_index], _data[left_index]);
                current_index = left_index;
            }
            else
            {
                std::swap(_data[current_index], _data[right_index]);
                current_index = right_index;
            }
        }
        else if(go_left)
        {
            std::swap(_data[current_index], _data[left_index]);
            current_index = left_index;
        }
        else // go_right
        {
            std::swap(_data[current_index], _data[right_index]);
            current_index = right_index;
        }
    }
}

priority_queue::priority_queue(const std::vector<int>& data) :
    _data(data)
{
    // build_heap
    for (int i = _data.size() / 2 - 1; i >= 0; i--)
        heapify(i);    
}

void priority_queue::push(int element)
{
    _data.push_back(element);
    int index = _data.size() - 1;
    int parent_index = parent(index);

    while(index > 0 && _data[index] > _data[parent_index])
    {
        std::swap(_data[index], _data[parent_index]);
        index = parent_index;
        parent_index = parent(index);
    }
}

int priority_queue::peek() const
{
    return _data[0];
}

void priority_queue::pop() 
{
    if(empty())
        throw std::runtime_error("Pop on empty queue");
    
   _data[0] = _data.back();
   _data.pop_back();
   heapify(0); 
}

size_t priority_queue::size() const
{
    return _data.size();
}

bool priority_queue::empty() const
{
    return size() == 0;
}