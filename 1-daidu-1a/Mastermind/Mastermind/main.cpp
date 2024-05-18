#include <iostream>

#include <vector>

#include "code.h"

int main()
{
	const int length = 5;
	int range = 10;
	// initialize a new code object randomly
	Code secret_code(5, 10);
	secret_code.initializeRandom();

	std::cout << "You are playing mastermind! Try to guess the secret code!" << std::endl;

	// guesses are //
	// ((5, 0, 3, 2, 6), 
	// //(2, 1, 2, 2, 2),
	//(1, 3, 3, 4, 5))
	
	// create empty vector of code obejcts
	std::vector<Code> guesses;
	// add the guesses to the vecotr
	int array_guess1[length] = { 5, 0, 3, 2, 6 };
	int array_guess2[length] = { 2, 1, 2, 2, 2 };
	int array_guess3[length] = { 1, 3, 3, 4, 5 };

	guesses.push_back(Code(array_guess1, length));
	guesses.push_back(Code(array_guess2, length));
	guesses.push_back(Code(array_guess3, length));

	bool success = false;
	// loop through the guesses
	for (int i = 0; i < guesses.size(); i++)
	{

		// get the feedback
		int correct = secret_code.checkCorrect(guesses[i]);
		int incorrect = secret_code.checkIncorrect(guesses[i]);

		// print the feedback to the console
		std::cout << "Guess " << i + 1 << ": " << guesses[i] << std::endl;
		
		std::cout << "Correct: " << correct << std::endl;
		std::cout << "Incorrect: " << incorrect << std::endl;

		// if the guesses were all correct, print success and break
		if (correct == length)
		{
			std::cout << "Congratulations! You guessed the secret code!" << std::endl;
			success = true;
			break;
		}

	}
	if (!success)
	{
		std::cout << "Sorry! You did not guess the secret code!" << std::endl;
	}

	// reveal the secret code
	std::cout << "The secret code was: ";
	secret_code.reveal();

	return 0;
}

