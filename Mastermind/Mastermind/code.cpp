#include "code.h"
#include <vector>
#include <iostream>
#include <random>

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
	int incorrect = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i != j) {
				if (code_vector[i] == guess.code_vector[j])
				{
					incorrect++;
			}
			}
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