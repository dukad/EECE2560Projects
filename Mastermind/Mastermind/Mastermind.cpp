#include "Mastermind.h"
#include <iostream>

#include "code.h"
#include "Response.h"
#include <vector>

using namespace std;

Mastermind::Mastermind()
{
	n = 5;
	m = 10;
	secretCode = Code(n, m);
}

Mastermind::Mastermind(int n, int m)
{
	this->n = n;
	this->m = m;
	secretCode = Code(n, m);
}

Code Mastermind::humanGuess()
{
	vector<int> guessVector(n);
	cout << "Enter your guess, pressing enter in between every digit: ";
	for (int i = 0; i < n; i++)
	{
		cin >> guessVector[i];
	}

	Code guess = Code(guessVector, n);
	return guess;
}

Response Mastermind::getResponse(Code guess)
{
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
	secretCode.reveal();
}
