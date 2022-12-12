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
    Tree<int>* root = new Tree<int>(50);
	Tree<int>* n1 = new Tree<int>(25);
	Tree<int>* n2 = new Tree<int>(75);
	Tree<int>* n3 = new Tree<int>(12);
	Tree<int>* n4 = new Tree<int>(30);
	Tree<int>* n5 = new Tree<int>(60);
	Tree<int>* n6 = new Tree<int>(85);
	Tree<int>* n7 = new Tree<int>(52);
	Tree<int>* n8 = new Tree<int>(70);

	root->left = n1;
	root->right = n2;
	n1->left = n3;
	n1->right = n4;
	n2->left = n5;
	n2->right = n6;
	n5->left = n7;
	n5->right = n8;

	std::cout << findSum(root, 30, 75);
}