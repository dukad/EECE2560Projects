#pragma once

#include <iostream>
#include "d_matrix.h"
#include <vector>

typedef int ValueType;

class board
    // Stores the entire Sudoku board
{
public:
    board(int);
    void clear();
    void initialize(ifstream& fin);
    void print();
    bool isBlank(int, int);
    ValueType getCell(int, int);
    void setCell(int i, int j, int val);
    void resetCell(int i, int j);
    void printConflicts();
private:

    // The following matrices go from 1 to BoardSize in each
    // dimension, i.e., they are each (BoardSize+1) * (BoardSize+1)

    matrix<ValueType> value;

    // initialize boolean vectors for conflicts coutners, first index is row, second is value
	matrix<bool> row_conflicts;
	matrix<bool> col_conflicts;
	matrix<bool> box_conflicts;

};