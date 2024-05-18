#pragma once


#include <iostream>
#include <vector>

// secret code object
class Code
{
public:
	// constructor
	Code(int n, int m);
	Code(int codeArray[], int length);
	// member function to compare the guess to the code
	int checkCorrect(Code guess);
	int checkIncorrect(Code guess);
	void initializeRandom();
	// reveal the code
	void reveal();
	// overload << operator
	friend std::ostream& operator<<(std::ostream& os, const Code& code);
	
	//
private:
	//secret code vector object
	std::vector<int> code_vector;
	int n;
	int m;
};

