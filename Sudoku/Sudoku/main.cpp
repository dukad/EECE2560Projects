// Sudoku.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "board.h"

using namespace std;
const int SquareSize = 3;


ostream& operator<<(ostream& ostr, vector<int>& v)
// Overloaded output operator for vector class.
{
    for (int i = 0; i < v.size(); i++)
        ostr << v[i] << " ";
    cout << endl;
    return ostr;
}

int main()
{
    ifstream fin;

    // Read the sample grid from the file.
    string fileName = "sudoku3.txt";

    fin.open(fileName.c_str());
    if (!fin)
    {
        cerr << "Cannot open " << fileName << endl;
        exit(1);
    }

	cout << "Reading initial board from file " << fileName << endl;

    try
    {
        board b1(SquareSize);

        while (fin && fin.peek() != 'Z')
        {
            
            b1.initialize(fin);
			cout << "INITIAL BOARD" << endl;
            b1.print();
            b1.printConflicts();
        }

        b1.checkSolved();
    }

    
    catch (indexRangeError& ex)
    {
        cout << ex.what() << endl;
        exit(1);
    }
}