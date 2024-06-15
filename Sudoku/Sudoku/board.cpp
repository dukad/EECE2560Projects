// Declarations and functions for project #4

#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>

#include "board.h"

using namespace std;

typedef int ValueType; // The type of the value in a cell
const int Blank = -1;  // Indicates that a cell is blank
 
const int SquareSize = 3;  //  The number of cells in a small square
                           //  (usually 3).  The board has
                           //  SquareSize^2 rows and SquareSize^2
                           //  columns.

const int BoardSize = SquareSize * SquareSize;

const int MinValue = 1;
const int MaxValue = 9;

int numSolutions = 0;



board::board(int sqSize)
   : value(BoardSize,BoardSize)
// Board constructor
{
   clear();
   // resive conflict coutners to be the widthxwidth
   row_conflicts.resize(BoardSize, BoardSize);
   col_conflicts.resize(BoardSize, BoardSize);
   box_conflicts.resize(BoardSize, BoardSize);
   // initialize all values to false
   for (int i = 0; i < BoardSize; i++) {
	   for (int j = 0; j < BoardSize; j++) {
		   row_conflicts[i][j] = false;
		   col_conflicts[i][j] = false;
		   box_conflicts[i][j] = false;
	   }
   }
   
}

void board::clear()
// Mark all possible values as legal for each board entry
{
   for (int i = 0; i < BoardSize; i++)
      for (int j = 0; j < BoardSize; j++)
      {
         value[i][j] = Blank;
      }
}

void board::initialize(ifstream &fin)
// Read a Sudoku board from the input file.
{
   char ch;

   clear();
   
   for (int i = 0; i < BoardSize; i++)
      for (int j = 0; j < BoardSize; j++)
	    {
	       fin >> ch;

          // If the read char is not Blank
           if (ch != '.') {
               setCell(i, j, ch - '0');   // Convert char to int
           }
		   else {
			   resetCell(i, j);
		   }
        } 
}


ValueType board::getCell(int i, int j)
// Returns the value stored in a cell.  Throws an exception
// if bad values are passed.
{
   if (i >= 0 && i < BoardSize && j >= 0 && j < BoardSize)
      return value[i][j];
   else
      throw rangeError("bad value in getCell");
}

bool board::isBlank(int i, int j)
// Returns true if cell i,j is blank, and false otherwise.
{
   if (i < 0 || i > BoardSize - 1 || j < 0 || j > BoardSize - 1)
      throw rangeError("bad value in setCell");

   return (getCell(i,j) == Blank);
}

int squareNumber(int i, int j)
// Return the square number of cell i,j (counting from left to right,
// top to bottom.  Note that i and j each go from 1 to BoardSize
{
    // Note that (int) i/SquareSize and (int) j/SquareSize are the x-y
    // coordinates of the square that i,j is in.  

    return SquareSize * ((i) / SquareSize) + (j) / SquareSize;
}

void board::print()
// Prints the current board in board format.
{
   for (int i = 0; i < BoardSize; i++)
   {
      if ((i) % SquareSize == 0)
      {
         cout << " -";
	 for (int j = 0; j < BoardSize; j++)
	    cout << "---";
         cout << "-";
	 cout << endl;
      }
      for (int j = 0; j < BoardSize; j++)
      {
	 if ((j) % SquareSize == 0)
	    cout << "|";
	 if (!isBlank(i,j))
	    cout << " " << getCell(i,j) << " ";
	 else
	    cout << "   ";
      }
      cout << "|";
      cout << endl;
   }

   cout << " -";
   for (int j = 0; j <= BoardSize - 1; j++)
      cout << "---";
   cout << "-";
   cout << endl;
}

void board::setCell(int i, int j, int val) {
    // check to make sure it is between min and max
	if (!(val < MinValue || val > MaxValue)) {
        // check row
		if (row_conflicts[i][val-1]) {
			throw rangeError("row conflict");
		}
		// check column
        if (col_conflicts[j][val-1]) {
			throw rangeError("column conflict");
        }
        // check box conflicts
        if (box_conflicts[squareNumber(i, j)][val-1]) {
			throw rangeError("box conflict");
        }
    }
    else {
		throw rangeError("value out of range");
    }
    // reset the cell
	resetCell(i, j);
    value[i][j] = val;
    // update conflicts
	if (val != Blank) {
		row_conflicts[i][val-1] = true;
		col_conflicts[j][val-1] = true;
		box_conflicts[squareNumber(i, j)][val-1] = true;
	}
}

void board::resetCell(int i, int j) {
    // clear the conflicts in the associated row and column
	if (value[i][j] != Blank) {
		row_conflicts[i][value[i][j]] = false;
		col_conflicts[j][value[i][j]] = false;
		box_conflicts[squareNumber(i, j)][value[i][j]] = false;
	}
    value[i][j] = Blank;
}

void board::printConflicts() {
    //for loops to iterate and print conflict matrices
    cout << "Row Conflicts: " << endl;
    for (int i=0; i < BoardSize; i++) {
        cout << "Row " << i << ": ";
        for (int j=0; j < BoardSize; j++) {
            cout << row_conflicts[i][j] << " ";
        }
        cout << endl;
    }
    cout << "\n";
    cout << "Column Conflicts: " << endl;
    for (int i=0; i < BoardSize; i++) {
        cout << "Column " << i << ": ";
        for (int j=0; j < BoardSize; j++) {
            cout << col_conflicts[i][j] << " ";
        }
        cout << endl;
    }
    cout << "\n";
    cout << "Square Conflicts: " << endl;
    for (int i=0; i < BoardSize; i++) {
        cout << "Square " << i << ": ";
        for (int j=0; j < BoardSize; j++) {
            cout << box_conflicts[i][j] << " ";
        }
        cout << endl;
    }
    cout << "\n";
}

bool board::checkSolved() {
    // check to see if there is a value in every cell
    for (int i = 1; i <= BoardSize; i++) {
        for (int j = 1; j <= BoardSize; j++) {
            if (value[i][j] == Blank) {
				cout << "Board is not solved\n" << endl;
                return false;
            }
        }
    }
    //output to screen
	cout << "Board is solved\n" << endl;
    return true;
}