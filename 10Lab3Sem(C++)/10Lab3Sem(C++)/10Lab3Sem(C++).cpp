// 10Lab3Sem(C++).cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

struct ANode {
	int key;
	ANode* left;
	ANode* right;
	int height;
	ANode(int t_key) {
		key = t_key;
		left = NULL;
		right = NULL;
		height = 0;
	}
};

class AVLTree {
private:
	ANode* root;
	int  cal_height(ANode* node);
	ANode* left_rotate(ANode* node);
	ANode* right_rotate(ANode* node);
	ANode* double_left_rotate(ANode* node);
	ANode* double_right_rotate(ANode* node);
	ANode* choose_rotate(ANode* node);
	ANode* insert(int key, ANode* leaf);
	ANode* remove(ANode*& leaf, int key);
	void print(const string& prefix, const ANode* node, bool isLeft);
	void search(int key, ANode*& curr, bool& is_left, ANode*& prev);
public:
	AVLTree() {
		root = NULL;
	}
	int difference(ANode*);
	int balance_f(ANode* node);
	void insert(int key);
	void print();
	void remove(int key);


};


int  AVLTree::cal_height(ANode* node) {
	if (node == NULL) {
		return 0;
	}
	else
	{
		int left_side;
		int right_side;
		left_side = cal_height(node->left);
		right_side = cal_height(node->right);
		return left_side > right_side ? left_side + 1 : right_side + 1;
	}
}
ANode* AVLTree::left_rotate(ANode* node) {
	ANode* prev = node;
	ANode* curr = node->right;

	prev->right = curr->left;
	curr->left = prev;

	return curr;
}


ANode* AVLTree::right_rotate(ANode* node) {

	ANode* prev = node;
	ANode* curr = node->left;


	prev->left = curr->right;
	curr->right = prev;

	return curr;
}


ANode* AVLTree::double_left_rotate(ANode* node) {
	ANode* prev = node;
	ANode* curr = node->right;
	prev->right = right_rotate(curr);
	prev = left_rotate(prev);
	return prev;

}

ANode* AVLTree::double_right_rotate(ANode* node) {
	ANode* prev = node;
	ANode* curr = node->left;
	prev->left = left_rotate(curr);
	prev = right_rotate(prev);
	return prev;

}

int AVLTree::balance_f(ANode* node) {

	int left = cal_height(node->left) - 1;
	int right = cal_height(node->right) - 1;
	return left - right;

}



ANode* AVLTree::choose_rotate(ANode* node) {
	int balance = balance_f(node);
	if (balance == 2) {
		if (cal_height(node->left->left) >= cal_height(node->left->right)) {
			node = right_rotate(node);
		}
		else {
			node = double_right_rotate(node);
		}
	}
	else if (balance == -2) {
		if (cal_height(node->right->left) <= cal_height(node->right->right)) {
			node = left_rotate(node);
		}
		else {
			node = double_left_rotate(node);
		}
	}
	return node;
}


ANode* AVLTree::insert(int key, ANode* leaf)
{
	if (leaf != nullptr) {
		if (key < leaf->key)
		{
			leaf->left = insert(key, leaf->left);
		}
		else if (key >= leaf->key)
		{
			leaf->right = insert(key, leaf->right);
		}
	}
	else {
		leaf = new ANode(key);
		return leaf;
	}
	if (leaf != root) {
		leaf = choose_rotate(leaf);
	}
	else {
		root = choose_rotate(leaf);
	}
	return leaf;
}
ANode* AVLTree::remove(ANode*& leaf, int key)
{
	// Find the node and delete it
	if (leaf == NULL)
		return leaf;
	if (key < leaf->key)
		leaf->left = remove(leaf->left, key);
	else if (key > leaf->key)
		leaf->right = remove(leaf->right, key);
	else {
		if ((leaf->left == NULL) || (leaf->right == NULL)) {
			ANode* temp = leaf->left ? leaf->left : leaf->right;
			if (temp == NULL) {
				temp = leaf;
				leaf = NULL;
			}
			else
				*leaf = *temp;
			delete temp;
		}
		else {
			ANode* current = leaf->right;
			while (current->left != NULL) {
				current = current->left;
			}
			ANode* temp = current;
			leaf->key = temp->key;
			leaf->right = remove(leaf->right, temp->key);
		}
	}

	if (leaf == NULL)
		return leaf;
	// Update the balance factor of each node and
	// balance the tree
	if (leaf != root) {
		leaf = choose_rotate(leaf);
	}
	else {
		root = choose_rotate(leaf);
	}
	return leaf;
}

void AVLTree::search(int key, ANode*& curr, bool& is_left, ANode*& prev) {
	while (curr != nullptr && curr->key != key)
	{
		prev = curr;
		if (key < curr->key) {
			curr = curr->left;
		}
		else {
			curr = curr->right;
		}
	}
	if (prev != nullptr) {
		is_left = prev->left == curr ? true : false;
	}
}
void AVLTree::insert(int key)
{
	if (root == nullptr) {
		root = new ANode(key);
	}
	else {
		insert(key, root);
	}
}


