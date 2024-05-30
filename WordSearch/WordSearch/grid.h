// Kaden Du and Ryan Dailor
// Definition of the Grid Class

#pragma once

#include <iostream>
#include <vector>

using namespace std;

class grid
{
public:
	grid(string fileName);
	vector<vector<char>> matrix;
	int rows;
	int cols;


	// friend for easy printing
	friend ostream& operator<<(ostream& os, grid g)
	{
		for (int i = 0; i < g.rows; i++)
		{
			for (int j = 0; j < g.cols; j++)
			{
				os << g.matrix[i][j] << " ";
			}
			os << endl;
		}
		return os;
	}

};

