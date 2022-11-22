#include<iostream>
#include"../Seminar04/linked-list-utils.h"
#include<stack>

using ListNode = LinkedListNode<std::stack<int>>;

// O(k*n) памет, където n е дължината на списъка а k размера на най - големия стек
// O(k*n) време
void equalize(ListNode* ll) {
    std::stack<int> temp;
    ListNode* iter = ll;

    while(iter) {
        while(!iter->data.empty()) {
            temp.push(iter->data.top());
            iter->data.pop();
        }
        iter = iter->next;
    }

    iter = ll;

    while(!temp.empty()) {
        if(iter == nullptr) {
            iter = ll;
        }
        iter->data.push(temp.top());
        temp.pop();
        iter = iter->next;
    }
}

void printStack(std::stack<int> s) {
    int size = s.size();

    std::cout << "[";

    while (!s.empty()) {
        std::cout << s.top() << " ";
        s.pop();
    }

    std::cout << "] -> " << size << std::endl;
}

int main() {
    ListNode* ll = fromList(
        {
            std::stack<int>({1, 4}), 
            std::stack<int>({6, 7, 8, 9, 5}), 
            std::stack<int>({10, 11, 12}), 
            std::stack<int>({1, 41}), 
            std::stack<int>({6, 7, 8, 9, 5, 7, 9, 0, 10, 20, 30})
        }
    );
    
    equalize(ll);
    printLinkedList(ll, printStack);
    freeList(ll);
}