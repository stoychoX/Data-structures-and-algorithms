#include <iostream>

struct ListNode 
{
    int val;
    ListNode* next;
    ListNode(int x, ListNode* next = nullptr) : val(x), next(next) {}
};
template<class Comparator>
void insert_sorted(ListNode*& head, ListNode*& tail, ListNode* element, const Comparator& cmp)
{
    if(head == nullptr)
    {
        head = tail = element;
        return;
    }
    
    if(!cmp(head->val, element->val))
    {
        element->next = head;
        head = element;
        return;
    }

    ListNode* iter = head;

    while(iter->next)
    {
        if(!cmp(iter->next->val, element->val))
            break;
        
        iter = iter->next;
    }

    if(iter->next == nullptr)
        tail = element;

    element->next = iter->next;
    iter->next = element;
}

ListNode* odd_even_sort(ListNode* node)
{
    if(!node || !node->next)
        return node;

    ListNode* even_head = nullptr;
    ListNode* even_tail = nullptr;

    ListNode* odd_head = nullptr;
    ListNode* odd_tail = nullptr;

    std::less<int> less;
    std::greater<int> greater;

    while(node)
    {
        ListNode* to_insert = node;
        node = node->next;
        to_insert->next = nullptr;

        if(to_insert->val % 2 == 0)
        {
            insert_sorted(even_head, even_tail, to_insert, less);
        }
        else
        {
            insert_sorted(odd_head, odd_tail, to_insert, greater);
        }
    }

    if(odd_tail != nullptr)
        odd_tail->next = nullptr;
    
    if(even_head == nullptr)
    {
        return odd_head;
    }

    even_tail->next = odd_head;
    return even_head;
}


void free_list(ListNode* list)
{
    while(list)
    {
        ListNode* to_delete = list;
        list = list->next;
        delete list;
    }
}

int main()
{
    ListNode* example = new ListNode(
        11, new ListNode(21, new ListNode(31, new ListNode(5, new ListNode(51))))
    );

    ListNode* result = odd_even_sort(example);

    ListNode* iter = result;

    while(iter)
    {
        std::cout << iter->val << " ";
        iter = iter->next;
    }

    free_list(result);
}