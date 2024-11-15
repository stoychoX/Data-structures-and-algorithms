#include <iostream>
#include <deque>
#include <vector>

std::vector<int> sliding_window_maximum(const std::vector<int> v, unsigned k)
{
    std::vector<int> result;
    std::deque<int> window;

    for (size_t i = 0; i < k; i++)
    {
        while(!window.empty() && window.back() < v[i])
        {
            window.pop_back();
        }
        window.push_back(v[i]);
    }
    
    result.push_back(window.front());

    for (size_t i = k; i < v.size(); i++)
    {
        if(window.front() == v[i-k])
            window.pop_front();
        
        while(!window.empty() && window.back() < v[i])
        {
            window.pop_back();
        }

        window.push_back(v[i]);

        result.push_back(window.front());
    }

    return result;
}

int main()
{

}