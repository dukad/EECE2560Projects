#include "code.h"
#include <vector>
#include <iostream>
#include <random>

Code::Code()
{
	// default constructor
	n = 5;
	m = 10;
	code_vector = std::vector<int>(n);
	srand(time(NULL)); // random seeding for random number generation
}

// constructors
Code::Code(int n, int m)
{
	// store length n and range m
	this->n = n;
	this->m = m;
	// declare vecotr of length n
	code_vector = std::vector<int>(n);
	srand(time(NULL)); // random seeding for random number generation
}

Code::Code(int codeArray[], int length)
{
	for (int i = 0; i < length; i++)
	{
		code_vector.push_back(codeArray[i]);
	}
	// set n to be the length of the code vector
	n = length;
	// set m to be the range of the code vector
	m = 0;
	for (int i = 0; i < length; i++)
	{
		if (codeArray[i] > m)
		{
			m = codeArray[i];
		}
	}
	m++;
}

Code::Code(std::vector<int> codeVector, int length)
{
	code_vector = codeVector;

	// set n to be the length of the code vector
	n = length;
	// set m to be the range of the code vector
	m = 0;
	for (int i = 0; i < length; i++)
	{
		if (codeVector[i] > m)
		{
			m = codeVector[i];
		}
	}
	m++;
}

void Code::initializeRandom()
{
	for (int i = 0; i < n; i++)
	{
		// generate random between 0 and m with seed of time
		
		code_vector[i] = rand() % m;

	}
}

int Code::checkCorrect(Code guess)
{
	int correct = 0;
	for (int i = 0; i < n; i++)
	{
		if (code_vector[i] == guess.code_vector[i])
		{
			correct++;
		}
	}
	return correct;
}

int Code::checkIncorrect(Code guess)
{
	// create a copy of the guess as just a vector
	std::vector<int> guess_vector = guess.code_vector;
	std::vector<int> code_copy = code_vector;
	// iterate through the code and the guess
	for (int i = n-1; i >= 0; i--) {
		if (guess.code_vector[i] == code_vector[i]) {
			// remove the guess from the copy
			guess_vector.erase(guess_vector.begin() + i);
			code_copy.erase(code_copy.begin() + i);
		}
	}
	// we now have two vectors that have any correct numbers removed
	// simply iterate through the guess and check if its in the code
	// print out the vector copies
	
	int incorrect = 0;
	
	// while the guess vector still has elements
	while (guess_vector.size() > 0) {
		// check to see if the first element is in the code
		if (std::find(code_copy.begin(), code_copy.end(), guess_vector[0]) != code_copy.end()) {
			// store the value
			int remove_value = guess_vector[0];
			// if it is, remove it from both vectors
			code_copy.erase(std::find(code_copy.begin(), code_copy.end(), guess_vector[0]));
			guess_vector.erase(guess_vector.begin());
			// increment the incorrect counter
			incorrect++;
		}
		else {
			// if it is not, remove it from the guess vector
			guess_vector.erase(guess_vector.begin());
		}
	}

	

	
	return incorrect;
}

void Code::reveal()
{
	for (int i = 0; i < n; i++)
	{
		std::cout << code_vector[i] << " ";
	}
	std::cout << std::endl;
}

//operator overload
std::ostream& operator<<(std::ostream& os, const Code& code)
{
	for (int i = 0; i < code.n; i++)
	{
		os << code.code_vector[i] << " ";
	}
	return os;
}