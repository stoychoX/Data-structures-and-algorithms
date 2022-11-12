#ifndef _SINGLY_LINKED_LIST_IMPL
#define _SINGLY_LINKED_LIST_IMPL

#include<stdexcept>

template<class T>
class LinkedList {
private:
    struct LinkedListNode {
        T data;
        LinkedListNode* next;

        LinkedListNode(const T& elem, LinkedListNode* n = nullptr) : data{ elem }, next { n } {} 
    };

    void free();
    void copy(const LinkedList<T>&);
public:
    class Iterator {
        private:
            // Текущия възел в обхождането
            LinkedListNode* currentNode;

            Iterator(LinkedListNode* arg) : currentNode { arg } {}
        public:
        
        Iterator& operator++() {
            if(currentNode == nullptr)
                return *this;
            currentNode = currentNode->next;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        T& operator*() {
            return currentNode->data;
        }

        bool operator==(const Iterator& other) const {
            return other.currentNode == currentNode;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }

        friend class LinkedList;
    };

    class ConstIterator {
        private:
            const LinkedListNode* currentNode;    // Това вече е указател към константна памет!

            ConstIterator(LinkedListNode* arg) : currentNode { arg } {}  
        public:

        ConstIterator& operator++() {
            if(currentNode == nullptr)
                return *this;
            
            currentNode = currentNode->next;
            return *this;
        }

        ConstIterator operator++(int) {
            ConstIterator temp = *this;
            ++(*this);
            return temp;
        }

        const T& operator*() const {
            return currentNode->data;
        }

        bool operator==(const ConstIterator& other) const {
            return other.currentNode == currentNode;
        }

        bool operator!=(const ConstIterator& other) const {
            return !(*this == other);
        }

        friend class LinkedList;
    };

    LinkedList();

    LinkedList(const LinkedList<T>&);
    LinkedList(LinkedList<T>&&);

    LinkedList& operator=(const LinkedList<T>&);
    LinkedList& operator=(LinkedList<T>&&);

    Iterator begin() {
        return Iterator(head);
    }

    Iterator end() {
        return Iterator(nullptr);
    }

    ConstIterator begin() const {
        return Iterator(head);
    }

    ConstIterator end() const {
        return Iterator(nullptr);
    }

    ConstIterator cbegin() const {
        return ConstIterator(head);
    }

    ConstIterator cend() const {
        return ConstIterator(nullptr);
    }

    void pushBack(const T&);
    void popBack();

    void pushFront(const T&);
    void popFront();

    const T& front() const;
    const T& back() const;

    bool empty() const;
    size_t size() const;

    ~LinkedList();

private:
    LinkedListNode* head;
    LinkedListNode* tail;
    size_t sizeOfList;
};

template<class T>
LinkedList<T>::LinkedList() : head {nullptr}, tail {nullptr}, sizeOfList { 0 } {}

template<class T>
void LinkedList<T>::free() {
    while(head) {
        LinkedListNode* toDelete = head;
        head = head->next;
        delete toDelete;
    }
    sizeOfList = 0;
}

template<class T>
void LinkedList<T>::copy(const LinkedList<T>& other) {
    LinkedListNode* iter = other.head;

    while(iter) {
        pushBack(iter->data);
        iter = iter->next;
    }

    sizeOfList = other.sizeOfList;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) : head {nullptr}, tail{ nullptr } {
    copy(other);
}

template<class T>
LinkedList<T>::LinkedList(LinkedList<T>&& other) {
    head = other.head;
    tail = other.tail;
    sizeOfList = other.sizeOfList;

    other.head = other.tail = nullptr;
    other.sizeOfList = 0;
}

template<class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other) {
    if(this != & other) {
        free();
        copy(other);
    }
    return *this;
}

template<class T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& other) {
    if(this != &other) {
        free();
        
        head = other.head;
        tail = other.tail;
        sizeOfList = other.sizeOfList;

        other.head = other.tail = nullptr;
        other.sizeOfList = 0;
    }
    return *this;
}

template<class T>
void LinkedList<T>::pushBack(const T& elem) {
    LinkedListNode* toInsert = new LinkedListNode(elem);
    ++sizeOfList; 

    if(empty()) {
        head = tail = toInsert;
    }
    else {
        tail->next = toInsert;
        tail = toInsert;
    }
}

template<class T>
void LinkedList<T>::popBack() {
    if(empty()) {
        throw std::runtime_error("Tried to pop back on empty list!");
    }
    --sizeOfList;

    if(head == tail) {
        delete tail;
        head = tail = nullptr;
    }
    else {
        LinkedListNode* newTail = head;

        // O(n) за n дължината на свързания списък
        while (newTail->next != tail) { 
            newTail = newTail->next;
        }

        delete tail;
        tail = newTail;
        tail->next = nullptr;
    }
}

template<class T>
void LinkedList<T>::pushFront(const T& elem) {
    LinkedListNode* toInsert = new LinkedListNode(elem, head);
    
    if(empty())
        tail = toInsert;
    
    head = toInsert;

    ++sizeOfList;
}

template<class T>
void LinkedList<T>::popFront() {
    if(empty()) 
        throw std::runtime_error("Cannot pop front from empty list!");
    
    if(head == tail) {
        delete tail;
        head = tail = nullptr;
    }
    else {
        LinkedListNode* toDelete = head;
        head = head->next;
        delete toDelete;
    }

    --sizeOfList;
}

template<class T>
bool LinkedList<T>::empty() const {
    return head == nullptr;
}

template<class T>
size_t LinkedList<T>::size() const {
    return sizeOfList;
}

template<class T>
const T& LinkedList<T>::front() const {
    if(empty()) 
        throw std::runtime_error("Empty list!");

    return head->data;
}

template<class T>
const T& LinkedList<T>::back() const {
    if(empty()) 
        throw std::runtime_error("Empty list!");

    return tail->data;
}

template<class T>
LinkedList<T>::~LinkedList() {
    free();
}

#endif
