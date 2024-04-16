#pragma once
#ifndef _ADMINISTRATOR_H_
#define _ADMINISTRATOR_H_
#include<string>
using namespace std;
void Administrator_Model();
class Administrator {
public:
	string Login(string a, string b);//Administrator Login
	void Menu();//Administrator menu
	void Check_Commodity();//View all the commodities
	void Search_Commodity();//Search the commodities
	void Remove_Commodity();//Remove the commodities
	void Check_Orders();//View all the orders
	void Check_Users();//View all the users
	void Ban_User();//Ban users
};
#endif