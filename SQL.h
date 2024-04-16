#pragma once
#ifndef _SQL_H_
#define _SQL_H_
#include<string>
#include"Data.h"
using namespace std;
class SQL {
public:
	void INSERT_INTO(string st, string a);//INSERT_INTO instruction
	void UPDATE(string st);//UPDATE instruction
	void SELECT(string st, string st0);//SELECT instruction
	void SELECT(string st, string st0, string a);//SELECT instruction,User - related information is needed
	void SELECT_ALL(string st);//show all TABLE
	void SELECT_PART(string st, string st0);//show part TABLE
private:
	void Save_to_commands(string st);
	friend void Get(ifstream& IFS, string st[], string st2);//get first line
	friend bool Get(ifstream& IFS, commodity& CO);//Gets the value in the file
	friend bool Get(ifstream& IFS, order& OR);//Gets the value in the file
	friend bool Get(ifstream& IFS, user& US);//Gets the value in the file
	friend bool Get(ifstream& IFS, shopping_cart& SH);//Gets the value in the file
	friend bool Get(ifstream& IFS, message& ME);//Gets the value in the file
	void Show_first(ifstream& IFS, string st1[], string st2, string st0);//show first line
	void Show(ifstream& IFS, string st, string st0);//show all
	void Show(ifstream& IFS, string st1,string st2,string st3, string st0);//Show the required content of string st
	string F = "FROM";
	string W = "WHERE";
	string C = "CONTAINS";
};
void Get(ifstream& IFS, string st[], string st2);//get first line
bool Get(ifstream& IFS, commodity& CO);//Gets the value in the file
bool Get(ifstream& IFS, order& OR);//Gets the value in the file
bool Get(ifstream& IFS, user& US);//Gets the value in the file
bool Get(ifstream& IFS, shopping_cart& SH);//Gets the value in the file
bool Get(ifstream& IFS, message& ME);//Gets the value in the file
#endif