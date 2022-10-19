#include<iostream>
#include<deque>
#include<vector>

std::vector<int> maxSlidingWindow(const std::vector<int>& v, size_t k) {
    std::deque<int> window;
    std::vector<int> result;

    for (size_t i = 0; i < k; i++) {
        while(!window.empty() && window.back() < v[i]) {
            window.pop_back();
        }
        window.push_back(v[i]);
    }

    result.push_back(window.front());

    for (size_t i = k; i < v.size(); i++) {
        if(window.front() == v[i - k]) {
            window.pop_front();
        }

        while(!window.empty() && window.back() < v[i]) {
            window.pop_back();
        }

        window.push_back(v[i]);
        result.push_back(window.front());
    }
    
    return result;
}

int main() {
    std::vector<int> example = {1, 3, -1, -3, 5, 3, 6, 7};

    std::vector<int> result = maxSlidingWindow(example, 3);

    for(auto elem : result)
        std::cout << elem << " ";
}