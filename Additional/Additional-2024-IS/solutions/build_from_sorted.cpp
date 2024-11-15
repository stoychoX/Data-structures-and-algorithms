#include <iostream>
#include <vector>

struct node
{
	int data;
	node* left = nullptr;
	node* right = nullptr;

	node(int d, node* l = nullptr, node* r = nullptr)
		: data(d)
		, left(l)
		, right(r)
	{}
};

using const_iterator = std::vector<int>::const_iterator;

node* build_from_range(const_iterator begin, const_iterator end)
{
    // When end is before begin std::distance will return
    // negative number by standard.
    int distance = std::distance(begin, end);

    if(distance < 0)
        return nullptr;
    
    if(distance == 0)
        return new node(*begin);
    
    int mid = distance / 2;

    return new node(
        *(begin + mid),
        build_from_range(begin, begin + mid - 1),
        build_from_range(begin + mid + 1, end)
    );
}

node* build_from_sorted(const std::vector<int>& v)
{
    return build_from_range(v.begin(), v.end() - 1);
}

void inorder(node* root)
{
    if(!root) return;

    inorder(root->left);
    std::cout << root->data << " ";
    inorder(root->right);
}

void free_tree(node* tree)
{
    if(!tree)
        return;
    free_tree(tree->left);
    free_tree(tree->right);

    delete tree;
}

int main()
{
    std::vector<int> sorted = {1, 2, 4, 8, 16, 32, 64};
    node* result = build_from_sorted(sorted);

    inorder(result);
    free_tree(result);
}