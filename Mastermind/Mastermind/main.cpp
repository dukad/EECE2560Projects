#include <iostream>
#include <vector>
#include "Mastermind.h"
#include "code.h"
#include "Response.h"

int main(){
	Mastermind M(5, 10);
	M.playGame();
	return 0;
}
