#ifndef AVL_TREE_IMPL
#define AVL_TREE_IMPL

#include<algorithm>
#include<cassert>
#include<cstddef>

template<class T>
class AVLTree {
private:

	struct Node {
		T data;
		Node* left;
		Node* right;
		int height;

		static int getHeight(const Node* r) {
			if (r == nullptr)
				return 0;

			return r->height;
		}

		static void rotateLeft(Node*& r) {
			assert(r->right != nullptr);

			Node* originalRight = r->right;
			r->right = originalRight->left;
			originalRight->left = r;
			r = originalRight;
		}

		static void rotateRight(Node*& r) {
			assert(r->left != nullptr);

			Node* originalLeft = r->left;
			r->left = originalLeft->right;
			originalLeft->right = r;
			r = originalLeft;
		}

		static void balanceLeft(Node*& r) {
			assert(r);

			int rootBalance = getBalanceFactor(r);
			int leftBalance = getBalanceFactor(r->left);

			if (rootBalance == -2) {
				if (leftBalance == 1) {
					rotateLeft(r->left);
					updateHeight(r->left->left);
					updateHeight(r->left);
				}

				rotateRight(r);
				updateHeight(r->right);
				updateHeight(r);
			}
		}

		static void balanceRight(Node*& r) {
			assert(r);

			int rootBalance = getBalanceFactor(r);
			int rightBalance = getBalanceFactor(r->right);

			if (rootBalance == 2) {
				if (rightBalance == -1) {
					rotateRight(r->right);
					updateHeight(r->right->right);
					updateHeight(r->right);
				}

				rotateLeft(r);
				updateHeight(r->left);
				updateHeight(r);
			}
		}

		static void updateHeight(Node* r) {
			if (r == nullptr)
				return;
			r->height = std::max(getHeight(r->left), getHeight(r->right)) + 1;
		}

		static int getBalanceFactor(const Node* r) {
			if (r == nullptr)
				return 0;

			return getHeight(r->right) - getHeight(r->left);
		}

		Node(const T& d, Node* l, Node* r, int h) : data{ d }, left{ l }, right{ r }, height{ h } {}
	};

	Node* findMinNode(Node* r) {
		if (r->left == nullptr)
			return r;

		return findMinNode(r->left);
	}

	void insertRec(Node*& r, const T& elem) {
		if (r == nullptr) {
			r = new Node(elem, nullptr, nullptr, 1);
			size++;
			return;
		}

		if (r->data < elem) {
			insertRec(r->right, elem);

			Node::updateHeight(r->right);
			Node::balanceRight(r);
		}
		else if (r->data > elem) {
			insertRec(r->left, elem);

			Node::updateHeight(r->left);
			Node::balanceLeft(r);
		}
	}

	bool removeRec(Node*& r, const T& elem) {
		if (r == nullptr) {
			return false;
		}

		if (r->data < elem) {
			removeRec(r->right, elem);

			Node::updateHeight(r);
			Node::balanceLeft(r);
		}
		else if (r->data > elem) {
			removeRec(r->left, elem);

			Node::updateHeight(r);
			Node::balanceRight(r);
		}
		else {
			if (!r->left && !r->right) {
				delete r;
				r = nullptr;
				return true;
			}
			else if (r->left && !r->right) {
				Node* toDelete = r;
				r = r->left;
				delete toDelete;
			}
			else if (!r->left && r->right) {
				Node* toDelete = r;
				r = r->right;
				delete toDelete;
			}
			else {
				root->data = findMinNode(root->right)->data;
				removeRec(r->right, r->data);
				Node::updateHeight(r);
				Node::balanceRight(r);
			}
		}
		return true;
	} 

	void freeRec(Node* r) {
		if (r == nullptr)
			return;

		freeRec(r->left);
		freeRec(r->right);
		delete r;
	}

public:
	AVLTree() : root{ nullptr }, size{ 0 } {}
	
	// TBI
	AVLTree(const AVLTree<T>& other) = delete;
	AVLTree& operator=(const AVLTree<T>& other) = delete;
	bool contains(const T& elem);

	void insert(const T& elem) {
		insertRec(root, elem);
	}

	bool remove(const T& elem) {
		return removeRec(root, elem);
	}	

	~AVLTree() {
		freeRec(root);
	}

private:

	Node* root;
	size_t size;
};

#endif
