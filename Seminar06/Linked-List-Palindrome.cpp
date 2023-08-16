#include"../Seminar04/linked-list-utils.h"

template<class T>
bool isLinkedListPalRec(const LinkedListNode<T>*& begin, const LinkedListNode<T>* end) {
    if(end == nullptr)
        return true;

    bool res = isLinkedListPalRec(begin, end->next) && (begin->data == end->data);

    begin = begin->next;
    return res;
}

template<class T>
bool isLinkedListPal(const LinkedListNode<T>* ll) {
    if(ll == nullptr)
        return true;
    
    const LinkedListNode<T>* begin = ll;
    const LinkedListNode<T>* end = ll;
    
    return isLinkedListPalRec(begin, end);
}

int main() {
    LinkedListNode<int>* ll = new LinkedListNode(0, new LinkedListNode(1, new LinkedListNode(1)));

    std::cout << isLinkedListPal(ll);
}
