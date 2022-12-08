#include"../Seminar08/tree-utils.h"
#include<optional>
#include<vector>
#include<assert.h>
#include<algorithm>

template<class T>
std::optional<T> getMax(const Tree<T>* t) {
	if (t == nullptr)
		return {}; // Няма стойност

	T res = t->data;

	std::optional<T> left = getMax(t->left);
	std::optional<T> right = getMax(t->right);

	if (left.has_value())
		res = std::max(res, left.value());

	if (right.has_value())
		res = std::max(res, right.value());

	return res;
}

bool isBSTRec(const Tree<int>* t, int min, int max) {
	if (t == nullptr)
		return true;

	if (t->data < min || t->data > max)
		return false;

	return isBSTRec(t->left, min, t->data) && isBSTRec(t->right, t->data, max);
}

bool isBST(const Tree<int>* t) {
	return isBSTRec(t, INT_MIN, INT_MAX);
}

template<class T>
Tree<T>* buildFromRec(const std::vector<T>& v, int start, int end) {
	if (end < start)
		return nullptr;

	int mid = (end - start) / 2 + start;

	return new Tree<T>(v[mid], buildFromRec(v, start, mid - 1), buildFromRec(v, mid + 1, end));
}

template<class T>
Tree<T>* buildFrom(const std::vector<T>& v) {
	return buildFromRec(v, 0, v.size() - 1);
}

template<class T>
bool isSameTree(const Tree<T>* fst, const Tree<T>* snd) {
	if (!fst && !snd)
		return true;

	if ((fst && !snd) || (!fst && snd) || fst->data != snd->data)
		return false;

	return isSameTree(fst->left, snd->left) && isSameTree(fst->right, snd->right);
}

template<class T>
Tree<T>* clone(const Tree<T>* t) {
	if (!t)
		return nullptr;

	return new Tree<T>(t->data, clone(t->left), clone(t->right));
}

template<class T>
void rotateLeft(Tree<T>*& root) {
	assert(root->right != nullptr);

	Tree<T>* originalRight = root->right;
	root->right = originalRight->left;
	originalRight->left = root;
	root = originalRight;
}

template<class T>
void rotateRight(Tree<T>*& root) {
	assert(root->left != nullptr);

	Tree<T>* originalLeft = root->left;
	root->left = originalLeft->right;
	originalLeft->right = root;
	root = originalLeft;
}

void rotationsTests() {
	std::vector<int> v;
	for (size_t i = 0; i < 100; i++)
		v.push_back(rand() % 100);

	std::sort(v.begin(), v.end());

	Tree<int>* example = buildFrom(v);
	Tree<int>* exampleClone = clone(example);

	// Тестваме лява ротация:
	// Тука не правя проверки за nullptr понеже не е това целта на този пример
	Tree<int>* alpha = clone(example->left);
	Tree<int>* beta  = clone(example->right->left);
	Tree<int>* gamma = clone(example->right->right);

	rotateLeft(example);

	assert(isSameTree(alpha, example->left->left));
	assert(isSameTree(beta, example->left->right));
	assert(isSameTree(gamma, example->right));

	freeTree(alpha); freeTree(beta); freeTree(gamma);
	
	// Тествам дясна ротация
	alpha = clone(example->left->left);
	beta = clone(example->left->right);
	gamma = clone(example->right);

	rotateRight(example);

	assert(isSameTree(alpha, example->left));
	assert(isSameTree(beta, example->right->left));
	assert(isSameTree(gamma, example->right->right));

	freeTree(alpha); freeTree(beta); freeTree(gamma);

	// Лявата ротация е симетрична на дясната следователно като направим лява + дясна трябва да остане същото дърво
	assert(isSameTree(example, exampleClone));

	freeTree(example);
	freeTree(exampleClone);
}

int main() {
	rotationsTests();
}