// Kaden Du and Ryan Dailor
// contains the implementation for the grid class

#include "grid.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

grid::grid(string fileName)
{
	// open the file
	ifstream file(fileName);
	if (!file)
	{
		cout << "Error opening file" << endl;
		exit(1);
	}

	// take the dimenstions from the top of the file
	file >> rows >> cols;
	matrix.resize(rows, vector<char>(cols));
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			// enter each character into the grid
			file >> matrix[i][j];
		}
	}
	file.close();
}

