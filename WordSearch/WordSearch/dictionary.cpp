// Kaden Du and Ryan Dailor
// contains implementation for the dictionary class

#include "dictionary.h"
#include "heap.h"
#include <fstream>
#include <iostream>
using namespace std;

dictionary::dictionary()
{
	vector<string> dict;
}

void dictionary::readFromDictFile(string path)
{
	// read from Dictionary and add to the vector 
	// open the file
	ifstream file(path);
	if (file.is_open())
	{
		string word;
		// while i can read from the file, add it to the dictionary
		while (file >> word)
		{
			dict.push_back(word);
		}
	}
	else
	{ // error catching
		cout << "Error: Could not open file" << endl;
	}

}

void dictionary::writeToSortedDictFile()
{
	// write the sorted dictionary to the file for easy testing
	ofstream file("SortedDictionary");
	if (file.is_open())
	{
		for (int i = 0; i < dict.size(); i++)
		{
			file << dict[i] << endl;
		}
	}
	else
	{
		cout << "Error: Could not open file" << endl;
	}
}

void dictionary::selectionSort() {
	// selection sort the dictionary in place
	for (int i = 0; i < dict.size(); i++)
	{
		int minIndex = i; // iterating through the list
		for (int j = i + 1; j < dict.size(); j++)
		{
			
			if (dict[j] < dict[minIndex])
			{ // find the smallest element
				minIndex = j;
			}
		}
		// put smallest element in the correct place
		swap(dict[i], dict[minIndex]);
	}
}

int dictionary::binarySearch(string word)
{
	// binary search the dictionary for the word
	int low = 0;
	int high = dict.size() - 1;
	// while there are still elements to search
	while (low <= high)
	{
		// take the midpoint
		int mid = (low + high) / 2;
		if (dict[mid] == word)
		{
			return mid;
		}
		// basicaly recurse on either the left or the right half of the array
		else if (dict[mid] < word)
		{
			low = mid + 1;
		}
		else
		{
			high = mid - 1;
		}
	}
	// not found
	return -1;
}
//quick sort algorthm using left and right parameters and right-most partition
void dictionary::quicksort(int left, int right) {
	if (left < right) {
		int s = partition(left, right);
		quicksort(left, s - 1);
		quicksort(s + 1, right);
	}
	else { return; }
}
//partition function used in quicksort, rightmost pivot implementation
int dictionary::partition(int left, int right) {
	string x = dict[right];
	int i = left - 1;
	for (int j = left; j < right; j++) {
		if (dict[j] <= x) {
			i = i + 1;
			swap(dict[i], dict[j]);
		}
	}
	swap(dict[i + 1], dict[right]);
	return (i + 1);
}
//public function to access size of private dict, used in main
int dictionary::getSize() {
	return dict.size();
}
//heap sort function which instantiates heap and copies dictionary values into it
void dictionary::heapsort() {
	heap heaperooni;
	heaperooni.initializeMaxHeap(dict);
	dict = heaperooni.heapsort();
}