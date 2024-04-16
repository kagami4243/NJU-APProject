#pragma once
#ifndef _CALCULATOR_
#define _CALCULATOR_
#include<sstream>
#include<vector>
#include<stack>
#include"Data.h"
using namespace std;
class Calculate {
public:
	string getResult(string st);//get result
	void getPostfix(string st);//Converted to a postfix expression
	string calculate(string st);//External interface
	int get_Level(char ch);//Judge operator priority
	string IsLegal(string st);//Judge the legality of the expression
	string solve_Negative(string st);//Dealing with negative numbers
private:
	vector<string> postfix;//Storage postfix expression
	stack<char> signal;//Storage operator
	stack<double> figure;//Storage figures
	double op1 = 0, op2 = 0;//two figures are used to calculate
};
#endif