#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include"Administrator.h"
#include"SQL.h"

void Administrator_Model() {
	Administrator AD;
	string a, b;
	cout << "Please enter the administrator's name:";
	getline(cin, a);
	cout << "Please enter your password:";
	getline(cin, b);
	cout << endl << endl;
	string st=AD.Login(a, b);//judge login successfully
	cout << st << endl << endl << endl;
	if (st != "-----SUCCESS-----")
		return;
	string option;
	while (true) {
		AD.Menu();//Admin Menu
		getline(cin, option);
		if (option == "1") {
			AD.Check_Commodity();//View all the commodities
		}
		else if (option == "2") {
			AD.Search_Commodity();//Search the commodities
		}
		else if (option == "3") {
			AD.Remove_Commodity();//Remove the commodities
		}
		else if (option == "4") {
			AD.Check_Orders();//View all the orders
		}
		else if (option == "5") {
			AD.Check_Users();//View all the users
		}
		else if (option == "6") {
			AD.Ban_User();//Block User
		}
		else if (option == "7") {
			break;
		}
		else {
			cout << "Illegal input!Please re-enter!" << endl << endl << endl;
		}
	}
}
string Administrator::Login(string a, string b) {
	if (a == "admin" && b == "123456")
		return "-----SUCCESS-----";
	else if (a != "admin")
		return "------Administrator's name does not exist, returns to the main menu------";
	else return "-----Wrong password,the logon fails,return to the main menu-----";
}
void Administrator::Menu() {
	cout << "==============================================================================================================================================" << endl;
	cout << "1.View all the commodities 2.Search the commodities 3.Remove the commodities 4.View all the orders 5.View all the users 6.Ban the users 7.Exit " << endl;
	cout << "==============================================================================================================================================" << endl << endl << endl;
	cout << "Input operation:";
}
void Administrator::Check_Commodity() {
	string st = "SELECT * FROM commodity";
	SQL S;
	S.SELECT(st,"Administrator");
}
void Administrator::Search_Commodity() {
	string st, st1;
	cout << "Please enter a Commodity Name:";
	getline(cin, st);
	st1 = "SELECT * FROM commodity WHERE commodityName CONTAINS " + st;
	SQL S;
	S.SELECT(st1, "Administrator");
}
void Administrator::Remove_Commodity() {
	string st1, st2;
	cout << "Please confirm that you want off the shelf product ID:";
	getline(cin, st1);
	st2 = "SELECT * FROM commodity WHERE commodityID CONTAINS " + st1;
	SQL S;
	S.SELECT_PART(st2, "Administrator");
}
void Administrator::Check_Orders() {
	string st = "SELECT * FROM order";
	SQL S;
	S.SELECT(st, "Administrator");
}
void Administrator::Check_Users() {
	string st = "SELECT * FROM user";
	SQL S;
	S.SELECT(st, "Administrator");
}
void Administrator::Ban_User() {
	string st1, st2;
	cout << "Please confirm that you want to ban user ID:";
	getline(cin, st1);
	st2 = "SELECT * FROM user WHERE userID CONTAINS " + st1;
	SQL S;
	S.SELECT_PART(st2, "Administrator");
}


