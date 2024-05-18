#pragma once
#include <iostream>

#include "code.h"
#include "Response.h"

using namespace std;
#include "code.h"
#include "Response.h"


using namespace std;

class Mastermind
{
public:
	Mastermind();
	Mastermind(int n, int m);
	void playGame(Code secretCode);
public:
	Mastermind();
	Mastermind(int n, int m);


private:
	Code secretCode;
	Code humanGuess();
	Response getResponse(Code guess);
	bool isSolved(Response response);
	void revealCode();
	int n;
	int m;
};