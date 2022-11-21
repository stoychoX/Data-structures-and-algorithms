#ifndef DOUBLY_LINKED_LIST_IMPL_
#define DOUBLY_LINKED_LIST_IMPL_

#include<exception>

template<class T>
class DoublyLinkedList {
private:
    struct DLListNode {
        T data;
        DLListNode* next;
        DLListNode* prev;

        DLListNode(const T& d, DLListNode* n = nullptr, DLListNode* p = nullptr) :
            data {d},
            next {n},
            prev {p} {}
    };

    using Node = DLListNode;

    Node* head;
    Node* tail;

    void copy(const DoublyLinkedList<T>& other);
    void free();
    
    class Iterator {
    private:
        Node* current;
        Iterator(Node* c = nullptr) : current { c } {}

    public:
        Iterator& operator++() {
            if(current == nullptr) 
                return *this;
            current = current->next;
            return *this;
        }

        Iterator operator++(int) {
            if(current == nullptr)
                return *this;
            
            Iterator tmp = *this;
            current = current->next;
            return tmp;
        }

        Iterator& operator--() {
             if(current == nullptr)
                return *this;
            
            current = current->prev;
            return *this;
        }

        Iterator operator--(int) {
            if(current == nullptr)
                return *this;
            
            Iterator tmp = *this;
            current = current->prev;
            return tmp;
        }

        const T& operator*() {
            if(current == nullptr)
                throw std::exception();
            
            return current->data;
        }

        bool operator==(const Iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }

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

template<class T>
DoublyLinkedList<T>::DoublyLinkedList() : head { nullptr }, tail { nullptr } {}

template<class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other) : head {nullptr}, tail {nullptr} {
    copy(other);
}

template<class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& other) {
    if(this != &other) {
        free();
        copy(other);
    }
    return *this;
}

template<class T>
DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList<T>&& other) {
    head = other.head;
    tail = other.tail;

    other.head = other.tail = nullptr;
}

template<class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(DoublyLinkedList<T>&& other) {
    if(this != &other) {
        free();

        head = other.head;
        tail = other.tail;

        other.head = other.tail = nullptr;
    }
    return *this;
}

template<class T>
void DoublyLinkedList<T>::copy(const DoublyLinkedList<T>& other) {
    Node* iter = other.head;

    while(iter) {
        pushBack(iter->data);
        iter = iter->next;
    }
}

template<class T>
void DoublyLinkedList<T>::free() {
    while(head) {
        Node* toDelete = head;
        head = head->next;
        delete toDelete;
    }
}

template<class T>
bool DoublyLinkedList<T>::empty() const {
    return head == nullptr;
}

template<class T>
void DoublyLinkedList<T>::pushBack(const T& elem) {
    Node* toInsert = new Node(elem);

    if(empty()) {
        head = tail = toInsert;
    }
    else {
        toInsert->prev = tail;
        tail->next = toInsert;
        tail = toInsert;
    }
}

template<class T>
void DoublyLinkedList<T>::pushFront(const T& elem) {
    Node* toInsert = new Node(elem);

    if(empty()) {
        head = tail = toInsert;
    }
    else {
        toInsert->next = head;
        head->prev = toInsert;
        head = toInsert;
    }
}

template<class T>
void DoublyLinkedList<T>::popBack() {
    if(empty())
        throw std::exception();
    
    if(tail == head) {
        delete head;
        tail = head = nullptr;
        return;
    }

    tail->prev->next = nullptr;

    Node* toDelete = tail;
    tail = tail->prev;
    delete toDelete;
}


template<class T>
void DoublyLinkedList<T>::popFront() {
    if(empty())
        throw std::exception();
    
    Node* toDelete = head;

    if(head == tail) {
        delete toDelete;
        head = tail = nullptr;
        return;
    }

    head->next->prev = nullptr;
    head = head->next;
    delete toDelete;
}

template<class T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::begin() {
    return Iterator(head);
}

template<class T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::end() {
    return Iterator(nullptr);
}

template<class T>
void DoublyLinkedList<T>::insert(Iterator at, const T& elem) {
    // Ако е nullptr предполагам, че са подали .end() и добавям в края
    if(at.current == nullptr) {
        tail->next = new Node(elem, nullptr, tail);
        tail = tail->next;
        return;
    }

    Node* toInsert = new Node(elem, at.current, at.current->prev);
    
    if(at.current->prev != nullptr)
        at.current->prev->next = toInsert;
    
    at.current->prev = toInsert;

    if(at.current == head)
        head = toInsert;
    
    if(at.current == tail)
        tail = toInsert;

    at.current = toInsert;
}

template<class T>
const T& DoublyLinkedList<T>::back() const {
    if(empty())
        throw std::exception();
    
    return tail->data;
}

template<class T>
const T& DoublyLinkedList<T>::front() const {
    if(empty())
        throw std::exception();
    
    return head->data;
}

template<class T>
DoublyLinkedList<T>::~DoublyLinkedList(){ free(); }

#endif