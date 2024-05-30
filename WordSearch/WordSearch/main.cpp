// Main for Project 2a - Kaden Du & Ryan Dailor
// contains all global functions and the main to run the program

#include <iostream>
#include <fstream>

#include "dictionary.h"
#include "grid.h"

using namespace std;

#define MIN_WORD_LENGTH 5


string getWord(grid g, int row, int col, int h, int v, int wordLength)
{
	//cout << "Getting possible word in direction: " << h << ", " << v << ", " << wordLength << endl;
	// this function will return a string which should be check for a match in the dictionary
	string word = "";
	for (int i = 0; i < wordLength; i++)
	{
		int newRow = row + i * h;
		int newCol = col + i * v;
		// now ensure that the new row and column are within the grid
		newRow = (newRow + g.rows) % g.rows;
		newCol = (newCol + g.cols) % g.cols;

		//cout << "New row: " << newRow << " New col: " << newCol << endl;
		
		word += g.matrix[newRow][newCol];
	}
	return word;
}

void checkAllDirections(dictionary dict, grid g, int row, int col, vector<string> &found)
{
	// given a coordinate in the gird, this function will check for words in all directions
	//cout << "Checking all directions at index: " << row << ", " << col << endl;
	int wordLength = MIN_WORD_LENGTH;
	while (wordLength <= min(g.rows, g.cols))
	{
		for (int h = -1; h <= 1; h++)
		{
			for (int v = -1; v <= 1; v++)
			{
				string word = getWord(g, row, col, h, v, wordLength); // get the possible word in that direction etc. 
				//cout << "Checking word: " << word << endl;
				int index = dict.binarySearch(word); // check if the word is in the dictionary
				if (index != -1)
				{
					cout << "found: " << word << " at position: " << row << ", " << col << endl;
					// save the word in the found vector
					found.push_back(word);
				}
			}
		}
		wordLength++;
	}
}


void findMatches(dictionary dict, grid g, vector<string> &found)
{
	// this function will iterate through the entire grid and check for matches
	//cout << "Finding matches" << endl;
	// iterate through the entire grid position by position
	for (int row = 0; row < g.rows; row++) {
		for (int col = 0; col < g.cols; col++) {
			// check for matches in all directions
			checkAllDirections(dict, g, row, col, found);
		}
	}
}

void search() {
	// this function will handle loading inputs from keyboard input to control which grid and dictionary files to use
	string gridFile;
	cout << "Enter the name of the grid file: ";
	cin >> gridFile;

	grid g(gridFile);

	cout << "Would you like to use the pre-sorted dictionary file? (y/n): ";	
	char choice;
	cin >> choice;
	dictionary dict;
	if (choice == 'y')
	{
		//initialize dictionary
		string path = "SortedDictionary";
		//read from dictionary file
		cout << "Reading from dictionary file" << endl;
		dict.readFromDictFile(path);
	}
	else {
		//initialize dictionary
		string path = "Dictionary";
		//read from dictionary file
		cout << "Reading from dictionary file" << endl;
		dict.readFromDictFile(path);
		//sort the dictionary
		cout << "Sorting the dictionary" << endl;
		dict.selectionSort();
		//search for a word
		cout << "Writing to the sorted dictionary file" << endl;
		dict.writeToSortedDictFile();
	}

	// init vector to store found words
	vector<string> found;

	// finding matches
	findMatches(dict, g, found);
	cout << "Search complete! Words found (saved to found.txt):" << endl;

	// print the found words, also save them to a file
	ofstream file("found.txt");
	if (file.is_open())
	{
		for (int i = 0; i < found.size(); i++)
		{
			file << found[i] << endl;
			cout << "found: " << found[i] << endl;
		}
	}
	else
	{
		cout << "Error: Could not open file" << endl;
	}
}

int main()
{
	// call the search function to do all the work
	search();
	return 0;
}