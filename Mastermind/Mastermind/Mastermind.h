#pragma once
#include <iostream>
#include <vector>
#include "code.h"
#include "Response.h"

using namespace std;


class Mastermind
{
public:
	// default constructor
	Mastermind();
	// constructor with inputs
	Mastermind(int n, int m);
	// play the game
	void playGame();


private:
	// private member variables
	Code secretCode;
	int n;
	int m;
	// private member functions
	Code humanGuess();
	Response getResponse(Code guess);
	bool isSolved(Response response);
	void revealCode();
	
};