// 11Lab3Sem(C++).cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
struct Node
{
	int key;
	Node* parent;
	char color;
	Node* left;
	Node* right;
	Node(int _key, Node* node, char _color) {
		key = _key;
		parent = node;
		color = _color;
		left = nullptr;
		right = nullptr;
	}
};
class RbTree
{
	Node* root;
	Node* insert(int, Node*, Node*, Node*&);
	void print(const string&, const Node*, bool);
	void fix(Node*);
	void left_rotate(Node*);
	void right_rotate(Node*);
	Node* remove(Node*& leaf, int key);
	void remove_fix(Node*);
	void transplant(Node* u, Node* v);
	Node* min(Node* x);
	void del(int);
	void deleteNode(Node* node, int key);
	/*void deleteNode(Node* v);
	void delfix(Node*);
	Node* successor(Node*);
	Node* replace(Node* x);
	void fixDoubleBlack(Node* x);*/

public:
	RbTree()
	{
		root = nullptr;
	}
	void insert(int);
	void print();
	void remove(int key);
};
void RbTree::left_rotate(Node* node) {
	Node* prev = node;
	Node* curr = node->right;

	prev->right = curr->left;
	curr->left == nullptr ? 0 : curr->left->parent = prev;
	curr->left = prev;
	curr->parent = prev->parent;
	prev->parent = curr;
	if (root == prev) {
		root = curr;
	}
	else {
		curr->parent->left == prev ? curr->parent->left = curr : curr->parent->right = curr;
	}
}


void RbTree::right_rotate(Node* node) {

	Node* prev = node;
	Node* curr = node->left;

	prev->left = curr->right;
	curr->right == nullptr ? 0 : curr->right->parent = prev;
	curr->right = prev;
	curr->parent = prev->parent;
	prev->parent = curr;
	if (root == prev) {
		root = curr;
	}
	else {
		curr->parent->left == prev ? curr->parent->left = curr : curr->parent->right = curr;
	}
}
void RbTree::fix(Node* node) {
	if (node == nullptr) {
		return;
	}
	if (root == node)
	{
		node->color = 'B';
		return;
	}
	while (node->parent != nullptr && node->color == 'R' && node->parent->color == 'R')
	{
		Node* grand_father = node->parent->parent;
		if (grand_father->left == node->parent)
		{
			if (grand_father->right != nullptr && grand_father->right->color == 'R') {
				grand_father->right->color = 'B';
				grand_father->left->color = 'B';
				grand_father->color = 'R';
				node = grand_father;
			}
			else if (grand_father->right == nullptr || (grand_father->right != nullptr && grand_father->right->color == 'B'))
			{
				Node* father = node->parent;
				if (node->parent->right == node) {
					left_rotate(father);
					father = node;
				}
				father->color = 'B';
				grand_father->color = 'R';
				right_rotate(grand_father);

			}
		}
		else
		{
			if (grand_father->left != nullptr && grand_father->left->color == 'R') {
				grand_father->right->color = 'B';
				grand_father->left->color = 'B';
				grand_father->color = 'R';
				node = grand_father;
			}
			else if (grand_father->left == nullptr || (grand_father->left != nullptr && grand_father->left->color == 'B'))
			{
				Node* father = node->parent;
				if (node->parent->left == node) {
					right_rotate(father);
					father = node;
				}
				father->color = 'B';
				grand_father->color = 'R';
				left_rotate(grand_father);

			}
		}
		root->color = 'B';


	}
}

