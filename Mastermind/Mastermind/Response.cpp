#include "Response.h"
#include <iostream>
#include <vector>
using namespace std;

Response::Response() {
	num_correct = 0;
	num_incorrect = 0;
}

void Response::setNumCorrect(int x) { num_correct = x; }
void Response::setNumIncorrect(int y) { num_incorrect = y; }

bool operator==(Response const& res_1, Response const& res_2) {
	return ((res_1.num_correct == res_2.num_correct) && (res_1.num_incorrect == res_2.num_incorrect));
}

ostream& operator<<(ostream& ostr, const Response& res) {
	ostr << "Num Correct: " << res.num_correct << " Num Incorrect: " << res.num_incorrect;
	return ostr;
}

int Response::getCorrect() { return num_correct; }

int Response::getIncorrect() { return num_incorrect; }