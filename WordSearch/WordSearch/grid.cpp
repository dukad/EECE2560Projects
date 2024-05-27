#include "grid.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

grid::grid(string fileName)
{
	ifstream file(fileName);
	if (!file)
	{
		cout << "Error opening file" << endl;
		exit(1);
	}

	file >> rows >> cols;
	matrix.resize(rows, vector<char>(cols));
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			file >> matrix[i][j];
		}
	}
	file.close();
}

