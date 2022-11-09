#include<iostream>
#include<list>
#include<algorithm>

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