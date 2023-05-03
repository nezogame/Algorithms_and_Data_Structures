// 6Lab3Sem(C++).cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

struct Node {
	int key;
	int value;
	Node* next;
	Node() {
		key = -1;
		value = 0;
	}
	Node(int t_key, int t_value) {
		key = t_key;
		value = t_value;
	}
	Node(Node& deepCopy) {
		key = deepCopy.key;
		value = deepCopy.value;
		next = deepCopy.next;
	}
};

class SingleLinkedList
{
	Node* head;
	int size;
public:

	SingleLinkedList() : head(NULL), size(0) {};

	int Size() {
		return size;
	}


	void pushFront(int key, int value);
	void removeAt(int index);
	Node* swap(Node* nodeFirst, Node* nodeSecond);
	Node* get_head();

};

class Hash_table {
	int table_size;
	SingleLinkedList** hash_table;
public:
	Hash_table() :table_size(0), hash_table(NULL) {};
	Hash_table(int n) {
		table_size = n;
		hash_table = new SingleLinkedList * [n];
		for (int i = 0; i < n; i++) {
			hash_table[i] = new SingleLinkedList();
		}

	}
	int division_hash(int key);
	Node* search(int index);
	void insert(int key, int value);
	void print_table();
	void remove(int key);
	int find_by_key(int key);
};

void SingleLinkedList::pushFront(int key, int value) {
	if (head == nullptr) {
		head = new Node(key, value);
		head->next = nullptr;
		size++;
	}
	else {
		Node* temp = head;
		head = new Node(key, value);
		head->next = temp;
		size++;
	}
}
void SingleLinkedList::removeAt(int index) {
	if (index > size || index < 1) {
		cout << "You enter WRONG index for function removeAt. Min idex is: 1, Max index are: " << size << "\n\n";
		return;
	}
	else if (index == 1) {
		Node* next = nullptr;
		next = head->next;
		delete head;
		head = next;
		size--;

	}
	else if (index == size) {
		Node* next = head;
		for (int i = 0; i < size - 2; i++) {
			next = next->next;
		}
		delete next->next;
		next->next = nullptr;
		size--;

	}
	else {
		Node* next = head, * current = nullptr;

		for (int i = 0; i < index - 1; i++) {
			current = next;
			next = next->next;

		}
		current->next = next->next;
		delete next;
		size--;
	}
}
Node* SingleLinkedList::swap(Node* nodeFirst, Node* nodeSecond) {
	Node* tmp = nodeSecond->next;
	nodeSecond->next = nodeFirst;
	nodeFirst->next = tmp;
	return nodeSecond;
}
Node* SingleLinkedList::get_head() {
	return head;
}

void Hash_table::insert(int key, int value) {
	hash_table[division_hash(key)]->pushFront(key, value);
}
void Hash_table::print_table() {
	for (int i = 0; i < table_size; i++) {
		Node* tmp = hash_table[i]->get_head();
		cout << endl;
		if (tmp == nullptr) {
			cout << "List is empty";
		}
		while (tmp != nullptr) {
			cout << "[Key: " << tmp->key << ", Value: " << tmp->value << "]->";
			tmp = tmp->next;
		}
		cout << endl;
	}
	cout << endl;
}
void Hash_table::remove(int key) {
	int count = 1;
	Node* deleted_node = hash_table[division_hash(key)]->get_head();
	while (deleted_node != nullptr) {
		if (deleted_node->key == key) {
			hash_table[division_hash(key)]->removeAt(count);
			return;
		}
		deleted_node = deleted_node->next;
		count++;
	}
}
int Hash_table::find_by_key(int key) {
	Node* exist = hash_table[division_hash(key)]->get_head();
	while (exist != nullptr) {
		if (exist->key == key) {
			return exist->value;
		}
		exist = exist->next;
	}
	return -1;
}

int Hash_table::division_hash(int key) {
	return key % table_size;
}

bool Interface(Hash_table & hash_table) {
	 
	int action, number, result;
	std::cout << "Choose your action (from 1 to 3).\n"
		"1 is add elemet to hash table\n"
		"2 is remove elemet from hash table\n"
		"3 is find value by key\n"
		"4 is print out hash table\n"
		"0 if you want to finish the program " << endl;

	cin >> action;
	cout << endl;
	switch (action) {
	case 1:

		std::cout << "Input value (value also a key) : " << endl;
		cin >> number;
		hash_table.insert(number,number);
		break;
	case 2:
		std::cout << "Input KEY: " << endl;
		cin >> number;
		hash_table.remove(number);
		break;
	case 3:
		std::cout << "Input KEY: " << endl;
		cin >> number;
		result = hash_table.find_by_key(number);
		if (result > -1) {
			cout << "Value under the key: " << number << " is: " << result << endl;
		}
		else {
			cout << "Value under the key: " << number << " doesn't exist!!!!\n";
		}
		break;
	case 4:
		hash_table.print_table();
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
	int test;
	cout << "Enter size of the table: \n";
	cin >> test;
	Hash_table tax(test);
	do {
		result = Interface(tax);
	} while (result != false);
}

//void Hash_table::insert(int key,int value) {
//	Node* tmp = search(division_hash(key));
//	tmp->key = key;
//	tmp->value = value;
//
//}
//void Hash_table::create_table(int n) {
//	if (head == nullptr) {
//		head = new Node;
//	}
//	Node* tmp = head;
//	for (int i = 1; i < n; i++) {
//		tmp->next = new Node();
//		tmp = tmp->next;
//	}
//	tmp->next = nullptr;
//}
//void Hash_table::print_table() {
//	Node* tmp = head;
//	while (tmp != nullptr) {
//		cout << "[Key: " << tmp->key << ", Value: " << tmp->value << "] ";
//		tmp = tmp->next;
//	}
//	cout << endl;
//}
//void Hash_table::remove(int key) {
//	Node* deleted_node = search(division_hash(key));
//	if (deleted_node->key == key) {
//		deleted_node->key = -1;
//		deleted_node->value = 0;
//	}
//}
//
//bool Hash_table::find_by_key(int key) {
//	Node* exist = search(division_hash(key));
//	if (exist->key == key) {
//		return true;
//	}
//	return false;
//}


//Node* Hash_table::search(int index) {
//	if (index > table_size-1 || index < 0) {
//		std::cout << "Wrong index\n";
//		return nullptr;
//	}
//	Node* tmp = head;
//	for (int i = 0; i < index; i++) {
//		tmp = tmp->next;
//	}
//	return tmp;
//}