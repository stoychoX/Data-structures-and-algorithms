#include <iostream>

struct Node
{
    Node* next = nullptr;
    int data = 0;
    Node(int data, Node* next = nullptr) : data(data), next(next){}
};

struct Queue
{
    Node* head = nullptr;
    Node* tail = nullptr;
};

void push(Queue& q, int el)
{
    if (q.head == nullptr)
        q.head = q.tail = new Node(el);
    else
    {
        Node* newNode = new Node(el);
        q.tail->next = newNode;
        
        q.tail = newNode;
    }
}
void pop(Queue& q)
{
    if (!q.head)
        return;
    Node* toDelete = q.head;
    q.head = q.head->next;
    delete toDelete;
}

void insert(Queue& q, int el)
{
    Node* iter = q.head;

    while (iter)
    {
        if (iter->data % 10 == el % 10)
        {
            break;
        }
        iter = iter->next;
    }

    if (iter)
    {
        Node* newNode = new Node(el);
        newNode->next = iter->next;
        iter->next = newNode;
    }
    else
    {
        if (!q.head)
        {
            Node* newNode = new Node(el);
            q.head = q.tail = newNode;
        }
        else
        {
            Node* newNode = new Node(el);
            q.tail->next = newNode;
            q.tail = newNode;
        }
    }
}

void print(const Queue& q)
{
    const Node* it = q.head;

    while(it)
    {
        std::cout << it->data << " ";

        it = it->next;
    }
}
void free(Queue& q)
{
    while (q.head)
    {
        Node* toDelete = q.head;
        q.head = q.head->next;

        delete toDelete;
    }
    
}
int main()
{
    Queue q;

    push(q, 1);
    push(q, 2);
    push(q, 4);
    push(q, 8);
    push(q, 16);

    insert(q, 12);

    print(q);

    free(q);
}