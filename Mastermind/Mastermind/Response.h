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
	void setNumIncorrect(int y);

private:
	int num_correct;
	int num_incorrect;
	
};


