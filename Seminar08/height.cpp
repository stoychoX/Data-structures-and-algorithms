#include"tree-utils.h"
#include<iostream>

template<typename T>
size_t height(const Tree<T>* tree) {
	if (!tree)
		return 0;

	return 1 + std::max(height(tree->left), height(tree->right));
}

int main(){
  
}
