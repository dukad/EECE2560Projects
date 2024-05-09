#include <iostream>
#include <vector>


int main()
{
	// prompt the user for the range of elements and the number of elements
	bool success = false;
	int range, numElements;
	std::cout << "Enter the range of elements: ";
	std::cin >> range;
	std::cout << "Enter the number of elements: ";
	std::cin >> numElements;

	// create a vector to store the elements
	std::vector<int> elements;
	// generate random numbers and store them in the vector
	for (int i = 0; i < numElements; i++)
	{
		elements.push_back(rand() % range);
	}

	// allow the user to take ten guesses to guess the numbers in the vector
	//initialize a vector to store the guesses
	std::vector<int> guesses;
	// iterate ten times
	for (int i = 0; i < 10; i++)
	{
		// prompt the user for a guess
		// iterate through vecotor and add for range
		for (int j = 0; j < numElements; j++)
		{
			std::cout << "Enter your guess: ";
			int guess;
			std::cin >> guess;
			// store the guess in the vector
			guesses.push_back(guess);
		}
		// compare the guess to the elements in the vector. If t
		int correct = 0;
		int inAnswer = 0;
		for (int j = 0; j < numElements; j++)
		{
			if (guesses[j] == elements[j])
			{
				correct++;
			}
			else
			{
				// check to see if the guess is in the vector at all
				bool inAnswerBool = false;
				for (int k = 0; k < numElements; k++)
				{
					if (guesses[j] == elements[k])
					{
						inAnswerBool = true;
					}
				}
				if (inAnswerBool)
				{
					inAnswer++;
				}
			}
			
		}
		// print the results for the user
		std::cout << "Correct: " << correct << std::endl;
		std::cout << "In Answer: " << inAnswer << std::endl;

		// if correct is equal to the number of elements, the user has guessed all the numbers
		if (correct == numElements)
		{
			std::cout << "You have guessed all the numbers!" << std::endl;
			success = true;
			break;
		}
		// clear the guesses vector
		guesses.clear();

	}
	// guesses are over, check to see if the user has guessed all the numbers
	if (success) {
		std::cout << "Congratulations!" << std::endl;
	}
	else {
		std::cout << "You have run out of guesses!" << std::endl;
	}
	// print the elements in the vecotr
	std::cout << "The elements were: ";
	for (int i = 0; i < numElements; i++)
	{
		std::cout << elements[i] << " ";
	}
	//press enter to exit
	std::cin >> range;

	return 0;
}