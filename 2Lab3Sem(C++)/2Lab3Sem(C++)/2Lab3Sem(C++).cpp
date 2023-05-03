
#include <iostream>
#include "string"
#include"string.h"
using namespace std;

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
class SingleLinkedList
{
	Node* head;
	int size;
public:

	SingleLinkedList() : head(NULL) , size(0) {};

	int Size() {
		return size;
	}

	
	string operator[](const int index);
	void pushFront(int key);
	void insert(int key, int index);
	void move(int index_from, int index_to);
	void removeAt(int index);
	void deleteEveryN(int everyNumber);
	Node* swap(Node* nodeFirst, Node* nodeSecond);
	void bubble_sort();
	void listDeepCopy(SingleLinkedList list);
	void clean();
	void gluing( SingleLinkedList gluing_list);
	void inner_join(SingleLinkedList first_list, SingleLinkedList second_list);
	Node* get_head();


};
class CircularList {
	Node* head;
	int size;
public:

	CircularList() : head(NULL), size(0) {};
	CircularList(int number){

		for (int i = 1; i <= number; i++) {
			this->push_back(i);
		}
	}
	CircularList(SingleLinkedList list) {
		if (list.Size() == 0) {
			return;
		}
		this->size = list.Size();
		Node** current = &head, * tmp=nullptr;
		tmp = list.get_head();
		(*current) = new Node(*tmp);
		while (tmp->next != nullptr) {
			tmp = tmp->next;
			(*current)->next = new Node(*tmp);
			current=&(*current)->next;
		}
		(*current)->next = head;
	}

	int Size() {
		return size;
	}
	string operator[] (const int index);
	void lottery_winners(int number_of_winners, int every_n_winner, CircularList* winners_holder);
	void  remove(Node* curr, Node* prev);
	void push_back(int key);
	Node* get_back();

};
string SingleLinkedList::operator [] (const int index)
{
	if (size == 0) {
		return "List is empty\n";
	}
	int counter = 0;
	Node* current = this->head;
	string res = "";
	while (current != nullptr)
	{
		if (counter == index)
		{

			return res += to_string(current->key);
		}

		current = current->next;
		counter++;
	}
	return "No elements in list" + '\n' + '\n';
}
void SingleLinkedList::pushFront(int key) {
	if (head == nullptr) {
		head = new Node(key);
		head->next = nullptr;
		size++;
	}
	else {
		Node* temp = head;
		head = new Node(key);
		head->next = temp;
		size++;
	}
}
void SingleLinkedList::insert(int key, int index) {
	if (index > size || index < 0) {
		cout << "You enter WRONG index for insert.Min idex is: 0, Max index is : " << size << "\n\n";
		return;
	}
	
	Node* next = head, * current = nullptr;

	for (int i = 0; i < index - 1; i++) {
		current = next;
		next = current->next;
	}
	if (index == size) {
		next->next = new Node(key);
		next->next->next = nullptr;
	}
	else if (index == 0)
	{
		pushFront(key);
		size--;
	}
	else {
		current = next->next;
		next->next = new Node(key);
		next->next->next = current;
	}
	size++;

}
void SingleLinkedList::move(int index_from, int index_to) {
	if (index_from > size || index_from < 0 ) {
		cout << "You enter the WRONG index for move.Min idex is: 0, Max index is : " << size << "\n\n";
		return;
	}
	else if (index_to + index_from > size || index_to<0) {
		cout << "You enter the WRONG number for move, it is out of scope\n\n";
		return;
	}
	Node* next = head, * current = nullptr;

	if (index_to == 0) {
		return;
	}
	else if (index_from == 1) {
		current = next;
		head = head->next;
		for (int i = 0; i < index_to; i++) {
		next = next->next;
		}
		current->next = next->next;
		next->next = current;
	}
	else {
		for (int i = 0; i < index_from - 1; i++) {
			current = next;
			next = current->next;
		}
		current->next = next->next;
		for (int i = 0; i < index_to; i++) {
			current = current->next;
		}
		next->next = current->next;
		current->next = next;
	}

}
void SingleLinkedList::removeAt(int index) {
	if (index > size|| index<1) {
		cout << "You enter WRONG index for function removeAt. Min idex is: 1, Max index are: " << size << "\n\n";
		return;
	}
	else if (index==1) {
		Node* next = nullptr;
		next = head->next;
		delete head;
		head = next;
		size--;

	}
	else if (index == size) {
		Node* next = head;
		for (int i = 0; i < size-2; i++) {
			next = next->next;
		}
		delete next->next;
		next->next = nullptr;
		size--;

	}
	else {
		Node* next = head, * current = nullptr;

		for (int i = 0; i < index-1; i++) {
			current = next;
			next = next->next;
			
		}
		current->next = next->next;
		delete next;
		size--;
	}
}

