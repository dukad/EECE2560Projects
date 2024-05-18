#include <iostream>
#include <vector>
#include "Mastermind.h"
#include "code.h"
#include "Response.h"

int main(){
	int n, m;
	cout << "Enter the desired code length: ";
	cin >> n;
	cout << "Enter the maximum digit value (m-1): ";
	cin >> m;
	Mastermind M(n, m);
	M.playGame();
	return 0;
}
