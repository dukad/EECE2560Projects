// Sudoku.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "board.h"
#include <chrono>
#include <thread>

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
    string fileName = "sudoku.txt";

    fin.open(fileName.c_str());
    if (!fin)
    {
        // cant open file, throw error
        cerr << "Cannot open " << fileName << endl;
        exit(1);
    }

    try
    {
        board b1(SquareSize);
        int total_calls = 0;
		// loop through the file and initialize the board 
        while (fin && fin.peek() != 'Z')
        {
            board b1(SquareSize);
            // initilize the board
            b1.initialize(fin);
            // print the board
            b1.print();
            // print the conflicts
            //b1.printConflicts();


            // check if board is solved (it hasn't)
            int i = 0;
            bool solved = b1.Solve(i);
			cout << "Solved: " << solved << endl;
            total_calls += i;
			// print the board
			b1.print();
        }
    }

    
    catch (indexRangeError& ex)
    {
        // error catching
        cout << ex.what() << endl;
        exit(1);
    }
}