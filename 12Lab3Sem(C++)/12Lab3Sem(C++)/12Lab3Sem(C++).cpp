// 12Lab3Sem(C++).cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;




class MinHeap
{
	int* harr;
	int capacity;
	int heap_size;
	void print(const string& prefix, int index, bool isLeft);
public:
	// Constructor
	MinHeap(int _capacity);
	// Constructor
	MinHeap(int* arr, int _capacity);

	int parent(int i) { return (i - 1) / 2; }
	int left_child(int i) { return (2 * i + 1); }
	int right_child(int i) { return (2 * i + 2); }
	void insert(int);
	bool is_full();
	int get_heapSize();
	void heapify();
	void sift_down(int index);
	void sift_up(int index);
	void swap(int*, int*);
	void print();
	void deleteRoot();
	void remove(const int& value);
};

void MinHeap::swap(int* x, int* y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}
int  MinHeap::get_heapSize() {
	return heap_size;
}

bool MinHeap::is_full()
{
	return heap_size == get_heapSize();
}

MinHeap::MinHeap(int _capacity)
{
	heap_size = 0;
	capacity = _capacity;
	harr = new int[_capacity];
}

MinHeap::MinHeap(int* arr, int _capacity)
{
	heap_size = _capacity;
	capacity = _capacity;
	harr = new int[_capacity];
	for (int i = 0; i < _capacity; i++)
	{
		harr[i] = arr[i];
	}

	heapify();
}

// Inserts a new key 'k'
void MinHeap::insert(int k)
{
	if (is_full())
	{
		capacity = 2 * capacity;
		int* new_arr = new int[capacity];
		for (int i = 0; i < capacity / 2; i++)
		{
			new_arr[i] = harr[i];
		}
		harr = new_arr;
	}

	harr[heap_size] = k;
	sift_up(heap_size);

	heap_size++;
}

void MinHeap::sift_up(int index) {
	while (index > 0) {
		int p = parent(index);
		if (harr[p] <= harr[index]) {
			break;
		}
		swap(&harr[p], &harr[index]);
		index = p;
	}
}

void MinHeap::sift_down(int index) {
	while (true) {
		int left = left_child(index);
		int right = right_child(index);
		int min_index = index;
		if (left < heap_size && harr[left] < harr[min_index]) {
			min_index = left;
		}
		if (right < heap_size && harr[right] < harr[min_index]) {
			min_index = right;
		}
		if (min_index == index) {
			break;
		}
		swap(&harr[index], &harr[min_index]);
		index = min_index;
	}
}

void MinHeap::heapify()
{
	for (int i = heap_size / 2 - 1; i >= 0; i--) {
		sift_down(i);
	}
}



void MinHeap::print(const string& prefix, int index, bool isLeft)
{
	if (index < heap_size)
	{
		cout << prefix;
		cout << (isLeft ? "|--" : "L--");
		std::cout << harr[index] << endl;
		print(prefix + (isLeft ? "|  " : "   "), left_child(index), true);
		print(prefix + (isLeft ? "|  " : "   "), right_child(index), false);

	}
}
void MinHeap::print() {
	if (heap_size <= 0) {
		cout << "Heap is empty!!!\n";
	}
	else {
		print("", 0, false);
	}
}

void MinHeap::deleteRoot() {
	if (heap_size == 0) {
		cout << "Heap is empty!!!\n";
		return;
	}
	harr[0] = harr[heap_size - 1];
	heap_size--;
	sift_down(0);
}

void MinHeap::remove(const int& value) {
	int index = -1;
	for (int i = 0; i < heap_size; i++) {
		if (harr[i] == value) {
			index = i;
			break;
		}
	}
	if (index == -1) {
		cout << "Key doesn't exxist!!!\n";
		return;
	}
	harr[index] = harr[heap_size - 1];
	heap_size--;
	sift_down(index);
	sift_up(index);
}

bool Interface(MinHeap& heap) {

	int action, key, number, value;
	std::cout << "Choose your action (from 1 to 3).\n"
		"1 is add elemet to heap\n"
		"2 is remove elemet from heap\n"
		"3 is remove ROOT elemet from heap\n"
		"4 is print out heap\n"
		"0 if you want to finish the program " << endl;

	cin >> action;
	cout << endl;
	switch (action) {
	case 1:

		cout << "Enter key: " << endl;
		cin >> key;
		heap.insert(key);
		break;
	case 2:
		std::cout << "Input KEY: " << endl;
		cin >> key;
		heap.remove(key);
		break;
	case 3:
		heap.deleteRoot();
		break;
	case 4:
		heap.print();
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
	int const SIZE = 10;
	int* arr = new int[SIZE] { 3, 2, 15, 5, 4, 45, 1, 7, 9, 10 };
	MinHeap h(arr, SIZE);
	bool result;
	do {
		result = Interface(h);
	} while (result != false);
	return 0;
}
