#include "tree-utils.h"
#include <cmath>

// for regular binary trees
template <typename T>
int max_elem(Tree<T> *tree) {
    int res = tree->data;

    if (tree->left != nullptr) {
        res = std::max(res, max_elem(tree->left));
    }
    if (tree->right != nullptr) {
        res = std::max(res, max_elem(tree->right));
    }

    return res;
}

template <typename T>
int min_elem(Tree<T> *tree) {
    int res = tree->data;

    if (tree->left != nullptr) {
        res = std::min(res, min_elem(tree->left));
    }
    if (tree->right != nullptr) {
        res = std::min(res, min_elem(tree->right));
    }

    return res;
}

// for binary search trees
template <typename T>
int max_elem_bst(Tree<T> *tree) {
    while (tree->right != NULL)
        tree = tree->right;

    return tree->data;
}

template <typename T>
int min_elem_bst(Tree<T> *tree) {
    while (tree->left != NULL)
        tree = tree->left;

    return tree->data;
}

int main() {
    Tree<int> *regularTree = new Tree<int>(2, new Tree<int>(3, new Tree<int>(4), new Tree<int>(5)), new Tree<int>(13, new Tree<int>(7), new Tree<int>(8)));
    printTree(regularTree);
    std::cout << "Maximum element in regular binary tree: " << max_elem(regularTree) << '\n';
    std::cout << "Minimum element in regular binary tree: " << min_elem(regularTree) << '\n';

    Tree<int> *binarySearchTree = new Tree<int>(8, new Tree<int>(3, new Tree<int>(1), new Tree<int>(6, new Tree<int>(4), new Tree<int>(7))), new Tree<int>(10, nullptr, new Tree<int>(14, new Tree<int>(13))));
    printTree(binarySearchTree);
    std::cout << "Maximum element in bs tree: " << max_elem_bst(binarySearchTree) << '\n';
    std::cout << "Minimum element in bs tree: " << min_elem_bst(binarySearchTree) << '\n';

    freeTree(regularTree);
    freeTree(binarySearchTree);
    return 0;
}