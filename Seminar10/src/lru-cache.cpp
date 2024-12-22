#include <list>
#include <unordered_map>
#include <stdexcept>

class LRUCache
{
    size_t capacity;
    std::list<std::pair<int, int>> data;
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> dataMap;

public:
    LRUCache(size_t capacity) : capacity(capacity) { }

    int get(int key)
    {
        if (dataMap.find(key) == dataMap.end())
        {
            throw std::runtime_error("Data not in cache");
        }

        auto it = dataMap[key];

        // Transfers elements from one list to another. 
        // No elements are copied or moved, only the internal pointers of the list nodes are re-pointed.
        data.splice(data.begin(), data, it);
        return it->second;
    }

    void put(int key, int value)
    {
        if (dataMap.find(key) != dataMap.end())
        {
            auto it = dataMap[key];
            data.erase(it);
        }

        data.push_front({ key, value });
        dataMap[key] = data.begin();
        if (data.size() > capacity)
        {
            dataMap.erase(data.back().first);
            data.pop_back();
        }
    }
};