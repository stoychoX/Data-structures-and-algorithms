#include "singly-linked-list.hpp"
#include <iostream>
#include <cassert>
#include <forward_list>

void push_tests()
{
    singly_linked_list<int> ll;
    ll.push_back(1);

    assert(ll.front() == 1 && ll.size() == 1);
    ll.push_front(0);
    assert(ll.front() == 0 && ll.back() == 1 && ll.size() == 2);

    for (size_t i = 2; i < 100; i++)
        ll.push_back(i);

    assert(ll.size() == 100);

    auto it = ll.begin();

    for (size_t i = 0; i < 100; i++)
    {
        assert(*it == i);
        ++it;
    }
    
    ll.remove_after(ll.begin());
    assert(*(++ll.begin()) == 2 && ll.size() == 99);
}

void construct_tests()
{
    singly_linked_list<int> ll;
    for (size_t i = 0; i < 100; i++)
    {
        ll.push_back(i);
    }
    
    singly_linked_list<int> copy(ll);

    auto it = ll.begin();
    auto it_copy = copy.begin();

    while (true)
    {
        assert(*it == *it_copy);
        ++it;
        ++it_copy;

        if(it == ll.end() || it_copy == copy.end())
            break;
    }

    assert(ll.size() == copy.size());   

    singly_linked_list<int> move(std::move(ll));
    ll = std::move(move);
    move = std::move(ll);

    auto its = move.begin();
    for(const auto& x : copy)
    {
        assert(x == *its);
        assert(its != move.end());
        ++its;
    }
    assert(its == move.end());
    assert(move.size() == 100);
}

void concat_tests()
{
    singly_linked_list<int> ll;
    singly_linked_list<int> lls;

    for (size_t i = 0; i < 50; i++)
    {
        ll.push_back(i);
        lls.push_back(50 + i);
    }

    singly_linked_list<int> cat = concat(ll, lls);
    assert(cat.size() == 100);
    int val = 0;

    for(const auto& x : cat)
    {
        assert(x == val++);
    }
}

int main()
{
    push_tests();
    construct_tests();
    concat_tests();
}