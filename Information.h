#pragma once
#ifndef _INFORMATION_H_
#define _INFORMATION_H_
#include<string>
using namespace std;
void Infor_Mana(string a);
class Information {
public:
	void Menu();//Personal information menu
	void Check(string a);//View Personal Information
	void Modify(string a);//Update Personal Information 
	void reCharge(string a);//Charge
	string GET_EXPRESSION(string a);//get the expression of balance
private:
	struct Expression {
		string number;
		string price[100];
		int price_number;
	};
};
#endif
