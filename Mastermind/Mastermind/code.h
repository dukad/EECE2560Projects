#include <iostream>
#incldue <vector>

// secret code object
class Code
{
public:
	// constructor
	Code(int range, int numElements);
	// destructor
	~Code();
	// member function to compare the guess to the code
	void compareGuess(int* guess, int* correct, int* inAnswer);
	// member function to print the code
	void revealCode();
private:
	//secret code vector object
	std::vector<int> code;
};