void AVLTree::print(const string& prefix, const ANode* node, bool isLeft)
{
	if (node != nullptr)
	{
		cout << prefix;
		cout << (isLeft ? "|--" : "L--");

		cout << node->key << endl;

		print(prefix + (isLeft ? "|   " : "    "), node->left, true);
		print(prefix + (isLeft ? "|   " : "    "), node->right, false);

	}
}

void AVLTree::print()
{
	print("", root, false);
}

void AVLTree::remove(int key) {
	remove(root, key);
}

bool Interface(AVLTree& tree) {

	int action, key, number, value;
	ANode* find = nullptr;
	std::cout << "Choose your action (from 1 to 3).\n"
		"1 is add elemet to tree\n"
		"2 is remove elemet from tree\n"
		"3 is print out tree\n"
		"0 if you want to finish the program " << endl;

	cin >> action;
	cout << endl;
	switch (action) {
	case 1:

		cout << "Enter key: " << endl;
		cin >> key;
		tree.insert(key);
		break;
	case 2:
		std::cout << "Input KEY: " << endl;
		cin >> key;
		tree.remove(key);
		break;
	case 3:
		tree.print();
		break;
	case 0:
		std::cout << "Thanks for using, bye bye";
		return false;
		break;
	default:
		cout << "Wrong number!!!";
	}
	cout << "\n\n";
	return true;
}
int main()
{

	bool result;
	AVLTree beer;
	do {
		result = Interface(beer);
	} while (result != false);
	/*beer.insert(20);
	beer.print();
	cout << "-----------------------------------\n";
	beer.insert(15);
	beer.print();
	cout << "-----------------------------------\n";
	beer.insert(54);
	beer.print();
	cout << "-----------------------------------\n";
	beer.insert(18);
	beer.print();
	cout << "-----------------------------------\n";
	beer.insert(24);
	beer.print();
	cout << "-----------------------------------\n";
	beer.insert(76);
	beer.print();
	cout << "-----------------------------------\n";
	beer.insert(12);
	beer.print();
	cout << "-----------------------------------\n";
	beer.insert(7);
	beer.print();
	cout << "-----------------------------------\n";
	beer.insert(5);
	beer.print();
	cout << "-----------------------------------\n";
	beer.insert(14);
	beer.print();
	cout << "-----------------------------------\n";
	beer.insert(19);
	beer.print();
	cout << "-----------------------------------\n";
	cout << "===============REMOVE==============\n";
	beer.remove(15);
	beer.print();
	cout << "-----------------------------------\n";
	cout << "===============REMOVE==============\n";
	beer.remove(19);
	beer.print();
	cout << "-----------------------------------\n";*/



	/*beer.insert(7);
	beer.print();
	cout << "-----------------------------------\n";
	beer.insert(3);
	beer.print();
	cout << "-----------------------------------\n";
	beer.insert(18);
	beer.print();
	cout << "-----------------------------------\n";
	beer.insert(15);
	beer.print();
	cout << "-----------------------------------\n";
	beer.insert(20);
	beer.print();
	cout << "-----------------------------------\n";
	beer.insert(17);
	beer.print();
	cout << "-----------------------------------\n";*/

	/*beer.insert(10);
	beer.print();
	cout << "-----------------------------------\n";
	beer.insert(4);
	beer.print();
	cout << "-----------------------------------\n";
	beer.insert(15);
	beer.print();
	cout << "-----------------------------------\n";
	beer.insert(3);
	beer.print();
	cout << "-----------------------------------\n";
	beer.insert(7);
	beer.print();
	cout << "-----------------------------------\n";
	beer.insert(5);
	beer.print();
	cout << "-----------------------------------\n";
	beer.insert(18);
	beer.print();
	cout << "-----------------------------------\n";
	beer.insert(20);
	beer.print();
	cout << "-----------------------------------\n";
	cout << "===============REMOVE==============\n";
	beer.remove(10);
	beer.print();
	cout << "-----------------------------------\n";
	beer.insert(17);
	beer.print();
	cout << "-----------------------------------\n";
	cout << "===============REMOVE==============\n";
	beer.remove(5);
	beer.print();
	cout << "-----------------------------------\n";
	cout << "===============REMOVE==============\n";
	beer.remove(4);
	beer.print();
	cout << "-----------------------------------\n";*/






	/*beer.insert(4);
	beer.print();
	cout << "-----------------------------------\n";
	beer.insert(5);
	beer.print();
	cout << "-----------------------------------\n";
	beer.insert(7);
	beer.print();
	cout << "-----------------------------------\n";
	beer.insert(2);
	beer.print();
	cout << "-----------------------------------\n";
	beer.insert(1);
	beer.print();
	cout << "-----------------------------------\n";
	beer.insert(3);
	beer.print();
	cout << "-----------------------------------\n";
	beer.insert(6);
	beer.print();
	cout << "-----------------------------------\n";*/
}
1 7 
1 3
1 17
1 2
1 5
1 9
1 23
1 4
1 6
1 16


1 9
1 7
1 17
1 4
1 8
1 16
1 23
1 3 
1 5

