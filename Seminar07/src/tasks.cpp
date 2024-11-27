#include <iostream>
#include <climits>
#include <vector>
#include <queue>

struct node
{
    int data;
    node* left = nullptr;
    node* right = nullptr;

    node(int data_, node* left_ = nullptr, node* right_ = nullptr) :
        data(data_),
        left(left_),
        right(right_) {}
};

// Task 01: Check if tree is bst
bool is_bst_rec(node* root, int left_interval, int right_interval)
{
    if(root == nullptr)
        return true;
    
    if(root->data < left_interval || root->data > right_interval)
        return false;
    
    return is_bst_rec(root->left, left_interval, root->data) &&
        is_bst_rec(root->right, root->data, right_interval);
}

bool is_bst(node* root)
{
    return is_bst_rec(root, INT_MIN, INT_MAX);
}

// Task 02: check if root to leaf paths form a progression
// Solved in two ways.
bool is_progression(const std::vector<int>& v)
{
    if(v.size() <= 2)
        return true;
    
    int offset = v[1] - v[0];

    for (size_t i = 1; i < v.size() - 1; i++)
    {
        if(v[i+1] - v[i] != offset)
            return false;
    }
    return true;
}

void progression_rec(node* root, std::vector<int>& current_path)
{
    if(root == nullptr)
    {
        return;
    }

    current_path.push_back(root->data);

    if(!root->left && !root->right)
    {
        if(is_progression(current_path))
        {
            for(int x : current_path)
            {
                std::cout << x << " ";
            }
            std::cout << std::endl;
        }
    }

    progression_rec(root->right, current_path);
    progression_rec(root->left, current_path);
    current_path.pop_back();
}

void get_progression_dummy(node* root)
{
    std::vector<int> path;
    progression_rec(root, path);
}

void get_progression_offset(node* root, int offset, std::vector<int>& current_path)
{
    if(root == nullptr)
        return;
    
    current_path.push_back(root->data);

    if(!root->left && !root->right)
    {
        for(int x : current_path)
        {
            std::cout << x << " ";
        }
        std::cout << std::endl;
    }

    if(root->left)
    {
        int left_offset = root->left->data - root->data;

        if(left_offset == offset)
        {
            get_progression_offset(root->left, offset, current_path);
        }
    }

    if(root->right)
    {
        int eight_offset = root->right->data - root->data;

        if(eight_offset == offset)
        {
            get_progression_offset(root->right, offset, current_path);
        }
    }

    current_path.pop_back();
}

void get_progression(node* root)
{
    if(root == nullptr)
        return;
    std::vector<int> path;

    path.push_back(root->data);
    
    if(root->left)
    {
        int offset = root->left->data - root->data;
        get_progression_offset(root->left, offset, path);
    }

    if(root->right)
    {
        int offset = root->right->data - root->data;
        get_progression_offset(root->right, offset, path);
    }
}

// Task 03: check if any level forms a progression
// solved in two ways
unsigned height(node* root)
{
    if(root == nullptr)
        return 0;
    
    return 1 + std::max(height(root->left), height(root->right));
}

void fill_levels(node* root, std::vector<std::vector<int>>& levels, unsigned current_level)
{
    if(root == nullptr)
        return;
    
    levels[current_level].push_back(root->data);
    fill_levels(root->left, levels, current_level + 1);
    fill_levels(root->right, levels, current_level + 1);
}

void get_progression_dummy_levels(node* root)
{
    if(root == nullptr)
        return;
    
    std::vector<std::vector<int>> levels;
    levels.resize(height(root));

    fill_levels(root, levels, 0);
    for(const std::vector<int>& level : levels)
    {
        if(is_progression(level))
        {
            for(int x : level)
            {
                std::cout << x << ' ';
            }
            std::cout << std::endl;
        }
    }
}

void get_progression_levels(node* root)
{
    if(root == nullptr)
        return;
    
    std::queue<node*> q;
    q.push(root);

    while(q.size())
    {
        std::vector<int> current_level;

        current_level.resize(q.size());
        unsigned idx = 0;
        size_t elements_in_level = q.size();

        for (size_t i = 0; i < elements_in_level; i++)
        {
            node* current_node = q.front();
            q.pop();
            current_level[idx++] = current_node->data;

            if(current_node->left)
                q.push(current_node->left);


            if(current_node->right)
                q.push(current_node->right);
        }

        if(is_progression(current_level))
        {
            for(int x : current_level)
            {
                std::cout << x << " ";
            }
            std::cout << std::endl;
        }
        
    }
}

int main()
{
    
}