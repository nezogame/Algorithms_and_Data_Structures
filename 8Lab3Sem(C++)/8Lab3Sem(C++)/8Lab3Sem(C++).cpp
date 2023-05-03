#include <iostream>
#include "string"
#include"string.h"
using namespace std;

struct TreeNode {
	int number;
	int value;
	TreeNode* next;
	TreeNode* next_level;
	TreeNode() {
		number = NULL;
		value = NULL;
	}
	TreeNode(int number, int value) {
		this->number = number;
		this->value = value;
		this->next_level = nullptr;
		this->next = nullptr;
	}
};


//
//void SingleLinkedList::push(int value) {
//	if (head == nullptr) {
//		head = new TreeNode(value);
//		head->next = nullptr;
//		/*current = head;*/
//		size++;
//	}
//	else {
//	/*	current->next = new TreeNode(value);
//		current->next->next = nullptr;
//		current = current->next;*/
//		size++;
//	}
//}
//void SingleLinkedList::removeAt(int index) {
//	if (index > size || index < 1) {
//		cout << "You enter WRONG index for function removeAt. Min idex is: 1, Max index are: " << size << "\n\n";
//		return;
//	}
//	else if (index == 1) {
//		TreeNode* next = nullptr;
//		next = head->next;
//		delete head;
//		head = next;
//		size--;
//
//	}
//	else if (index == size) {
//		TreeNode* next = head;
//		for (int i = 0; i < size - 2; i++) {
//			next = next->next;
//		}
//		delete next->next;
//		next->next = nullptr;
//		size--;
//
//	}
//	else {
//		TreeNode* next = head, * current = nullptr;
//
//		for (int i = 0; i < index - 1; i++) {
//			current = next;
//			next = next->next;
//
//		}
//		current->next = next->next;
//		delete next;
//		size--;
//	}
//}




class GeneralTree {
	TreeNode* root;
public:
	GeneralTree() : root(NULL) {};
	GeneralTree(int r_number, int r_value) {
		root = new TreeNode(r_number, r_value);
	}
	TreeNode* get_root();
	TreeNode* find(TreeNode* branch, int number, TreeNode* pref_branch);
	void add_branch(int number, int value, int new_number);
	void print_tree(TreeNode* branch);
	void pre_order(TreeNode* branch);
	void post_order(TreeNode* branch);
	void in_order(TreeNode* branch, TreeNode* remind);
	void remove(int index);
	void remove_helper(TreeNode* branch, int& count);
	TreeNode* find_remove(TreeNode* branch, int number, TreeNode* pref_branch, bool& stop);
};

TreeNode* GeneralTree::find(TreeNode* branch, int number, TreeNode* pref_branch)
{
	bool flag = false;
	if (branch->number == number) {
		return (branch);
	}
	if ((branch)->next_level != nullptr) {
		branch = find((branch)->next_level, number, branch);
	}
	if ((branch)->number == number) {
		return (branch);
	}
	if ((branch)->next != nullptr) {
		branch = find((branch)->next, number, branch);
	}
	if ((branch)->number == number) {
		flag = true;
	}
	return flag ? branch : pref_branch;

}
void GeneralTree::add_branch(int number, int value, int new_number) {
	
	bool flag = false;
	if (root == nullptr) {
		root = new TreeNode(new_number, value);
		return;
	}
	TreeNode* tmp = find(root, new_number, root);
	if (tmp->number == new_number) {
		cout << "This node alredy exist!!!\n";
		return;
	}
	TreeNode* root_ref = root;
	TreeNode* prev = nullptr;
	TreeNode* curr = find(root_ref, number, root_ref);
	if (curr->number == number) {
		prev = curr;
		curr = curr->next_level;
		while (curr != nullptr) {
			prev = curr;
			curr = curr->next;
			flag = true;
		}
		if (flag) {
			curr = new TreeNode(new_number, value);
			prev->next = curr;
		}
		else {
			curr = new TreeNode(new_number, value);
			prev->next_level = curr;
		}
	}
	else {
		cout << "wrong number\n";
	}
}
void  GeneralTree::print_tree(TreeNode* branch) {
	cout << branch->value;
	if ((branch)->next_level != nullptr) {
		cout << "{ ";
		print_tree((branch)->next_level);
		cout << "} ";
	}
	else {
		cout << "{ ";
		cout << "} ";
	}
	if ((branch)->next != nullptr) {
		print_tree((branch)->next);
	}
}
TreeNode* GeneralTree::find_remove(TreeNode* branch, int number, TreeNode* pref_branch, bool& stop)
{
	bool flag = false;
	if (stop) {
		return branch;
	}
	else if (branch->number == number) {
		stop = true;
		return (pref_branch);
	}
	if ((branch)->next_level != nullptr) {
		branch = find_remove((branch)->next_level, number, branch, stop);
	}
	if (stop) {
		return branch;
	}
	else if (branch->number == number) {
		stop = true;
		return (pref_branch);
	}
	if ((branch)->next != nullptr) {
		branch = find_remove((branch)->next, number, branch, stop);
	}
	if (branch->number == number || stop) {
		flag = true;
	}
	return flag ? branch : pref_branch;

}
void GeneralTree::remove_helper(TreeNode* branch, int& count) {
	int curr = count;
	count++;
	if ((branch)->next_level != nullptr) {
		remove_helper(branch->next_level, count);
	}
	if (curr != 0) {
		if ((branch)->next != nullptr) {
			remove_helper((branch)->next, count);
		}
	}
	delete[] branch;
}
void  GeneralTree::remove(int index) {
	int first = 0;
	bool flag = false, right = false;
	TreeNode* searched_t_node = find_remove(root, index, root, flag);


	TreeNode* tmp = nullptr;
	if (searched_t_node->next->number == index) {
		tmp = searched_t_node->next;
		right = true;
	}
	else {
		tmp = searched_t_node->next_level;
	}
	TreeNode* next = tmp->next;
	remove_helper(tmp, first);
	if (right) {
		searched_t_node->next = next;
	}
	else {
		searched_t_node->next_level = next;
	}

}
void GeneralTree::pre_order(TreeNode* branch) {
	cout << branch->value << " ";
	if ((branch)->next_level != nullptr) {
		pre_order((branch)->next_level);
	}
	if ((branch)->next != nullptr) {
		pre_order((branch)->next);
	}
}
void  GeneralTree::post_order(TreeNode* branch) {
	if ((branch)->next_level != nullptr) {
		post_order((branch)->next_level);
		cout << branch->value << " ";
	}
	else {
		cout << branch->value << " ";
	}
	if ((branch)->next != nullptr) {
		post_order((branch)->next);

	}

}
void  GeneralTree::in_order(TreeNode* branch, TreeNode* remind) {
	if ((branch)->next_level != nullptr) {
		TreeNode* tmp = (branch);
		in_order((branch)->next_level, tmp);
	}
	if (branch->value == remind->next_level->value && branch->next_level == nullptr) {
		cout << branch->value << " " << remind->value << " ";
	}
	else if (branch->value == remind->next_level->value) {
		cout << remind->value << " ";
	}
	else if (branch->next_level != nullptr) {
	}
	else {
		cout << branch->value << " ";
	}


	if ((branch)->next != nullptr) {
		in_order((branch)->next, remind);
	}

}
TreeNode* GeneralTree::get_root() {
	return root;

}

