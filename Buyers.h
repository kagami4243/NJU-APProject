#pragma once
#ifndef _BUYERS_H_
#define _BUYERS_H_
#include<string>
using namespace std;
void Buyers_Model(string a);
class Buyers {
public:
	void Menu();//Buyers menu
	void Check_Onsale_Commodity();//View onsale commodities
	void Buy_Commodity(string a);//Purchase commodities
	void Search_Commodity();//Search the commodities
	void Check_Orders(string a);//View order history
	void Check_Comodity_Infor();//View commodity details
};
#endif
