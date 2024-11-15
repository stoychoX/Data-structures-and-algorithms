#include <algorithm>
#include <iostream>
#include <queue>

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

void fill(node* root, std::vector<int>& v)
{
	if (!root)
		return;

	v.push_back(root->data);
	fill(root->left, v);
	fill(root->right, v);
}

node* sort_by_level(node* tree)
{
	std::vector<int> v;
	fill(tree, v);

	std::sort(v.begin(), v.end());

	node* to_return = new node(v[0]);
	int idx = 1;

	std::queue<node*> q;
	q.push(to_return);

	while (idx < v.size())
	{
		node* current = q.front();
		q.pop();

		current->left = new node(v[idx++]);
		if (idx >= v.size())
			break;
		current->right = new node(v[idx++]);

		q.push(current->left);
		q.push(current->right);
	}

	return to_return;
}

void free_tree(node* root)
{
	if (!root)
		return;
	free_tree(root->left);
	free_tree(root->right);
	delete root;
}

// Print tree by levels.
// Not presented - used just for demo.
void print_levels(node* result)
{
	std::queue<node*> q;
	q.push(result);
	q.push(nullptr);

	while (q.size())
	{
		node* current = q.front();
		q.pop();

		if (current == nullptr)
		{
			if (!q.empty())
			{
				q.push(nullptr);
				std::cout << std::endl;
			}
			continue;
		}

		std::cout << current->data << " ";

		if (current->left)
			q.push(current->left);
		if (current->right)
			q.push(current->right);
	}
}

int main()
{
	node* tree = new node(5,
		new node(3, 
			new node(4), 
			new node(0, 
				new node(1), 
				new node(2))),
		new node(8, 
			new node(9), 
			new node(7, new node(10))));

	node* result = sort_by_level(tree);
	print_levels(result);

	free_tree(result);
	free_tree(tree);
}