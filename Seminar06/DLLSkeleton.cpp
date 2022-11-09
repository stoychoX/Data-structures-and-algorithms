#ifndef DOUBLY_LINKED_LIST_IMPL_
#define DOUBLY_LINKED_LIST_IMPL_

#include<exception>

template<class T>
class DoublyLinkedList {
private:
    struct DLListNode {};

    using Node = DLListNode;

    Node* head;
    Node* tail;

    void copy(const DoublyLinkedList<T>& other);
    void free();
    
    class Iterator {
    private:
        Node* current;
        Iterator(Node* c) {}

    public:
        Iterator& operator++() {}

        Iterator operator++(int) {}

        Iterator& operator--() {}

        Iterator operator--(int) {}

        const T& operator*() {}

        bool operator==(const Iterator& other) const {}

        bool operator!=(const Iterator& other) const {}

        friend class DoublyLinkedList<T>;
    };

public:
    DoublyLinkedList();

    DoublyLinkedList(const DoublyLinkedList<T>&);
    DoublyLinkedList& operator=(const DoublyLinkedList<T>&);

    DoublyLinkedList(DoublyLinkedList<T>&&);
    DoublyLinkedList& operator=(DoublyLinkedList<T>&&);

    void pushBack(const T&);
    void popBack();

    void pushFront(const T&);
    void popFront();

    bool empty() const;

    const T& back() const;
    const T& front() const;

    Iterator begin();
    Iterator end();

    void insert(Iterator at, const T& elem);

    ~DoublyLinkedList();
};

#endif