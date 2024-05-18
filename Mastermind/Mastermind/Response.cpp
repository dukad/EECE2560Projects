#include "Response.h"
#include <iostream>
#include <vector>
using namespace std;

//default constructor
Response::Response() {
	num_correct = 0;
	num_incorrect = 0;
}
//functions to set the response correct/incorrect values
void Response::setNumCorrect(int x) { num_correct = x; }
void Response::setNumIncorrect(int y) { num_incorrect = y; }

//overload == operator
bool operator==(Response const& res_1, Response const& res_2) {
	return ((res_1.num_correct == res_2.num_correct) && (res_1.num_incorrect == res_2.num_incorrect));
}

//overload << print operator
ostream& operator<<(ostream& ostr, const Response& res) {
	ostr << "Num Correct: " << res.num_correct << " Num Incorrect: " << res.num_incorrect;
	return ostr;
}

//functions to get the response correct/incorrect values
int Response::getCorrect() { return num_correct; }
int Response::getIncorrect() { return num_incorrect; }