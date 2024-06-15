// Declarations and functions for project #4

#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>

#include "board.h"


#include <chrono>
#include <thread>

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

   digit_count.resize(BoardSize, 0);
   // initialize all values to false
   for (int i = 0; i < BoardSize; i++) {
	   for (int j = 0; j < BoardSize; j++) {
		   row_conflicts[i][j] = false;
		   col_conflicts[i][j] = false;
		   box_conflicts[i][j] = false;
	   }
	   digit_count[i] = 0;
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
	//cout << "calling reset from setCell" << endl;
	resetCell(i, j);
    value[i][j] = val;
    // update conflicts
	if (val != Blank) {
		row_conflicts[i][val-1] = true;
		col_conflicts[j][val-1] = true;
		box_conflicts[squareNumber(i, j)][val-1] = true;
	}
	digit_count[val - 1]++;
}

void board::resetCell(int i, int j) {
	//cout << "reset function call" << endl;
	//cout << i << " " << j << endl;
    // clear the conflicts in the associated row and column
	if (value[i][j] != Blank) {
		row_conflicts[i][value[i][j] - 1] = false;
		col_conflicts[j][value[i][j] - 1] = false;
		box_conflicts[squareNumber(i, j)][value[i][j] - 1] = false;
		digit_count[value[i][j]-1]--;
	}
    value[i][j] = Blank;
	//cout << "end of reset function" << endl;
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
	//cout << "checking if solved" << endl;
    // check to see if there is a value in every cell
    for (int i = 0; i < BoardSize; i++) {
        for (int j = 0; j < BoardSize; j++) {
            if (value[i][j] == Blank) {
                return false;
            }
        }
    }
    //output to screen
	
    return true;
}

int board::getConstraintCount(int i, int j) {
	// get the number of constraints on a cell
	int count = 0;
	for (int k = 0; k < BoardSize; k++) {
		if (row_conflicts[i][k] || col_conflicts[j][k] || box_conflicts[squareNumber(i, j)][k]) {
			count++;
		}
	}
	return count;
}

bool board::Solve(int& counter) {
	counter++;
	// print the board
	//print();
	// base case: check if the board is solved
    if (checkSolved()) {
        // print the counter
		cout << "Number of recursive calls: " << counter << endl;
        return true;
    }

	//cout << "Finding the most constrained cell..." << endl;
	// board is not solved, find the most constrained cell that 
    int max_constraints = 0;
	int max_i = 0;
	int max_j = 0;
	for (int i = 0; i < BoardSize; i++) {
		for (int j = 0; j < BoardSize; j++) {
			if (value[i][j] == Blank) {
				int constraints = getConstraintCount(i, j);
				if (constraints > max_constraints) {
					max_constraints = constraints;
					max_i = i;
					max_j = j;
				}
			}
		}
	}

	//cout << "Most constrained cell found at: " << max_i << " " << max_j << endl;

	//cout << "getting all valid numbers for the cell..." << endl;
    vector<int> valid_numbers;
    // max constrained cell is now at i, j
    // get all the valid numbers for the cell
	for (int k = 1; k <= BoardSize; k++) {
		// check if the number is valid
		if (!row_conflicts[max_i][k - 1] && !col_conflicts[max_j][k - 1] && !box_conflicts[squareNumber(max_i, max_j)][k - 1]) {
			// store the number in a vector
			valid_numbers.push_back(k);
		}
	}

	//cout << "Sorting the valid numbers..." << endl;
	//cout << valid_numbers.size() << endl;
    if (valid_numbers.empty()) {
        //cout << "returning false...";
        return false;
    }
	//cout << "292 "<< endl;
    // sort valid numbers, using their count in digit count as the key
	for (int i = 0; i < valid_numbers.size(); i++) {
		//cout << i << endl;
		for (int j = i + 1; j < valid_numbers.size(); j++) {
			//cout << i << " " << j << endl;
			if (digit_count[valid_numbers[i] - 1] < digit_count[valid_numbers[j] - 1]) {
				int temp = valid_numbers[i];
				valid_numbers[i] = valid_numbers[j];
				valid_numbers[j] = temp;
			}
		}
	}

	//cout << "Trying the valid numbers..." << endl;
	// the valid numbers are now sorted in descending order of their count in digit count
	// iterate through the valid numbers
    for (int i = 0; i < valid_numbers.size(); i++) {
		//cout << "trying number: " << valid_numbers[i] << " at cell: " << max_i << " " << max_j << endl;
        // try the number
		setCell(max_i, max_j, valid_numbers[i]);
		// if the board is solved, return true
        if (Solve(counter)) return true;
		//cout << "Resetting the cell..." << endl;
        // board is not solved, reset the cell
		resetCell(max_i, max_j);
		//cout << "Cell reset" << endl;
    }

	//cout << "returning false at funciton completion" << endl;
	return false;
}