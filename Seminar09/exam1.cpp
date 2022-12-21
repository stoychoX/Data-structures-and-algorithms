#include"../Seminar08/tree-utils.h"

// pair.first -> Сумата до момента
// pair.second - Броя на наследниците, които изпълняват условието ключовете им да влизат в интервала в поддървото
std::pair<int, int> findSumHelper(const Tree<int>* t, int x, int y) {
    if(t == nullptr)
        return std::make_pair(0, 0);

    std::pair<int, int> l = std::make_pair(0, 0);
    std::pair<int, int> r = std::make_pair(0, 0);

    if(t->data >= x)
        l  = findSumHelper(t->left, x, y);

    if(t->data <= y)
        r = findSumHelper(t->right, x, y);

    bool oddChildren = ((l.second + r.second) % 2);

    int sum = l.first + r.first;
    int count = l.second + r.second + (t->data >= x && t->data <= y);

    if(oddChildren)
        sum += t->data;

    return std::make_pair(sum, count);
}

int findSum(const Tree<int>* t, int x, int y) {
    return findSumHelper(t, x, y).first;
}

int main() {
    
}