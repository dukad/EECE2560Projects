#pragma once
#include <iostream>
#include <vector>

using namespace std;

class dictionary
{
public:
	dictionary();
	void readFromDictFile(string path);
	void selectionSort();
	int binarySearch(string word);
	void writeToSortedDictFile();

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

