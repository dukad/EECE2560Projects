#pragma once
#include "Mastermind.h"
#include <iostream>

#include "code.h"
#include "Response.h"
#include <vector>

using namespace std;

Mastermind::Mastermind()
{
	// default constructor with default values!
	n = 5;
	m = 10;
	secretCode = Code(n, m);
}

Mastermind::Mastermind(int n, int m)
{
	// taking inputs for both length and range
	this->n = n;
	this->m = m;
	secretCode = Code(n, m);
}

Code Mastermind::humanGuess()
{
	// create a vector to store the guess
	vector<int> guessVector(n);
	// ask the user for their guess
	cout << "Enter your guess, pressing enter in between every digit: \n";
	for (int i = 0; i < n; i++)
	{
		while (!(cin >> guessVector[i])) {
			// guess is invalid
			cout << "Invalid input. Please enter a valid digit: ";
			// clear all of the input
			cin.clear();
			cin.ignore(10000, '\n');
		}
		if (guessVector[i] >= m || guessVector[i] < 0)
		{
			cout << "Invalid input. Please enter a valid number in the range 0 to " << m << ": \n";
			i--;
		}
		
	}
	// create a code object with the guess vector
	Code guess = Code(guessVector, n);
	return guess;
}

Response Mastermind::getResponse(Code guess)
{
	// check the guess against the secret code
	int correct = secretCode.checkCorrect(guess);
	int incorrect = secretCode.checkIncorrect(guess);
	Response response = Response();
	response.setNumCorrect(correct);
	response.setNumIncorrect(incorrect);
	return response;
}

bool Mastermind::isSolved(Response response)
{
	// create a response object with 5 correct and 0 incorrect
	Response correctResponse = Response();
	correctResponse.setNumCorrect(n);
	correctResponse.setNumIncorrect(0);
	// compare the response to the correct response
	return (response == correctResponse);
}

void Mastermind::revealCode()
{
	// reveal the secret code
	secretCode.reveal();
}
void Mastermind::playGame() {
	//Generate and print a random code object
	secretCode.initializeRandom();
	secretCode.reveal();
	//Iterate through user guesses 10 times
	for (int i = 0; i < 10; i++) {
		//Intake guess from user then generate response
		Code guess = humanGuess();
		Response res = getResponse(guess);
		//print response and win/lose case
		cout << "Response (" << i+1 << "/10): " << res << endl;
		if (isSolved(res)) {
			cout << "You Win!!!" << endl;
			break;
		}
		else if (i == 9) {
			cout << "You Lose." << endl;
		}
	}
}