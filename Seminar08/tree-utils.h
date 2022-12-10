#ifndef TREE_UTIL_IMPL
#define TREE_UTIL_IMPL

#include<iostream>
#include<string>
#include<fstream>

// Важни неща:
template<class T>
struct Tree {
    T data;
    Tree* left;
    Tree* right;

    Tree(T data, Tree<T>* l = nullptr, Tree<T>* r = nullptr) : data {data}, left {l}, right {r} {}
};

template<class T>
void freeTree(Tree<T>* t) {
    if(t == nullptr)
        return;
    freeTree(t->left);
    freeTree(t->right);
    delete t;
}

template<class T>
void insertInBST(Tree<T>*& t, const T& elem) {
    if (t == nullptr) {
        t = new Tree<T>(elem);
        return;
    }
    else if (t->data < elem) {
        insertInBST(t->right, elem);
    }
    else {
        insertInBST(t->left, elem);
    }
}

template<class T>
Tree<T>* getMinRightNode(const Tree<T>* t) {
	assert(t != nullptr);

	Tree<T>* iter = t;

	while (iter->left) {
		iter = iter->left;
	}
	return iter;
}

template<class T>
bool removeElement(Tree<T>*& t, const T& elem) {
	if (t == nullptr)
		return false;

	if (t->data > elem) {
		return removeElement(t->left, elem);
	}
	else if (t->data < elem) {
		return removeElement(t->right, elem);
	}
	else {																// Намерили сме елемента
		if (!t->left && !t->right) {									// Листо
			delete t;
			t = nullptr; //!!
		}
		else if (!t->left && t->right) {								// Има само дясно поддърво
			Tree<T>* toDelete = t;
			t = t->right;
			delete toDelete;
		}
		else if (t->left && !t->right) {								// Има само ляво поддърво
			Tree<T>* toDelete = t;
			t = t->left;
			delete toDelete;
		}
		else {															// Вътрешен връх. 
			T newData = getMinRightNode(t->right)->data;
			t->data = newData;
			removeElement(t->right, newData);
		}
		return true;
	}
}

template<class T>
bool containsBST(const Tree<T>* t, const T& elem) {
	if (t == nullptr)
		return false;

	if (t->data == elem)
		return true;

	if (t->data < elem)
		return containsBST(t->right, elem);

	return containsBST(t->left, elem);
}

// Неща за мое удобство, не е нужно да ги четете:

// Взето от:
// https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
template<class T>
void printBT(const std::string& prefix, const Tree<T>* node, bool isLeft) {
    if(node != nullptr) {
        std::cout << prefix;

        std::cout << (isLeft ? "|--" : "`--" );

        std::cout << node->data << std::endl;

        printBT( prefix + (isLeft ? "|   " : "    "), node->left, true);
        printBT( prefix + (isLeft ? "|   " : "    "), node->right, false);
    }
}

template<class T>
void printTree(const Tree<T>* node) {
    printBT("", node, false);    
}

// Следващите две функции са малко по - красив начин да изпринтим дърво, но го конвертира къмм LaTeX документ
// Когато извикате exportToTex("file.txt") ще ви създаде фейл с код. 
// Пейстнете кода в overleaf.com и ще ви излезе дървото.

// Не е перфектно но пък е по - удобно от конзолата. Това е за демонстрации, не е нужно да го учите или разбирате.
template<class T>
void recFillFileStream(std::ofstream& outFile, const Tree<T>* r) {
	if(r == nullptr)
		return;

	outFile << "[" << r->data << " ";
	recFillFileStream(outFile, r->left);
	recFillFileStream(outFile, r->right);

	outFile << "]";
}

template<class T>
void exportToTex(const Tree<T>* root, const char* filePath) {
	std::ofstream outFile(filePath, std::ios::trunc);

	outFile << "\\documentclass[tikz,border=10pt]{standalone}" << std::endl;
	outFile << "\\usepackage[linguistics]{forest}" << std::endl;
	outFile << "\\begin{document}" << std::endl;
	outFile << "\\begin{forest}" << std::endl;

	recFillFileStream(outFile, root);

	outFile << "\\end{forest}";
	outFile << "\\end{document}";

    outFile.close();
}

#endif