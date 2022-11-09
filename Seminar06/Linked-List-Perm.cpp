#include"../Seminar04/linked-list-utils.h"

bool isLinkedListPermRec(const LinkedListNode<int>*& begin, const LinkedListNode<int>* end) {
    if(end == nullptr)
        return true;

    bool res = isLinkedListPermRec(begin, end->next) && (begin->data == end->data);

    begin = begin->next;
    return res;
}

template<class T>
bool isLinkedListPerm(const LinkedListNode<T>* ll) {
    if(ll == nullptr)
        return true;
    
    const LinkedListNode<int>* begin = ll;
    const LinkedListNode<int>* end = ll;
    
    return isLinkedListPermRec(begin, end);
}

int main() {
    LinkedListNode<int>* ll = new LinkedListNode(0, new LinkedListNode(1, new LinkedListNode(1)));

    std::cout << isLinkedListPerm(ll);
}