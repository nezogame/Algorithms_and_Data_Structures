// 7Lab3Sem(C++).cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

struct Node {
	int key;
	int value;
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
	}
};

class Hash_map {
	int capacity;
	int size;
	Node** hash_arr;
	int chek_cell(int index, int key);
	void increase_arr(Hash_map& map);
	Node* dummy = new Node(-1, -1);
public:
	Hash_map() :capacity(0), size(0), hash_arr(NULL) {};
	Hash_map(int n) {
		capacity = n;
		hash_arr = new Node * [n];
		for (int i = 0; i < capacity; i++) {
			hash_arr[i] = nullptr;
		}
	}
	int division_hash(int key);
	void insert(int key, int value);
	void print_table();
	void remove(int key);
	int search(int key);
};


int Hash_map::division_hash(int key) {
	return key % capacity;
}
int Hash_map::chek_cell(int index, int key) {
	while (hash_arr[index] != nullptr && hash_arr[index]->key != key && hash_arr[index]->key != -1) {
		index++;
		index %= capacity;
	}
	return index;
}
void Hash_map::increase_arr(Hash_map& map) {
	Hash_map* new_hash_arr = new Hash_map(capacity * 2);
	for (int i = 0; i < capacity; i++) {
		if (hash_arr[i] != nullptr) {
			new_hash_arr->insert(hash_arr[i]->key, hash_arr[i]->value);
		}
	}
	map = *new_hash_arr;

}
void Hash_map::insert(int key, int value) {

	if (capacity * 0.8 < size) {
		increase_arr(*this);
	}
	int hash_index = chek_cell(division_hash(key), key);
	hash_arr[hash_index] = new Node(key, value);
	size++;
}

void Hash_map::print_table() {
	for (int i = 0; i < capacity; i++) {
		if (hash_arr[i] != nullptr && hash_arr[i]->key != -1) {
			cout << "Key: " << hash_arr[i]->key << ", Value: " << hash_arr[i]->value << endl;
		}
		else {
			cout << "NULL" << endl;
		}
	}
}
void Hash_map::remove(int key) {
	int hash_index = division_hash(key);
	int counter = 0;
	while (hash_arr[hash_index] != nullptr && hash_arr[hash_index]->key != key && counter < capacity) {

		hash_index++;
		hash_index %= capacity;
		counter++;
	}
	if (hash_arr[hash_index] != nullptr && hash_arr[hash_index]->key == key) {
		hash_arr[hash_index] = dummy;
		size--;
	}
	else {
		cout << "This key: " << key << " doesn't exist!\b";
	}
}

int Hash_map::search(int key) {
	int hash_index = division_hash(key);
	int counter = 0;
	while (hash_arr[hash_index] != nullptr && counter < capacity) {

		if (hash_arr[hash_index]->key == key) {
			return hash_arr[hash_index]->value;
		}
		hash_index++;
		hash_index %= capacity;
		counter++;
	}
	return -1;
}

bool Interface(Hash_map& hash_map) {

	int action, key, number, result;
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

		std::cout << "Input key and value: " << endl;
		cin >> key >> number;
		hash_map.insert(key, number);
		break;
	case 2:
		std::cout << "Input KEY: " << endl;
		cin >> key;
		hash_map.remove(key);
		break;
	case 3:
		std::cout << "Input KEY: " << endl;
		cin >> key;
		result = hash_map.search(key);
		if (result >-1) {
			cout << "Value under the key: " << key << " is: " << result << endl;
		}
		else {
			cout << "Value under the key: " << key << " doesn't exist!!!!\n";
		}
		break;
	case 4:
		hash_map.print_table();
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
	int size;


	cout << "Enter size of the table: \n";
	cin >> size;
	Hash_map abcdef_you(size);
	do {
		result = Interface(abcdef_you);
	} while (result != false);

}
