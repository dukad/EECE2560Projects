#include "heap.h"
#include <vector>


using namespace std;

heap::heap() { //constructor initializes heap string vector
	vector<string> real_heap;
	heapsize = 0;
}
//node relationships
int heap::parent(int i) {
	return floor(i / 2);
}

int heap::left(int i) {
	return (2 * i);
}

int heap::right(int i) {
	return (2 * i + 1);
}

string heap::getItem(int n) {
	return real_heap[n];
}
//copy unsorted dict into heap and make first index empty
void heap::initializeMaxHeap(vector<string> v) {
	real_heap = v;
	real_heap.insert(real_heap.begin(), "0");
	heapsize = real_heap.size() - 1;
	buildMaxHeap(); //build heap
}
//maxHeapify algorithm
void heap::maxHeapify(int j) {
	int l = left(j);
	int r = right(j);
	int largest;
	if ((l <= heapsize) && real_heap[l] > real_heap[j]) {
		largest = l;
	}
	else { largest = j; }
	if ((r <= heapsize) && real_heap[r] > real_heap[largest]) {
		largest = r;
	}
	if (largest != j) {
		swap(real_heap[j], real_heap[largest]);
		maxHeapify(largest);
	}
}
//build heap using maxHeapify
void heap::buildMaxHeap() {
	for (int i = floor(heapsize / 2); i > 0; i--) {
		maxHeapify(i);
	}
}
//sort heap using max heapify from bottom up, return sorted heap vector
vector<string> heap::heapsort() {
	for (int i = heapsize; i > 1; i--) {
		swap(real_heap[1], real_heap[i]);
		heapsize = heapsize - 1;
		maxHeapify(1);
	}
	return real_heap;
}
