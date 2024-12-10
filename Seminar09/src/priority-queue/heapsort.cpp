#include <iostream>
#include <vector>

void heapify(std::vector<int>& _data, size_t index, size_t array_size)
{
    int current_index = index;

    while(true)
    {
        size_t left_index = 2 * current_index + 1;
        size_t right_index = 2 * current_index + 2;

        bool go_left = left_index < array_size && _data[current_index] < _data[left_index];
        bool go_right = right_index < array_size && _data[current_index] < _data[right_index];

        if(!go_left && !go_right)
        {
            break;
        }

        if(go_left && go_right)
        {
            if(_data[left_index] < _data[right_index])
            {
                std::swap(_data[current_index], _data[right_index]);
                current_index = right_index;
            }
            else
            {
                std::swap(_data[current_index], _data[left_index]);
                current_index = left_index;
            }
        }
        else if(go_left)
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
}

void build_heap(std::vector<int>& data)
{
    for(int i = data.size() / 2 - 1; i >= 0; i--)
        heapify(data, i, data.size());
}

void heap_sort(std::vector<int>& data)
{
    build_heap(data);

    int current_min = data.size() - 1;

    for (size_t i = 0; i < data.size() - 1; i++)
    {
        std::swap(data[0], data[current_min--]);
        heapify(data, 0, current_min);
    }
}

int main()
{
    std::vector<int> v;
    for (size_t i = 0; i < 100; i++)
    {
        v.push_back(rand() % 100);
    }
    
    heap_sort(v);

    for(int x : v)
    {
        std::cout << x << " ";
    }
}