bool Interface(GeneralTree& tree) {

	int action, key, number, value;
	TreeNode* find = nullptr;
	std::cout << "Choose your action (from 1 to 5).\n"
		"1 is add elemet to tree\n"
		"2 is remove elemet from tree\n"
		"3 is find value by key\n"
		"4 is print out tree\n"
		"5 is print out traversals\n"
		"0 if you want to finish the program " << endl;

	cin >> action;
	cout << endl;
	switch (action) {
	case 1:

		std::cout << "Enter ancestor key: " << endl;
		cin >> key;
		std::cout << "\nEnter descendant value: " << endl;
		cin >> value;
		std::cout << "\nEnter descendant key: " << endl;
		cin >> number;
		tree.add_branch(key, value, number);
		break;
	case 2:
		std::cout << "Input KEY: " << endl;
		cin >> key;
		tree.remove(key);
		break;
	case 3:
		std::cout << "Input KEY: " << endl;
		cin >> key;
		find = tree.find(tree.get_root(), key, tree.get_root());
		if (find != nullptr) {
			cout << "Value under the key: " << key << " is: " << find->value << endl;
		}
		else {
			cout << "Value under the key: " << key << " doesn't exist!!!!\n";
		}
		break;
	case 4:
		tree.print_tree(tree.get_root());
		break;
	case 5:
		cout << "\n----------\n";
		tree.pre_order(tree.get_root());
		cout << "\n----------\n";
		tree.post_order(tree.get_root());
		cout << "\n----------\n";
		tree.in_order(tree.get_root(), tree.get_root());
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
	GeneralTree pinguin;
	do {
		result = Interface(pinguin);
	} while (result != false);

	/*pinguin.add_branch(0, 1, 1);
	pinguin.add_branch(1, 5, 5);
	pinguin.add_branch(1, 2, 2);
	pinguin.add_branch(5, 3, 3);
	pinguin.add_branch(5, 4, 4);
	pinguin.add_branch(5, 6, 6);
	pinguin.add_branch(2, 8, 8);
	pinguin.add_branch(2, 9, 9);
	pinguin.add_branch(6, 7, 7);
	pinguin.print_tree(pinguin.get_root());
	cout << "\n----------\n";
	pinguin.pre_order(pinguin.get_root());
	cout << "\n----------\n";
	pinguin.post_order(pinguin.get_root());
	cout << "\n----------\n";
	pinguin.in_order(pinguin.get_root(), pinguin.get_root());*/
	/*pinguin.remove(6);
	cout << "\n----------\n";
	pinguin.print_tree(pinguin.get_root());
	TreeNode* tmp = pinguin.find(pinguin.get_root(), 8, pinguin.get_root());
	cout << tmp->value;*/

}

//1 0 1 1
//1 1 5 5
//1 1 2 2
//1 5 3 3
//1 5 4 4
//1 5 6 6
//1 2 8 8
//1 2 9 9
//1 6 7 7
