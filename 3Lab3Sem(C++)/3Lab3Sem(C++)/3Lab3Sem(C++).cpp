
#include <iostream>
#include <string>
using namespace std;
#define CAPACITY 10
struct Node {
	int key;
	Node* next;
	Node() {
		key = 0;
	}
	Node(int key) {

		this->key = key;
	}
	Node(Node& deepCopy) {
		key = deepCopy.key;
		next = deepCopy.next;
	}
};
class Stack
{
	Node* stack_pointer;
	int capacity;
	int size;
public:
	Stack() : stack_pointer(NULL), capacity(CAPACITY), size(0) {};
	Stack(int capacity) {
		stack_pointer = NULL;
		this->capacity = capacity;
		size = 0;
	}
	void push(int);
	void pop();
	int top();
	bool is_full();
	bool is_empty();
	void change_first_last();
	void print_stack();
	Node* search(int index);
	void reverse(Stack& stack);
	bool exist(int item);
	void clean();
};

bool Stack::is_full() {
	return size == capacity;
}

bool Stack::is_empty() {
	return size == 0;
}

void Stack::push(int key) {
	if (is_full()) {
		std::cout << " go to Stack Overflow\n";
		return;
	}
	if (is_empty()) {
		stack_pointer = new Node(key);
		stack_pointer->next = nullptr;
	}
	else {
		Node* temp = stack_pointer;
		stack_pointer = new Node(key);
		stack_pointer->next = temp;
	}
	size++;
}
void Stack::pop() {
	if (is_empty()) {
		std::cout << "Stack is empty" << endl;
		return;
	}
	Node* temp = stack_pointer->next;

	delete stack_pointer;
	stack_pointer = temp;
	size--;
}
int Stack::top() {
	if (is_empty()) {
		std::cout << "Stack is empty\n";
	}
	return stack_pointer->key;
}
void Stack::print_stack() {
	if (is_empty()) {
		std::cout << "Stack is empty\n";
		return;
	}
	Node* tmp = stack_pointer;

	while (tmp != nullptr)
	{
		std::cout << tmp->key << " ";
		tmp = tmp->next;
	}
	std::cout << endl;
}
Node* Stack::search(int index) {
	if (index > size || index < 1) {
		std::cout << "Wrong index\n";
		return nullptr;
	}
	Node* tmp = stack_pointer;
	for (int i = 1; i < index; i++) {
		tmp = tmp->next;
	}
	return tmp;
}
void Stack::change_first_last() {
	if (is_empty()) {
		cout << "Stack is empty\n";
		return;
	}
	if (size == 1) {
		return;
	}
	if (size == 2) {
		Node* first = stack_pointer, * last = search(size);
		last->next = first;
		stack_pointer = last;
		first->next = nullptr;
	}
	else {
		Node* first = stack_pointer, * last = search(size - 1);
		last->next->next = stack_pointer->next;
		stack_pointer = last->next;
		last->next = first;
		first->next = nullptr;
	}
}
void Stack::reverse(Stack& stack) {
	Stack freedom = Stack(capacity);
	while (stack.is_empty() == false)
	{
		freedom.push(top());
		stack.pop();
	}
	stack = freedom;
	return;
}
bool Stack::exist(int item) {
	Node* tmp = stack_pointer;
	while (tmp != nullptr) {
		if (tmp->key == item) {
			return true;
		}
		tmp = tmp->next;
	}
	return false;
}
void Stack::clean() {
	int size_before = size;
	for (int i = 0; i < size_before; i++) {
		this->pop();
	}
}
bool Interface(Stack& stack) {
	bool result;
	int action, number;
	std::cout << "\n\nChoose your action (from 1 to 7).\n"
		"1 is add elemet to Stack\n"
		"2 is remove elemet from Stack\n"
		"3 is print all Stack on console\n"
		"4 is swapping the first and last elements in Stack\n"
		"5 is reversing Stack\n"
		"6 is check exist elemnt in list\n"
		"7 is clean a Stack\n"
		"0 if you want to finish the program " << endl;

	cin >> action;

	switch (action) {
	case 1:

		std::cout << "\nInput number : " << endl;
		cin >> number;
		stack.push(number);
		break;
	case 2:
		stack.pop();
		break;
	case 3:
		stack.print_stack();
		break;
	case 4:

		stack.change_first_last();
		break;
	case 5:
		stack.reverse(stack);
		break;
	case 6:
		std::cout << "\nInput number : " << endl;
		cin >> number;
		result=stack.exist(number);
		if (result == true) {
			cout << number << " exist\n";
		}
		else {
			cout << number << " DOESN'T exist\n";
		}
		break;
	case 7:
		stack.clean();
		break;
	case 0:
		std::cout << "Thanks for using, bye bye";
		return false;
		break;
	default:
		std::cout << "Wrong number!!!";
	}
	return true;
}
int main()
{
	int stack_size;
	bool result;
	Node* ex = nullptr;
	do {
		cout << "Enter size for Stack: \n";
		cin >> stack_size;
	} while (stack_size<1);
	Stack cringe = Stack(stack_size);

	do {
		result = Interface(cringe);
	} while (result != false);
}

