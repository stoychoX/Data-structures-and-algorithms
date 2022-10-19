#ifndef LINKED_QUEUE_IMPL
#define LINKED_QUEUE_IMPL

#include<cstddef>

template<class T>
class LinkedQueue {
private:
    struct LinkedNode {
        T data;
        LinkedNode* next;

        LinkedNode(const T& argData, LinkedNode* argNext = nullptr) : data {argData}, next{argNext} {} 
    };

    LinkedNode* head;                   // Първия добавен елемент в опашката
    LinkedNode* tail;                   // Последния добавен елемент в опашката
    size_t queueSize;

    void copy(const LinkedQueue<T>&);
    void free();

public:
    LinkedQueue();
    
    LinkedQueue(const LinkedQueue<T>&);
    LinkedQueue& operator=(const LinkedQueue<T>&);

    LinkedQueue(LinkedQueue<T>&&) noexcept;
    LinkedQueue& operator=(LinkedQueue<T>&&) noexcept;

    void push(const T&);
    void pop();
    const T& front() const;

    bool empty() const;

    size_t size() const;

    ~LinkedQueue();
};

template<class T>
LinkedQueue<T>::LinkedQueue() : head {nullptr}, tail{nullptr}, queueSize{0} {}

template<class T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T>& other) {
    copy(other);
}

template<class T>
LinkedQueue<T>& LinkedQueue<T>::operator=(const LinkedQueue<T>& other) {
    if(this != &other){
        free();
        copy(other);
    }

    return *this;
}

template<class T>
LinkedQueue<T>::LinkedQueue(LinkedQueue<T>&& other) noexcept {
    head = other.head;
    tail = other.tail;
    size = other.size;

    other.head = nullptr;
    other.tail = nullptr;
}

template<class T>
LinkedQueue<T>& LinkedQueue<T>::operator=(LinkedQueue<T>&& other) noexcept {
    if(this != &other) {
        head = other.head;
        tail = other.tail;
        size = other.size;

        other.head = nullptr;
        other.tail = nullptr;
    }
    return *this;
}

template<class T>
void LinkedQueue<T>::copy(const LinkedQueue<T>& other) {
    LinkedNode* iter = other.head;

    while(iter) {
        push(iter->data);
        iter = iter->next;
    }
}

template<class T>
void LinkedQueue<T>::free() {
    LinkedNode* iter = head;
    while(iter) {
        LinkedNode* removeMe = iter;
        iter = iter->next;
        delete removeMe;
    }
}

template<class T>
bool LinkedQueue<T>::empty() const {
    return head == nullptr;
}

template<class T>
size_t LinkedQueue<T>::size() const {
    return queueSize;
}

template<class T>
void LinkedQueue<T>::push(const T& elem) {
    LinkedNode* toPush = new LinkedNode(elem);
    if(empty()) {
        tail = toPush;
        head = toPush;
    }
    else {
        tail->next = toPush;
        tail = toPush;
    }

    ++queueSize;
}

template<class T>
void LinkedQueue<T>::pop() {
    if(empty()) {
        throw "Empty queue";
    }
    else if(head == tail) {
        delete head;
        head = nullptr;
        tail = nullptr;
    }
    else {
        LinkedNode* deleteMe = head;
        head = head->next;
        delete deleteMe;
    }

    --queueSize;
}

template<class T>
const T& LinkedQueue<T>::front() const {
    if(empty()){
        throw "Empty queue";
    }

    return head->data;
}

template<class T>
LinkedQueue<T>::~LinkedQueue() {
    free();
}

#endif
