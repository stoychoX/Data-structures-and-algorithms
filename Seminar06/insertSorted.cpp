#include<iostream>
#include<list>
#include"../Seminar04/linked-list-utils.h"
#include<algorithm>

template<class T>
void insertSorted(LinkedListNode<T>*& ll, const T& elem) {
	LinkedListNode<T>* toInsert = new LinkedListNode<T>(elem);

	if (ll == nullptr) {					// Празен списък
		ll = toInsert;
	}
	else if (ll->data > elem) {				// Елементът е по - малък от всички
		toInsert->next = ll;
		ll = toInsert;
	}
	else if (ll->next == nullptr) {			// Списъкът е от един елемент и елементът не стои в началото (ако стоеше щяхме да сме в сл2)
		ll->next = toInsert;
	}
	else {									// Елементът може да е в средата или в края
		LinkedListNode<T>* it = ll;

		while (it->next != nullptr) {
			if (it->next->data > elem) {	// Намерена е позицията на елемента
				LinkedListNode<T>* nNext = it->next;
				it->next = toInsert;
				toInsert->next = nNext;
				return;
			}

			it = it->next;
		}

		it->next = toInsert;			// Ако сме стигнали до тук то мястото на елемента е в края на списъка
	}
}

template<class T>
void insertSorted(std::list<T>& ll, const T& elem) {
    auto iter = ll.begin();

    while(iter != ll.end()) {
        if(*iter > elem) {
            ll.insert(iter, elem);
            break;
        }
        ++iter;
    }

    if(iter == ll.end())
        ll.push_back(elem);
}

int main() {
    std::list<int> ll;

    srand(time(NULL));

    for (size_t i = 0; i < 55555; i++)
        insertSorted(ll, rand());

    std::cout << std::is_sorted(ll.begin(), ll.end());
}