void SingleLinkedList::deleteEveryN(int everyNumber) {
	if(everyNumber<1){
		cout << "You enter the WRONG number for the function deleteEveryN, Min number is: 1, Max number are: " << size << "\n\n";
		return;
	}
	else if (size ==0) {
		cout << "You enter the WRONG number for the function deleteEveryN, it is empty \n\n";
		return;
	}
	else if (everyNumber > size) {
		cout << "You enter the WRONG number for the function deleteEveryN, Min number is: 1, Max number are: " << size << "\n\n";
		return;
	}
	int countDelete = 0;
	int sizeBefore = size;
	for (int i = 1; i <= sizeBefore; i++) {
		if (i % everyNumber == 0) {
			removeAt(i- countDelete);
			countDelete++;
		}
	}

}
Node* SingleLinkedList::swap(Node* nodeFirst, Node* nodeSecond) {
	Node* tmp = nodeSecond->next;
	nodeSecond->next = nodeFirst;
	nodeFirst->next = tmp;
	return nodeSecond;
}
void SingleLinkedList::bubble_sort() {
	Node **temp = &head;

	int swapped;

	for (int i = 0; i <= size; i++)
	{
		swapped = 0;
		for (int j = 0; j < size - i- 1; j++)
		{
			Node* p1 = *temp;
			Node* p2 = p1->next;

			if ((p1->key) > (p2->key)) {
				*temp = swap(p1, p2);
				swapped = 1;
			}
			temp = &((*temp)->next);
		}
		temp = &head;
		if (swapped == 0) {
			break;
		}
	}
}
void SingleLinkedList::listDeepCopy(SingleLinkedList list) {
	Node* copied_list = list.head;
	Node** temp = &this->head;
	while (copied_list != nullptr) {
		*temp = new Node(copied_list->key);
		size++;
		copied_list = copied_list->next;
		temp = &(*temp)->next;
	}
	*temp = nullptr;
}
void SingleLinkedList::clean() {
	deleteEveryN(1);
	head = nullptr;
}
void SingleLinkedList::gluing(SingleLinkedList gluing_list) {
	Node* end = this->head;

	SingleLinkedList gluing_copy;
	gluing_copy.listDeepCopy(gluing_list);
	Node* start = gluing_copy.head;
	
	if(this->size == 0) {
		head = start;
	} 
	else 
	{
		while (end != nullptr && end->next != nullptr)
		{
			end = end->next;
		}

	end->next = start;
	}
	size += gluing_list.size;
}
void SingleLinkedList::inner_join(SingleLinkedList first_list, SingleLinkedList second_list) {
	Node* first = first_list.head;
	for (int i = 0; i < first_list.size;i++) {
		Node* second = second_list.head;
		for (int j = 0; j < second_list.size; j++) {
			if (first->key == second->key) {
				this->pushFront(first->key);
			}
			second = second->next;
		}
		first = first->next;
	}
	this->bubble_sort();
}
Node* SingleLinkedList::get_head() {
	return this->head;
}
string CircularList::operator[] (const int index)
{
	if (size == 0) {
		return "List is empty\n";
	}
	int counter = 0;
	Node* current = this->head;
	string res = "";
	while (current != nullptr)
	{
		if (counter == index)
		{

			return res += to_string(current->key);
		}

		current = current->next;
		counter++;
	}
	return "No elements in list" + '\n' + '\n';
}
void  CircularList::push_back(int key) {
	if (head == nullptr) {
		head = new Node(key);
		head->next = head;
		size++;
	}
	else {
		Node* tmp = head;
		while (tmp->next != head) {
			tmp = tmp->next;
		}
		tmp->next = new Node(key);
		tmp->next->next = head;
		size++;
	}
}
Node* CircularList::get_back() {
	Node* tmp = head;
	while (tmp->next!=head)
	{
		tmp = tmp->next;
	}
	return tmp;
}
void  CircularList::lottery_winners(int number_of_winners, int every_n_winner, CircularList *winners_holder) {
	if (size == 0) {
		cout << "list is empty" << endl;
		return;
	}
	else if (number_of_winners > size) {
		cout << "We have only " << size << " plyers" << endl;
		return;
	}
	Node* curr = head, * prev = get_back(), *tmp = nullptr;
	int count_winners = 0;
	
	while (count_winners != number_of_winners) {
		for (int i = 0; i < every_n_winner-1; i++) {
			prev = curr;
			curr = curr->next;
		}
		winners_holder->push_back(curr->key);
		count_winners++;
		if (curr == head) {
			Node* next = nullptr;
			next = head->next;

			delete(head);
			head = next;
			curr = head;
			prev->next = head;
			size--;
		}
		else if (curr->next == head) {
			prev->next = head;
			tmp = curr->next;
			delete(curr);
			curr = tmp;
			size--;
		}
		else {
			prev->next = curr->next;
			tmp = curr->next;
			delete(curr);
			curr = tmp;
			size--;
		}
	}
}



