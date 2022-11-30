#include<iostream>
#include"tree-utils.h"

// Тук допускаме да има повторения. Ако искаме да няма повторения втория else ще стане else if(t->data > elem)
template<class T>
void insertInBST(Tree<T>*& t, const T& elem) {
    if(t == nullptr) {
        t = new Tree<T>(elem);
        return;
    }
    else if(t->data < elem) {
        insertInBST(t->right, elem);
    }
    else {
        insertInBST(t->left, elem);
    }
}

int main() {
    Tree<int>* example = new Tree<int>(4, new Tree<int>(2), new Tree<int>(6));
    
    insertInBST(example, 1);
    printTree(example);

    // За любопитните: колко ли ще е височината на дърво от 50 случайни числа?
    Tree<int>* secondExample = nullptr;
    srand(time(NULL));
    for (int i = 0; i < 50; i++)
        insertInBST<int>(secondExample, rand() % 100);
    
    exportToTex(secondExample, "file.txt");
    //-------------------------------------------------

    freeTree(example);
    freeTree(secondExample);
}