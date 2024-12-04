#include <iostream>

struct node
{
    int data;
    node* left;
    node* right;

    node(int data_, node* left_ = nullptr, node* right_ = nullptr) :
    data(data_),
    left(left_),
    right(right_) {}
};

node* leftRotate(node* root)
{
    if(root == nullptr || root->right == nullptr)
        return nullptr;
    
    node* originalRight = root->right;
    root->right = originalRight->left;
    originalRight->left = root;

    return originalRight;
}

node* rightRotate(node* root)
{
    if(root == nullptr || root->left == nullptr)
        return nullptr;
    
    node* originalLeft = root->left;
    root->left = originalLeft->right;
    originalLeft->right = root;

    return originalLeft;
}

int main()
{
    node* example = new node(2, new node(1), new node(3));
    example = leftRotate(example);
    example = rightRotate(example);

    std::cout << example->data << " " << example->left->data << " " << example->right->data;

}