void printList(SingleLinkedList list)
{
	
	if (list.Size() == 0) {
		cout << "\nList is empty";
		return;
	}
	cout << "\nList key: ";
	for (int i = 0; i < list.Size(); i++)
	{

		cout << list[i] << " -> ";
	}
	cout << endl;
	cout << endl;
}
void printArrList(SingleLinkedList* list) {
	for (int i = 0; i < 3; i++) {
		printList(list[i]);
	}
}
bool Interface(SingleLinkedList *list) {
	int action,index, number, list_number, chosen_list, second_chosen_list, number_of_winners, every_n_winner;
	CircularList* weekend = nullptr;
	CircularList* two_days = new CircularList();
	CircularList* dead_line = new CircularList();
	CircularList* prizes;

	cout << "\n\nChoose your action (from 1 to 10).\n1 is add elemet in front of list\n2 is insert after n element\n3 is move element to n position\n4 is delete chosen element from list\n5 is delete every n element from list\n6 is sort in ascending order\n7 is create copy of chosen list\n8 is clean a list\n9 is gluing two list\n10 is create inner join list\n11 is print all lists on console\n12 is print lottery winners \n0 If you want to finish the program: " << endl;
	cin >> action;
	if (action > 0 && action < 10){
		do {
			cout << "\nChose list for action, enter number from 1 to 3 : " << endl;
				cin >> list_number;
		} while (!(list_number >= 1 && list_number <= 3));
				list_number--;
	}
	switch (action) {
	case 1:
		
		cout << "\nInput number : " << endl;
		cin >> number;
		list[list_number].pushFront(number);
		break;
	case 2:
		
		cout << "\nInput number and index: " << endl;
		cin >> number>>index;
		list[list_number].insert(number, index);
		break;
	case 3:
		
		cout << "\nInput index of number and for far it will ne moved: " << endl;
		cin >> number >> index;
		list[list_number].move(number, index);
		break;
	case 4:

		cout << "\nInput index which should be deleted: " << endl;
		cin >> index;
		list[list_number].removeAt(index);
		break;
	case 5:
		cout << "\nInput index for deleting each n element  : " << endl;
		cin >> index;
		list[list_number].deleteEveryN(index);
		break;
	case 6:

		list[list_number].bubble_sort();
	break;
	case 7:
		do {
			cout << "\nChose list for saving copy, enter number from 1 to 3 : " << endl;
			cin >> chosen_list;
		} while (!(chosen_list >= 1 && chosen_list <= 3));
		chosen_list--;
		list[chosen_list].listDeepCopy(list[list_number]);
	break;
	case 8:
		list[list_number].clean();
	break;
	case 9:
		do {
			cout << "\nChose list to which to gluing, enter number from 1 to 3 : " << endl;
			cin >> chosen_list;
		} while (!(chosen_list >= 1 && chosen_list <= 3));
		chosen_list--;

		list[list_number].gluing(list[chosen_list]);
	break;
	case 10:
		do {
			cout << "\nChose list first for inner join, enter number from 1 to 3 : " << endl;
			cin >> chosen_list;
		} while (!(chosen_list >= 1 && chosen_list <= 3));
		chosen_list--;
		do {
			cout << "\nChose list second for inner join, enter number from 1 to 3 : " << endl;
			cin >> second_chosen_list;
		} while (!(second_chosen_list >= 1 && second_chosen_list <= 3));
		second_chosen_list--;
		cout << "\nData will be saved in 3 list" << endl;
		list[2].inner_join(list[chosen_list], list[second_chosen_list]);
	break;
	case 11:
		printArrList(list);
		break;
	case 12:
		weekend = new CircularList(list[0]);
		if (weekend->Size() == 0) {
			cout << "List is empty" << endl;
			return true;
		}
		do {
			cout << "\nPlease enter number of winner from 1 to " << weekend->Size() << endl;
			cin >> number_of_winners;
		} while (!(number_of_winners >= 1 && number_of_winners <= weekend->Size()));
		prizes = new CircularList(weekend->Size());
		do {
			cout << "\nPlease enter which every person will win from 1 to something " << endl;
			cin >> every_n_winner;
		} while (!(every_n_winner >= 1));
		weekend->lottery_winners(number_of_winners, every_n_winner, two_days);
		prizes->lottery_winners(number_of_winners, every_n_winner, dead_line);
		for (int i = 0; i < (*two_days).Size(); i++) {
			cout << "Person: " << (*two_days)[i] << " win prize under the number-> " << (*dead_line)[i] << endl;
		}
		break;
	case 0:
		cout << "Thanks for using, bye bye";
		return false;
		break;
	default:
		cout << "Wrong number!!!";
	}
	return true;
}


int main()
{
	bool result;
	SingleLinkedList test;
	test.pushFront(30);
	test.pushFront(20);
	test.pushFront(3);
	test.insert(40, 3);
	test.insert(2, 2);
	test.insert(0, 1);
	test.insert(10, 0);
	//бублик сорт
	test.bubble_sort();
	SingleLinkedList tiredness;
	tiredness.listDeepCopy(test);
	tiredness.deleteEveryN(2);
	tiredness.pushFront(5);
	tiredness.pushFront(-23);
	tiredness.pushFront(7);
	tiredness.pushFront(0);
	tiredness.bubble_sort();

	

	SingleLinkedList sleep;
	SingleLinkedList list_arr[3] = {test,tiredness,sleep};


	
	do {
		result = Interface(list_arr);
	} while (result != false);
}