Node* RbTree::insert(int key, Node* leaf, Node* parent, Node*& added)
{
	if (leaf != nullptr) {
		if (key < leaf->key)
		{
			leaf->left = insert(key, leaf->left, leaf, added);
		}
		else if (key >= leaf->key)
		{
			leaf->right = insert(key, leaf->right, leaf, added);
		}
	}
	else {
		leaf = new Node(key, parent, 'R');
		added = leaf;
		return leaf;
	}
	return leaf;
}
void RbTree::insert(int key)
{
	if (root == nullptr) {
		root = new Node(key, nullptr, 'B');
	}
	else {
		Node* added = nullptr;
		insert(key, root, root, added);
		fix(added);
	}
}
void RbTree::print(const string& prefix, const Node* node, bool isLeft)
{
	if (node != nullptr)
	{
		cout << prefix;
		cout << (isLeft ? "|--" : "L--");
		if (node->color == 'B') {
			cout << "\033[0m" << node->key << endl;
		}
		else {
			cout << "\033[31m" << node->key << endl;
		}
		cout << "\033[0m";
		print(prefix + (isLeft ? "|   " : "    "), node->left, true);
		print(prefix + (isLeft ? "|   " : "    "), node->right, false);

	}
}
void RbTree::print()
{
	if (root == nullptr) {
		cout << "Tree is empty!!!\n";
	}
	else {
		print("", root, false);
	}
}
void RbTree::remove_fix(Node* node) {
	Node* father;
	Node* successor;
	Node* source = node;
	while (node != root && node->color == 'B')
	{
		father = node->parent;
		if (father != nullptr && father->left == node) {
			if (father->right->color == 'R') {
				father->color = 'R';
				father->right->color = 'B';
				left_rotate(father);
			
			}
			else {
				successor = father->right;
				if ((successor->right == nullptr || successor->right->color == 'B') && (successor->left == nullptr || successor->left->color == 'B')) {
					successor->color = 'R';
					if (father->color == 'B') {
						node = node->parent;
					}
					else {
						father->color = 'B';
						break;
					}
				}
				else {
					if ((successor->right == nullptr || successor->right->color == 'B') && successor->left->color == 'R') {
						successor->color = 'R';
						successor->left->color = 'B';
						right_rotate(successor);
						successor = successor->parent;
					}

					successor->color = successor->parent->color;
					successor->parent->color = 'B';
					successor->right ? successor->right->color = 'B':0;

					left_rotate(father);

					node = root;
				}
			}
		}
		else {
			if (father->left->color == 'R') {
				father->color = 'R';
				father->left->color = 'B';
				right_rotate(father);
				
			}
			else {
				successor = father->left;
				if ((successor->right == nullptr || successor->right->color == 'B') && (successor->left == nullptr || successor->left->color == 'B')) {
					successor->color = 'R';
					if (father->color == 'B') {
						node = node->parent;
					}
					else {
						father->color = 'B';
						break;
					}
				}
				else {
					if ((successor->left == nullptr || successor->left->color == 'B') && successor->right->color == 'R') {
						successor->color = 'R';
						successor->right ? successor->right->color = 'B' : 0;
						left_rotate(successor);
						successor = successor->parent;
					}

					successor->color = successor->parent->color;
					successor->parent->color = 'B';
					successor->left? successor->left->color = 'B':0;

					right_rotate(father);

					node = root;
				}
			}

		}
	}
	root->color = 'B';
}
void RbTree::transplant(Node* u, Node* v) {
	if (u->parent == nullptr) {
		root = v;
	}
	else if (u == u->parent->left) {
		u->parent->left = v;
	}
	else {
		u->parent->right = v;
	}
	if (v != nullptr) {
		v->parent = u->parent;
	}
}

Node* RbTree::min(Node* x) {
	while (x->right != nullptr) {
		x = x->right;
	}
	return x;
}


Node* RbTree::remove(Node*& leaf, int key)
{
	if (leaf == nullptr) {
		cout << "Key doesn't exist!!!\n";
		return root;
	}
	if (key < leaf->key) {
		root = remove(leaf->left, key);
	}
	else if (key > leaf->key) {
		root = remove(leaf->right, key);
	}
	else {
		if ((leaf->left == nullptr) || (leaf->right == nullptr)) {
			Node* temp = leaf->left ? leaf->left : leaf->right;


			if (temp == nullptr) {
				if (leaf->color == 'B') {
 					remove_fix(leaf);
				}
				temp = leaf;
				leaf = nullptr;
			}
			else {
				temp->color = leaf->color;
				temp->parent = leaf->parent;
				*leaf = *temp;
			}
			delete temp;

		}
		else {

			Node* current = leaf->left;
			while (current->right != nullptr) {
				current = current->right;
			}
			Node* temp = current;
			leaf->key = temp->key;
			root = remove(leaf->left, temp->key);

		}
	}
	return root;
}


void RbTree::remove(int key)
{
	remove(root, key);
}

bool Interface(RbTree& tree) {

	int action, key, number, value;
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
	RbTree fork;
	do {
		result = Interface(fork);
	} while (result != false);
	/*fork.insert(9);
	fork.print();
	cout << "========================\n";
	fork.insert(15);
	fork.print();
	cout << "========================\n";
	fork.insert(17);
	fork.print();
	cout << "========================\n";
	fork.insert(4);
	fork.print();
	cout << "========================\n";
	fork.insert(7);
	fork.print();
	cout << "========================\n";
	fork.insert(8);
	fork.print();
	cout << "========================\n";
	fork.insert(14);
	fork.print();
	cout << "========================\n";
	fork.insert(6);
	fork.print();
	cout << "========================\n";
	fork.insert(11);
	fork.print();
	cout << "========================\n";
	fork.insert(13);
	fork.print();
	cout << "========================\n";
	fork.remove(4);
	fork.print();
	cout << "========================\n";
	fork.remove(6);
	fork.print();
	cout << "========================\n";
	fork.remove(9);
	fork.print();
	cout << "========================\n";
	fork.remove(8);
	fork.print();*/
}


//1 6
//1 4
//1 9
//1 5
//1 8
//1 12
//1 7
//1 10
//1 14
//1 11
//1 3
//1 2
//2 6
//2 8
//2 7
//2 2
//2 14
//2 9

//1 7 3
//1 14 3
//1 15 3
//1 24 3
//1 18 3
//1 20 3
//1 35 3
//1 1 3
//1 5 3
//1 9 3
//2 35 3
//2 15 3
//2 7 3
//2 20 3
//2 14 3
//1 3 3
//1 10 3


