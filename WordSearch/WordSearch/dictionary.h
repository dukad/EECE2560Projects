// Kaden Du and Ryan Dailor
// Definition of the Dictionary Class

#pragma once
#include <iostream>
#include <vector>

using namespace std;

class dictionary
{
public:
	// defualt constructor
	dictionary();
	void readFromDictFile(string path);
	void selectionSort();
	int binarySearch(string word);
	void writeToSortedDictFile();

	// friend for easy pritning of the dictionary
	friend ostream& operator<<(ostream& os, dictionary& dict)
	{
		for (int i = 0; i < dict.dict.size(); i++)
		{
			os << dict.dict[i] << endl;
		}
		return os;
	}

private:
	vector<string> dict;
};

