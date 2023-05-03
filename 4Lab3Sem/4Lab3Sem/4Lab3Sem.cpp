#include <iostream>
#include <string>
using namespace std;
struct Node {
	int value;
	Node* next;
	Node() {
		value = 0;
	}
	Node(int t_value) {

		value = t_value;
	}
	Node(Node& deepCopy) {
		value = deepCopy.value;
		next = deepCopy.next;
	}
};
class Queue {
	Node* front;     
	Node* rear;     
	int size;
public:
	Queue() : front(NULL), rear(NULL), size(0) {};
	Queue(int capacity) {
		  front = NULL;
		  rear = NULL;
		  size = 0;
	  }
	Node* search(int index);
	void enqueue(int value);
	void dequeue();
	int peek();
	bool isEmpty();
	void print_queue();
	void change_first_last();
	void reverse(Queue& q);
	bool exist(int item);
	void clean();
};

Node* Queue::search(int index) {
	if (index > size || index < 1) {
		std::cout << "Wrong index\n";
		return nullptr;
	}
	Node* tmp = rear;
	for (int i = 1; i < index; i++) {
		tmp = tmp->next;
	}
	return tmp;
}

bool Queue::isEmpty() {
	return (size == 0);
}

void Queue::enqueue(int value) {
	if (isEmpty()) {
		front = new Node(value);
		rear = front;
		front->next = nullptr;
	}
	else {
		Node* tmp = rear;
		rear = new Node(value);
		rear->next = tmp;
	}
	size++;
}
void Queue::dequeue() {
	if (isEmpty()) {
		cout << "Queue is empty!!!\n";
		return;
	}
	if (rear == front) {
		delete front;
		rear = nullptr;
		front = nullptr;
	}
	else {
		delete front;
		front = search(size-1);
		front->next = nullptr;
	}
	size--;
}
int Queue::peek() {
	if (isEmpty()) {
		cout<< "Queue is empty!!!\n";
	}
	else {
		return front->value;
	}

}
void Queue::print_queue() {
	if (isEmpty()) {
		cout << "Queue is empty\n";
		return;
	}
	Node* tmp = rear;
	while (tmp != nullptr){
		cout << tmp->value<<"->";
		tmp = tmp->next;
	}
	cout << endl;
}
void Queue::change_first_last() {
	if (isEmpty()) {
		cout << "queue is empty\n";
		return;
	}
	if (size == 1) {
		return;
	}
	if (size == 2) {
		Node* tmp = rear;
		tmp->next = nullptr; 
		rear = front;
		rear->next = tmp;
		
	}
	else {
		Node* first = rear, *last=search(size-1);
		rear = front;
		rear->next = first->next;
		front = first;
		last->next = front;
		front->next = nullptr;
	}
}
void Queue::reverse(Queue& q){
	if (isEmpty()) {
		return;
	}
	int elem = q.peek();
	q.dequeue();
	reverse(q);
	q.enqueue(elem);
}
bool Queue::exist(int item) {
	Node* tmp = rear;
	while (tmp != nullptr) {
		if (tmp->value == item) {
			return true;
		}
		tmp = tmp->next;
	}
	return false;
}
void Queue::clean() {
	int size_before = size;
	for (int i = 0; i < size_before; i++) {
		dequeue();
	}
}
bool Interface(Queue& queue) {
	bool result;
	int action, number;
	std::cout << "Choose your action (from 1 to 7).\n"
		"1 is add elemet to queue\n"
		"2 is remove elemet from queue\n"
		"3 is print all queue on console\n"
		"4 is swapping the first and last elements in queue\n"
		"5 is reversing queue\n"
		"6 is check exist elemnt in list\n"
		"7 is clean a queue\n"
		"0 if you want to finish the program " << endl;

	cin >> action;
	cout << endl;
	switch (action) {
	case 1:

		std::cout << "Input number : " << endl;
		cin >> number;
		queue.enqueue(number);
		break;
	case 2:
		queue.dequeue();
		break;
	case 3:
		queue.print_queue();
		break;
	case 4:

		queue.change_first_last();
		break;
	case 5:
		queue.reverse(queue);
		break;
	case 6:
		std::cout << "Input number : " << endl;
		cin >> number;
		result = queue.exist(number);
		if (result == true) {
			cout << number << " exist\n";
		}
		else {
			cout << number << " DOESN'T exist\n";
		}
		break;
	case 7:
		queue.clean();
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
	Queue too_too;
	too_too.enqueue(77);
	too_too.enqueue(3);
	too_too.enqueue(7);
	too_too.enqueue(12);
	too_too.enqueue(21);
	too_too.enqueue(34);
	too_too.enqueue(47);
	too_too.enqueue(55);

	do {
		result = Interface(too_too);
	} while (result != false);
}
