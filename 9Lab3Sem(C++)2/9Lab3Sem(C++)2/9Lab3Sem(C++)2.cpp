// 9Lab3Sem(C++).cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;



struct BinNode
{
	int key;
	BinNode* left;
	BinNode* right;
	BinNode() {
		key = NULL;
		left = NULL;
		right = NULL;
	}
	BinNode(int key) {
		this->key = key;
		this->left = nullptr;
		this->right = nullptr;
	}
	BinNode(BinNode& copy) {
		this->key = copy.key;
		this->left = copy.left;
		this->right = copy.right;
	}
};

class BinTree
{
private:
	void destroy_tree(BinNode* leaf);
	void insert(int key, BinNode* leaf);
	BinNode* search(int key, BinNode* leaf);
	void search(int key, BinNode*& curr, bool& is_left, BinNode*& prev);
	void remove(BinNode*& root, int key);
	void print(const std::string& prefix, const BinNode* node, bool isLeft);
	BinNode* root;
public:
	BinTree() : root(nullptr) {};
	void insert(int key);

	BinNode* search(int key);
	void remove(int key);
	void print();
};

void BinTree::insert(int key, BinNode* leaf)
{
	if (search(key) != nullptr) {
		cout << "This key already exist";
		return;
	}
	BinNode** tmpleaf = &leaf;
	while (*tmpleaf != nullptr) {
		if (key < (*tmpleaf)->key)
		{
			tmpleaf = &(*tmpleaf)->left;
		}
		else if (key >= (*tmpleaf)->key)
		{
			tmpleaf = &(*tmpleaf)->right;
		}
	}
	*tmpleaf = new BinNode(key);
}

BinNode* BinTree::search(int key, BinNode* leaf)
{
	if (leaf != nullptr)
	{
		if (key == leaf->key) {
			return leaf;
		}
		if (key < leaf->key) {
			return search(key, leaf->left);
		}
		else {
			return search(key, leaf->right);
		}
	}
	else return nullptr;
}


void BinTree::search(int key, BinNode*& curr, bool& is_left, BinNode*& prev) {
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



void BinTree::insert(int key)
{
	if (root == nullptr) {
		root = new BinNode(key);
	}
	else {
		insert(key, root);
	}
}
BinNode* BinTree::search(int key)
{
	return search(key, root);
}

void BinTree::print(const string& prefix, const BinNode* node, bool isLeft)
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

void BinTree::print()
{
	print("", root, false);
}

void BinTree::remove(int key) {
	remove(root, key);
}

void BinTree::remove(BinNode*& root, int key)
{

	bool is_left = false;	
	BinNode* prev = nullptr;
	BinNode* curr = root;
	search(key, curr, is_left, prev);
	if (curr == nullptr) {
		return;
	}
	if (prev == nullptr) {
		curr = root;
	}
	else {
		curr = is_left ? prev->left : prev->right;
	}
	if (curr->left == nullptr && curr->right == nullptr) {
		if (curr == root) {
			root = nullptr;
		}
		else {
			delete curr;
			is_left ? prev->left = nullptr : prev->right = nullptr;
		}
	}
	else if (curr->left == nullptr || curr->right == nullptr) {
		BinNode* next = (curr->left) ? curr->left : curr->right;
		if (curr != root)
		{
			if (curr == prev->left) {
				prev->left = next;
			}
			else {
				prev->right = next;
			}
		}
		else {
			root = next;
		}
		delete curr;
	}
	else {
		bool left_shift = false;
		BinNode* next = curr->right;
		BinNode* tmp = curr;
		if (curr != root)
		{
			while (next->left != nullptr) {
				left_shift = true;
				tmp = next;
				next = next->left;
			}

			if (left_shift) {
				tmp->left = next->right;
			}
			else {
				tmp->right = next->right;
			}
				next->right = curr->right;
				next->left = curr->left;
				is_left ? prev->left = next : prev->right = next;

			delete curr;
		}
		else {
			while (next->left != nullptr) {
				left_shift = true;
				tmp = next;
				next = next->left;
			}
			if (left_shift) {
				tmp->left = next->right;
			}
			else {
				tmp->right = next->right;
			}
			next->right = curr->right;
			next->left = curr->left;
			root = next;
			delete curr;
		}
	}
}



bool Interface(BinTree& tree) {

	int action, key, number, value;
	BinNode* find = nullptr;
	std::cout << "Choose your action (from 1 to 4).\n"
		"1 is add elemet to tree\n"
		"2 is remove elemet from tree\n"
		"3 is find value by key\n"
		"4 is print out tree\n"
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
		std::cout << "Input KEY: " << endl;
		cin >> key;
		find = tree.search(key);
		if (find != nullptr) {
			cout << "Value under the key: " << key << " is: " << find->key << endl;
		}
		else {
			cout << "Value under the key: " << key << " doesn't exist!!!!\n";
		}
		break;
	case 4:
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
	BinTree pinguin;
	do {
		result = Interface(pinguin);
	} while (result != false);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

 /*
 1 110
 1 16
 1 112 
 1 12
 1 19
 1 11
 1 15 
 1 18
 1 13
 1 17
 1 14
 1 116
 1 111
 1 9
 1 10
 
 
 1 8
 1 6
 1 11
 1 5
 1 7
 1 10
 1 15
 1 9
 1 2
 1 3
 1 1
 1 4
 1 13
 1 16
 1 12
 4*/
 // 
 //   1. Use the Solution Explorer window to add/manage files
 //   2. Use the Team Explorer window to connect to source control
 //   3. Use the Output window to see build output and other messages
 //   4. Use the Error List window to view errors
 //   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
 //   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
