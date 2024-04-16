#pragma once
#ifndef _SELLERS_H_
#define _SELLERS_H_
#include<string>
using namespace std;
void Sellers_Model(string a);
class Sellers {
public:
	void Menu();//Sellers menu
	void Onsale_Commodity(string a);//Update commodities
	void Check_Onsale_Commodity(string a);//View commodities 
	void Modify_Commodity_Infor(string a);//Modify commodities information 
	void Remove_Commodity(string a);//Remove commodities 
	void Check_Orders(string a);//Check order history
};
#endif

