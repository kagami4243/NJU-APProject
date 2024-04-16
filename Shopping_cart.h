#pragma once
#ifndef _SHOPPING_CART_
#define _SHOPPING_CART_
#include<string>
using namespace std;
void Shopping_cart_Model(string a);
class Shopping_cart {
public:
	void Menu();//shopping cart menu
	void view_shopping_cart(string a);//view shopping cart
	void move_into(string a);//move into the shopping cart
	void remove(string a);//remove the shopping cart
	void empty(string a);//empty the shopping cart
};
#endif