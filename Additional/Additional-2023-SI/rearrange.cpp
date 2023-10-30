#include <iostream>

struct Node
{
    Node* next = nullptr;
    Node* prev = nullptr;
    int data = 0;
    Node(int data, Node* next = nullptr, Node* prev = nullptr) : data(data), next(next), prev(prev) {}
};

Node* rearange(Node* head)
{
    Node* evensBegin = nullptr;
    Node* evensEnd = nullptr;
    Node* oddsBegin = nullptr;
    Node* oddsEnd = nullptr;

    Node* iter = head;

    while (iter)
    {
        if (iter->data % 2 == 0)
        {
            if (!evensBegin)
            {
                evensBegin = evensEnd = iter;
                iter->prev = nullptr;
            }
            else
            {
                evensEnd->next = iter;
                iter->prev = evensEnd;
                evensEnd = iter;
            }
        }
        else
        {
            if (!oddsBegin)
            {
                oddsBegin = oddsEnd = iter;
                iter->prev = nullptr;
            }
            else
            {
                oddsEnd->next = iter;
                iter->prev = oddsEnd;
                oddsEnd = iter;
            }
        }
        iter = iter->next;
    }
    if(evensEnd)
        evensEnd->next = nullptr;
    if(oddsEnd)
        oddsEnd->next = nullptr;

    // concat
    if (!evensBegin)
        return oddsBegin;
    if (!oddsBegin)
        return evensBegin;

    evensEnd->next = oddsBegin;
    oddsBegin->prev = evensEnd;
    return evensBegin;
}

Node* push_front(Node* list, int elem)
{
    if(!list)
    {
        return new Node(elem);
    }

    Node* toReturn = new Node(elem, list);
    list->prev = toReturn;
    return toReturn;
}

void free(Node* l)
{
    Node* it = l;

    while(it)
    {
        Node* toDelete = it;
        it = it->next;
        delete toDelete;
    }
}

int main()
{
    Node* l = nullptr;

    for (size_t i = 0; i < 50; i++)
    {
        l = push_front(l, 50 - i);
    }

    l = rearange(l);

    Node* it = l;

    while(it)
    {
        std::cout << it->data << " ";
        it = it->next;
    }

    free(l);
}