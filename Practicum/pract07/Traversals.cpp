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

// Preorder обхождане (корен, ляво, дясно)
template <typename T>
void preorderTraversal(TreeNode<T>* root) {
    if (!root) return;
    std::cout << root->data << " ";
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

// Inorder обхождане (ляво, корен, дясно)
template <typename T>
void inorderTraversal(TreeNode<T>* root) {
    if (!root) return;
    inorderTraversal(root->left);
    std::cout << root->data << " ";
    inorderTraversal(root->right);
}

// Postorder обхождане (ляво, дясно, корен)
template <typename T>
void postorderTraversal(TreeNode<T>* root) {
    if (!root) return;
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    std::cout << root->data << " ";
}

// Обхождане в широчина
template <typename T>
void bfs(TreeNode<T>* root) {
    if (!root) return;

    std::queue<TreeNode<T>*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode<T>* current = q.front();
        q.pop();

        std::cout << current->data << " ";

        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
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

    // Preorder обхождане
    std::cout << "Preorder traversal: ";
    preorderTraversal(root); // 1 2 4 5 3 6 7
    std::cout << std::endl;

    // Inorder обхождане
    std::cout << "Inorder traversal: ";
    inorderTraversal(root); // 4 2 5 1 6 3 7
    std::cout << std::endl;

    // Postorder обхождане
    std::cout << "Postorder traversal: ";
    postorderTraversal(root); // 4 5 2 6 7 3 1
    std::cout << std::endl;

    // Обхождане в широчина
    std::cout << "BFS traversal: ";
    bfs(root); // 1 2 3 4 5 6 7
    std::cout << std::endl;

    return 0;
}
