#include "tree-utils.h"

template <typename T>
void inorderTraversal(Tree<T> *tree) {
    if (tree == nullptr) {
        return;
    }

    inorderTraversal(tree->left);
    std::cout << tree->data << ' ';
    inorderTraversal(tree->right);
}

int main() {
    Tree<int> *root = new Tree<int>(8, new Tree<int>(3, new Tree<int>(1), new Tree<int>(6, new Tree<int>(4), new Tree<int>(7))), new Tree<int>(10, nullptr, new Tree<int>(14, new Tree<int>(13))));

    inorderTraversal(root); //изпечатва елементите на дървото сортирано
    std::cout << '\n';
    printTree(root);

    freeTree(root);
    return 0;
}