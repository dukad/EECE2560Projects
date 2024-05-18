#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Response {

public: 
	Response();
	friend bool operator==(const Response& res_1, const Response& res_2);
	friend ostream& operator<<(ostream& ostr, const Response& res);
	void setNumCorrect(int x);
	void setNumIncorrect(int y) { num_incorrect = y; };

private:
	int num_correct;
	int num_incorrect;

};


bool operator==(Response const& res_1, Response const& res_2) {
	return ((res_1.num_correct == res_2.num_correct) && (res_1.num_incorrect == res_2.num_incorrect));
}

ostream& operator<<(ostream& ostr, const Response& res) {
	ostr << "Num Correct: " << res.num_correct << "Num Incorrect: " << res.num_incorrect;
	return ostr;
}