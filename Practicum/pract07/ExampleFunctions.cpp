#include <iostream>
#include <queue>
#include <algorithm>

template <typename T>
struct TreeNode {
    T data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const T& val) : data(val), left(nullptr), right(nullptr) {}
};

// Проверка дали даден възел е листо
// Листо е възел, който няма деца
template <typename T>
bool isLeaf(TreeNode<T>* node) {
    return node && !node->left && !node->right;
}

// Проверка дали даден елемент се съдържа в дърво
template <typename T>
bool contains(TreeNode<T>* root, T value) {
    if (root == nullptr) return false;

    if (root->data == value) return true;

    return contains(root->left, value) || contains(root->right, value);
}

// Намиране на височина на дърво
// Височината на дърво е дължината на най-дългия път от корена до някое листо
template <typename T>
int getHeight(TreeNode<T>* root) {
    if (!root) return -1;

    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);

    return 1 + std::max(leftHeight, rightHeight);
}

// Преброяване на възлите в дърво
template <typename T>
int countNodes(TreeNode<T>* root) {
    if (!root) return 0;

    if (!root->left && !root->right) return 1;

    return 1 + countNodes(root->left) + countNodes(root->right);
}

int main() {
    // Създаване на двоично дърво от цели числа
    TreeNode<int>* root = new TreeNode<int>(1);
    root->left = new TreeNode<int>(2);
    root->right = new TreeNode<int>(3);
    root->left->left = new TreeNode<int>(4);
    root->left->right = new TreeNode<int>(5);
    root->right->left = new TreeNode<int>(6);
    root->right->right = new TreeNode<int>(7);

    // Как изглежда дървото:
    //       1
    //      / \
    //     2   3
    //    / \ / \
    //   4  5 6  7

    // Проверка дали даден възел е листо
    std::cout << "Is 4 a leaf: " << std::boolalpha << isLeaf(root->left->left) << std::endl; // true
    std::cout << "Is 3 a leaf: " << std::boolalpha << isLeaf(root->right) << std::endl; // false

    // Проверка дали даден елемент се съдържа в дървото
    std::cout << "Does the tree contain 5: " << std::boolalpha << contains(root, 5) << std::endl; // true
    std::cout << "Does the tree contain 8: " << std::boolalpha << contains(root, 8) << std::endl; // false

    // Намиране на височината на дървото
    std::cout << "Height of the tree: " << getHeight(root) << std::endl; // 2

    // Преброяване на възлите в дървото
    std::cout << "Total nodes in the tree: " << countNodes(root) << std::endl; // 7

    return 0;
}
