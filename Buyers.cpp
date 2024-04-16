#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<sstream>
#include<ctime>
#include<iomanip>
#include<string>
#include"Buyers.h"
#include"SQL.h"
#include"Data.h"
#include"Judge.h"
#include"Shopping_cart.h"
using namespace std;

void Buyers_Model(string a) {
	Buyers BY;
	string option;
	while (true) {
		BY.Menu();//Buyers menu
		getline(cin, option);
		if (option == "1") {
			BY.Check_Onsale_Commodity();//View onsale commodities
		}
		else if (option == "2") {
			BY.Buy_Commodity(a);//Purchase commodities
		}
		else if (option == "3") {
			BY.Search_Commodity();//Search the commodities
		}
		else if (option == "4") {
			BY.Check_Orders(a);//View order history
		}
		else if (option == "5") {
			BY.Check_Comodity_Infor();//View commodity details
		}
		else if (option == "6") {
			Shopping_cart_Model(a);//shopping cart
		}
		else if (option == "7") {
			break;
		}
		else {
			cout << "Illegal input!Please re-enter!" << endl << endl << endl;
		}
	}
}
void Buyers::Menu() {
	cout << "==================================================================================================================================================================" << endl;
	cout << "1.View onsale commodities 2.Purchase commodities 3.Search the commodities 4.View order history 5.View commodity details 6.Shopping cart 7.Return to the main menu " << endl;
	cout << "==================================================================================================================================================================" << endl << endl << endl;
	cout << "Input operation:";
}
void Buyers::Check_Onsale_Commodity() {
	SQL S;
	string st = "SELECT * FROM commodity";
	S.SELECT(st, "Buyers");
}
void Buyers::Search_Commodity() {
	SQL S;
	string st;
	cout << "Please enter a Commodity Name:";
	getline(cin, st);
	string st1 = "SELECT * FROM commodity WHERE commodityName CONTAINS " + st;
	S.SELECT(st1, "Buyers");
}
void Buyers::Check_Orders(string a) {
	ifstream ifs;
	ifs.open("user.txt", ios::in);
	char ch[200];
	ifs.getline(ch, 200);
	int num = 0;
	user US[100];
	bool judge = Get(ifs, US[num]);
	while (!ifs.eof()) {
		int j = ifs.get();
		if (j != -1)
		{
			//IFS.seekg(-1, ios::cur);
			num++;
			judge = Get(ifs, US[num]);
		}
	}
	ifs.close();
	for (int i = 1; i <= num; i++)
		US[i].userID = "U0" + US[i].userID;
	int i = 0;
	for (; i <= num; i++) {
		if (US[i].username == a)
			break;
	}
	SQL S;
	string st = "SELECT * FROM order";
	S.SELECT(st, "Buyers", US[i].userID);
}
void Buyers::Check_Comodity_Infor() {
	cout << "Please enter the item ID that you want to view :";
	string st1;
	getline(cin, st1);
	SQL S;
	string st = "SELECT * FROM commodity WHERE commodityID CONTAINS " + st1;
	S.SELECT(st,"Buyers");
}
void Buyers::Buy_Commodity(string a) {
	ifstream ifs,IFS,ifs1;
	ifs.open("user.txt", ios::in);
	char ch[200];
	ifs.getline(ch, 200);
	int num = 0;
	user US[100];
	bool judge = Get(ifs, US[num]);
	while (!ifs.eof()) {
		int j = ifs.get();
		if (j != -1)
		{
			//IFS.seekg(-1, ios::cur);
			num++;
			judge = Get(ifs, US[num]);
		}
	}
	ifs.close();
	for (int i = 1; i <= num; i++)
		US[i].userID = "U0" + US[i].userID;
	int i = 0;
	for (; i <= num; i++) {
		if (US[i].username == a)
			break;
	}
	string st1;
	cout << "Please enter a Commodity ID:";
	getline(cin, st1);
	IFS.open("commodity.txt", ios::in);
	char ch1[200];
	IFS.getline(ch1, 200);
	int num1 = 0;
	commodity CO[100];
	bool judge1 = Get(IFS, CO[num1]);
	while (!IFS.eof()) {
		int j = IFS.get();
		if (j != -1)
		{
			//IFS.seekg(-1, ios::cur);
			num1++;
			judge1 = Get(IFS, CO[num1]);
		}
	}
	IFS.close();
	for (int i = 1; i <= num1; i++)
		CO[i].commodityID = "M0" + CO[i].commodityID;
	int j = 0;
	for (; j <= num1; j++) {
		if (CO[j].commodityID == st1)
			break;
	}
	if (j == num1 + 1) {
		cout << "Could not find the item you want!" << endl;
		cout << endl << endl;
		return;
	}
	if (CO[j].sellerID == US[i].userID)
	{
		cout << "Unable to purchase your own commodities!" << endl;
		cout << endl << endl;
		return;
	}
	if (CO[j].state == 0) {
		cout << "Could not find the item you want!" << endl;
		cout << endl << endl;
		return;
	}
	string st2;
	int n = 0;
	cout << "Please enter the number you want:";
	while (true) {
		bool judge = false;
		getline(cin, st2);
		if (!Judge_Number(st2)) {
			cout << "The number are not allowed!" << endl << "Please re-enter:";
			judge = true;
		}
		if (!judge) {
			stringstream ss;
			ss << st2;
			while (ss >> st2) {
				n = convert<int>(st2);
			}
			if (n <= 0) {
				cout << "The number are not allowed!" << endl << "Please re-enter:";
				judge = true;
			}
		}
		if (!judge)
			break;
	}
	if (n > CO[j].number) {
		cout << "Insufficient number of commodities!" << endl;
		cout << endl << endl;
		return;
	}
	double new_balance = US[i].balance - n * CO[j].price;
	if (new_balance < 0) {
		cout << "Insufficient balance! Purchase of failed!" << endl;
		cout << endl << endl;
		return;
	}
	time_t nowtime;
	struct tm* p;
	time(&nowtime);
	p=localtime(&nowtime);
	cout << endl << endl;
	cout << "Trade Reminding!" << endl;
	cout << "Trade Time:" << p->tm_year + 1900 << "-" <<
		setw(2) << setfill('0') << p->tm_mon << "-" <<
		setw(2) << setfill('0') << p->tm_mday << endl;
	cout << setfill(' ');
	cout << "Trade Unit Price:" << fixed << setprecision(1) << CO[j].price << endl;
	cout << "Trade Quantity:" << st2 << endl;
	cout << "Transaction status : The success of the transaction !" << endl;
	cout << "Your Balance:" << fixed << setprecision(1) << new_balance << endl;
	cout << endl << endl;
	ifs1.open("order.txt", ios::in);
	char ch2[200];
	ifs1.getline(ch2, 200);
	int num2 = 0;
	order OR[100];
	bool judge2 = Get(ifs1, OR[num2]);
	while (!ifs1.eof()) {
		int j = ifs1.get();
		if (j != -1)
		{
			//IFS.seekg(-1, ios::cur);
			num2++;
			judge2 = Get(ifs1, OR[num2]);
		}
	}
	ifs1.close();
	int num3 = num2 + 2 + 1000;
	string number;
	stringstream ss1;
	ss1 << num3;
	while (ss1 >> num3) {
		number = convert<string>(num3);
	}
	string number1 = number.substr(1);
	string PRICE;
	stringstream ss2;
	ss2 << CO[j].price;
	while (ss2 >> CO[j].price) {
		PRICE = convert<string>(CO[j].price);
	}
	size_t year = p->tm_year + 1900;
	string YEAR;
	stringstream ss3;
	ss3 << year;
	while (ss3 >> year) {
		YEAR = convert<string>(year);
	}
	string MONTH;
	stringstream ss4;
	ss4 << p->tm_mon;
	while (ss4 >> p->tm_mon) {
		MONTH = convert<string>(p->tm_mon);
	}
	string MDAY;
	stringstream ss5;
	ss5 << p->tm_mday;
	while (ss5 >> p->tm_mday) {
		MDAY = convert<string>(p->tm_mday);
	}
	SQL S;
	string st0 = "INSERT INTO order VALUES(";
	string st100 = st0 + "T" + number1 + "," + CO[j].commodityID + "," +
		PRICE + "," + st2 + "," + YEAR + "-" + MONTH + "-" + MDAY +
		"," + CO[j].sellerID + "," + US[i].userID + ")";
	S.INSERT_INTO(st100,"SELLERS");
	int n1 = CO[j].number - n;
	string NUMBER;
	stringstream ss6;
	ss6 << n1;
	while (ss6 >> n1) {
		NUMBER = convert<string>(n1);
	}
	string st101 = "UPDATE commodity SET number = " + NUMBER + " WHERE commodityID = " + CO[j].commodityID;
	S.UPDATE(st101);
}

