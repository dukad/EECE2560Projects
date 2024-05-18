#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Response {

public: 
	//default constructor listed, made in cpp
	Response();
	//friend for global scope operator overloads
	friend bool operator==(const Response& res_1, const Response& res_2);
	friend ostream& operator<<(ostream& ostr, const Response& res);
	//set and get functions
	void setNumCorrect(int x);
	void setNumIncorrect(int y);
	int getCorrect();
	int getIncorrect();

private:
	//private attributes for response
	int num_correct;
	int num_incorrect;
	
};


