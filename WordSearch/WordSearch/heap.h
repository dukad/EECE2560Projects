//Kaden Du and Ryan Dailor
//Definition of heap template class
#pragma once
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class heap
{
public:
	heap(); //default constructor

	void initializeMaxHeap(vector<string> v); //heap initialization which intakes dict vector
	vector<string> heapsort(); //heap sort which returns sorted vector for dict

private:
	vector<string> real_heap; //heap container
	int heapsize;
	int parent(int i);
	int left(int i);
	int right(int i);
	string getItem(int n);
	void maxHeapify(int j);
	void buildMaxHeap();
};