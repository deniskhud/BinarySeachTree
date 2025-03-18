#include <iostream>
#include<cassert>
#include<stdexcept>
using namespace std;

template<typename T>
class BinarySearchTree {
public:
	BinarySearchTree();
	~BinarySearchTree();

	void insert(T value);
	void remove(T value);
	void clear();
	bool find(T value);
	
	void inorder();

	T& min_element();
	T& max_element();
	
private:
	
	class TreeNode {
	public:
		T value;
		TreeNode* left;
		TreeNode* right;
		TreeNode(T value, TreeNode* left = nullptr, TreeNode* right = nullptr)
		{
			this->left = left;
			this->right = right;
			this->value = value;
		}
	};
	TreeNode* root;
	TreeNode* insertRec(TreeNode* node, T value);
	TreeNode* removeRec(TreeNode* node, T value);
	TreeNode* findMin(TreeNode* node);	
	void inorderRec(TreeNode* node);
	void clearRec(TreeNode* node);

};

int main()
{// Test 1: Inserting and traversing a tree
	BinarySearchTree<int> tree;
	tree.insert(50);
	tree.insert(15);
	tree.insert(78);
	tree.insert(100);
	tree.insert(10);
	tree.insert(25);
	cout << "Inorder traversal (Expected: 10 15 25 50 78 100): ";
	tree.inorder(); // Expected result: 10 15 25 50 78 100
	cout << endl;

	// Test 2: Item Search
	assert(tree.find(50) == true);  // Element 50 must be found
	assert(tree.find(15) == true);  // Element 15 must be found
	assert(tree.find(100) == true); // Element 100 must be found
	assert(tree.find(200) == false); // Element 200 should not be found

	// Test 3: Finding the minimum and maximum elements
	assert(tree.min_element() == 10);  // The minimum element is 10
	assert(tree.max_element() == 100); // The maximum element is 100

	// Test 4: Deleting an item
	tree.remove(15);
	cout << "Inorder traversal after removing 15 (Expected: 10 25 50 78 100): ";
	tree.inorder(); // Expected result: 10 25 50 78 100
	cout << endl;

	// Test 5: Cleaning the tree
	tree.clear();
	cout << "Inorder traversal after clearing the tree (Expected: nothing): ";
	tree.inorder(); // Should output nothing, the tree is cleared
	cout << endl;

	// Test 6: An attempt to get the minimum and maximum elements on an empty tree
	try {
		tree.min_element();
	}
	catch (const runtime_error& e) {
		cout << "Caught expected exception for empty tree on min_element: " << e.what() << endl;
	}

	try {
		tree.max_element();
	}
	catch (const runtime_error& e) {
		cout << "Caught expected exception for empty tree on max_element: " << e.what() << endl;
	}

	cout << "All tests passed!" << endl;
	return 0;
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree()
{
}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
	clear();
}


template<typename T>
void BinarySearchTree<T>::insert(T value)
{
	root = insertRec(root, value);
}
template<typename T>
typename BinarySearchTree<T>::TreeNode* BinarySearchTree<T>::insertRec(TreeNode* node, T value) 
{
	if (!node) {
		return new TreeNode(value);
	}

	if (value < node->value) {
		node->left = insertRec(node->left, value);
	}
	else if (value > node->value) {
		node->right = insertRec(node->right, value);
	}
	return node;
}


template<typename T>
void BinarySearchTree<T>::clear()
{
	clearRec(root);
	root = nullptr;
}
template<typename T>
void BinarySearchTree<T>::clearRec(TreeNode* node)
{
	if (!node) return;
	clearRec(node->left);
	clearRec(node->right);

	delete node;
}

template<typename T>
void BinarySearchTree<T>::remove(T value)
{
	root = removeRec(root, value);
}

template<typename T>
typename BinarySearchTree<T>::TreeNode* BinarySearchTree<T>::removeRec(TreeNode* node, T value)
{
	if (node == nullptr) return nullptr;

	if (value < node->value) {
		node->left = removeRec(node->left, value);
	}
	else if (value > node->value) {
		node->right = removeRec(node->right, value);
	}
	else {
		if (!node->left && !node->right) {
			delete node;
			return nullptr;
		}
		else if (!node->left) {
			TreeNode* temp = node->right;
			delete node;
			return temp;
		}
		else if (!node->right) {
			TreeNode* temp = node->left;
			delete node;
			return temp;
		}
		else {
			TreeNode* minNode = findMin(node->right);
			node->value = minNode->value;
			node->right = removeRec(node->right, minNode->value);
		}
	}
	return node;
}


template<typename T>
typename BinarySearchTree<T>::TreeNode* BinarySearchTree<T>::findMin(TreeNode* node) {
	while (node && node->left) {
		node = node->left;
	}
	return node;
}





template<typename T>
bool BinarySearchTree<T>::find(T value)
{
	if (!root) return false;
	TreeNode* current = root;
	while (current) {
		if (current->value > value) {
			current = current->left;
		}
		else if (current->value < value) {
			current = current->right;
		}
		else {
			return true;
		}
	}
	return false;
}





template<typename T>
void BinarySearchTree<T>::inorder()
{
	inorderRec(root);
	cout << endl;
}

template<typename T>
void BinarySearchTree<T>::inorderRec(TreeNode* node)
{
	if (!node) return;
	inorderRec(node->left);
	cout << node->value << " ";
	inorderRec(node->right);
}


template<typename T>
T& BinarySearchTree<T>::min_element()
{
	if (!root) {
		throw runtime_error("Tree is empty");
	}
	TreeNode* current = root;
	while (current && current->left) {
		current = current->left;
	}
	return current->value;
}

template<typename T>
T& BinarySearchTree<T>::max_element()
{
	if (!root) {
		throw runtime_error("Tree is empty");
	}
	TreeNode* current = root;
	while (current && current->right) {
		current = current->right;
	}
	return current->value;
	
}
