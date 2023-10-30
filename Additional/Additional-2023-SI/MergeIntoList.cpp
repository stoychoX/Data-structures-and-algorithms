#include <iostream>

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x, ListNode *n = nullptr) : val(x), next(n) {}
};

ListNode *advance(ListNode *from, size_t index)
{
    while (index)
    {
        if (from == nullptr)
        {
            return nullptr;
        }

        from = from->next;
        --index;
    }

    return from;
}

ListNode *getTail(ListNode *list)
{
    if (!list || !list->next)
    {
        return list;
    }

    while (list->next)
    {
        list = list->next;
    }
    return list;
}

void freeRagne(ListNode *from, ListNode *to)
{
    while (from != to)
    {
        ListNode *node = from;
        from = from->next;
        delete node;
    }
}

void free(ListNode *ll)
{
    while (ll)
    {
        ListNode *toDelete = ll;
        ll = ll->next;
        delete toDelete;
    }
}

ListNode *addFront(ListNode *destination, ListNode *target, size_t to)
{
    ListNode *tail = getTail(target);
    ListNode *end = advance(destination, to + 1);
    tail->next = end;
    freeRagne(destination, end);
    return target;
}

ListNode *mergeInBetween(ListNode *destination, ListNode *target, size_t from, size_t to)
{
    if (from == 0)
    {
        return addFront(destination, target, to);
    }

    ListNode *predBegin = advance(destination, from - 1);
    if (!predBegin)
    {
        return nullptr;
    }

    ListNode *postEnd = advance(predBegin, to - from + 2);
    ListNode *toDeleteHolder = predBegin->next;
    ListNode *targetTail = getTail(target);

    predBegin->next = target;
    targetTail->next = postEnd;

    freeRagne(toDeleteHolder, postEnd);

    return destination;
}

int main()
{
    ListNode *fst = new ListNode(1,
                                 new ListNode(2,
                                              new ListNode(3,
                                                           new ListNode(4,
                                                                        new ListNode(6)))));

    ListNode *snd = new ListNode(3,
                                 new ListNode(4, 
                                    new ListNode(5)));

    ListNode *ans = mergeInBetween(fst, snd, 1, 3);

    ListNode *it = ans;

    while(it)
    {
        std::cout << it->val << " ";
        it = it->next;
    }

    free(ans);
}