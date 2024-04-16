#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<sstream>
#include<iomanip>
#include<fstream>
#include"Sellers.h"
#include"Judge.h"
#include"Data.h"
#include"SQL.h"
using namespace std;
void Sellers_Model(string a) {
	Sellers SE;
	while (true) {
		SE.Menu();//Sellers menu
		string option;
		getline(cin,option);
		if (option == "1") {
			SE.Onsale_Commodity(a);//update commodities in stock
		}
		else if (option == "2") {
			SE.Check_Onsale_Commodity(a);//view commodities
		}
		else if (option == "3") {
			SE.Modify_Commodity_Infor(a);//Modify commodities information
		}
		else if (option == "4") {
			SE.Remove_Commodity(a);//remove commodities
		}
		else if (option == "5") {
			SE.Check_Orders(a);//check order history
		}
		else if (option == "6") {
			break;
		}
		else {
			cout << "Illegal Input!Please re-enter:" << endl << endl << endl;
		}
	}
}
void Sellers::Menu() {
	cout << "===============================================================================================================================================" << endl;
	cout << "1.Update commodities 2.View commodities 3.Modify commodities information 4.Remove commodities 5.Check order history 6.Return to the main menu " << endl;
	cout << "===============================================================================================================================================" << endl << endl << endl;
	cout << "Input operation:";
}
void Sellers::Onsale_Commodity(string a) {
	string st1, st2;
	string price;
	string number;
	cout << "Please enter Commodity Name:";
	while (true) {
		getline(cin, st1);
		int len = st1.length();
		if (len > 20) {
			cout << "Commodity Name are not allowed to be longer than 20 characters!" << endl << "Please re-enter:";
		}
		else if (!Judge_English(st1)) {
			cout << "Contains illegal characters! Commodity Name include only English letters!" << endl << "Please re-enter:";
		}
		else break;
	}
	cout << "Please enter Commodity UnitPrice:";
	double p = 0;
	while (true) {
		bool judge = false;
		getline(cin, price);
		if (!Judge_One_Decimal(price)) {
			cout << "You need the exact price to one decimal or prices that are not allowed!" << endl << "Please re-enter:";
			judge = true;
		}
		if (!judge) {
			stringstream ss;
			ss << price;
			while (ss >> price) {
				p = convert<double>(price);
			}
			if (p <= 0) {
				cout << "Prices that are not allowed!" << endl << "Please re-enter:";
				judge = true;
			}
		}
		if (!judge)
			break;
	}
	cout<<"Please enter Commodity Number:";
	int n = 0;
	while (true) {
		bool judge = false;
		getline(cin, number);
		if (!Judge_Number(number)) {
			cout << "Numbers that are not allowed!" << endl << "Please re-enter:";
			judge = true;
		}
		if (!judge) {
			stringstream ss;
			ss << number;
			while (ss >> number) {
				n = convert<int>(number);
			}
			if (n <= 0) {
				cout << "Numbers that are not allowed!" << endl << "Please re-enter:";
				judge = true;
			}
		}
		if (!judge)
			break;
	}
	cout << "Please enter Commodity Description:";
	while (true) {
		getline(cin,st2);
		int len = st2.length();
		if (len > 200) {
			cout << "Commodity Description are not allowed to be longer than 200 characters!" << endl << "Please re-enter:";
		}
		else if (st2 == "") {
			cout << "Illegal Input !"<< endl << "Please re-enter:";
		}
		else break;
	}
	cout << endl << endl;
	cout << "Verify that the published commodity information is correct!";
	cout << endl << endl;
	cout << "Commodity Name:" << st1 << endl
		<< "Commodity UnitPrice:" << fixed << setprecision(1) << p << endl
		<< "Commodity Number:" << setprecision(0) << n << endl
		<< "Commodity Description:" << st2 << endl << endl;
	cout << "Are you sure to update the commodity?(y/n) ";
	string option;
	getline(cin, option);
	if (option == "y") {
		cout << "Update the commodity successfully!" << endl << endl << endl;
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
		string st = "INSERT INTO commodity VALUES(" + st1 + ","
			+ price + "," + number + "," + st2 + ")";
		SQL S;
		S.INSERT_INTO(st, US[i].userID);
	}
	else if (option == "n")
		cout << "Cancel your update!" << endl << endl << endl;
	else {
		cout << "Illegal Input! Return to the menu!" << endl << endl << endl;
		return;
	}
}
void Sellers::Check_Onsale_Commodity(string a) {
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
	string st = "SELECT * FROM commodity";
	S.SELECT(st, "Sellers", US[i].userID);
}
void Sellers::Modify_Commodity_Infor(string a) {
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
	string st1;
	cout << "Please enter the Commodity ID you want to modify: ";
	getline(cin, st1);
	ifstream IFS;
	IFS.open("commodity.txt", ios::in);
	char ch1[200];
	IFS.getline(ch1, 200);
	int num1 = 0;
	commodity CO[100];
	bool judge1 = Get(IFS, CO[num1]);
	while (!IFS.eof()) {
		IFS.seekg(-1, ios::cur);
		num1++;
		judge1 = Get(IFS, CO[num1]);
	}
	IFS.close();
	int j = 0;
	for (; j <= num1; j++) {
		if (CO[j].commodityID == st1)
			break;
	}
	if (CO[j].sellerID != US[i].userID) {
		cout << "This is not your published commodity! Cannot modify the information!" << endl;
		cout << endl << endl;
		return;
	}
	cout << "Please input the properties of the commodities you want to update(1.UnitPrice 2.Description):";
	string st2;
	getline(cin, st2);
	if (st2 == "1") {
		cout << "Please enter the UnitPrice you want to update: ";
		string price;
		double p = 0;
		while (true) {
			bool judge = false;
			getline(cin, price);
			if (!Judge_One_Decimal(price)) {
				cout << "You need the exact price to one decimal or prices that are not allowed!" << endl << "Please re-enter:";
				judge = true;
			}
			if (!judge) {
				stringstream ss;
				ss << price;
				while (ss >> price) {
					p = convert<double>(price);
				}
				if (p <= 0) {
					cout << "prices that are not allowed!" << endl << "Please re-enter:";
					judge = true;
				}
			}
			if (!judge)
				break;
		}
		cout << "Verify the modified information is correct!" << endl;
		cout << endl << endl;
		cout << "commodityID:" << CO[i].commodityID << endl <<
			"commodityName:" << CO[i].commodityName << endl <<
			"price:" << fixed << setprecision(1) << p << endl <<
			"description:" << CO[i].description << endl;
		cout << endl << endl;
		cout << "Confirm to change?(y/n)";
		string option;
		while (true) {
			getline(cin, option);
			if (option == "y") {
				cout << "Update successfully!" << endl << endl << endl;
				string st0 = "UPDATE commodity SET price = " +
					price + " WHERE commodityID = " + st1;
				SQL S;
				S.UPDATE(st0);
				break;
			}
			else if (option == "n") {
				cout << "Cancel update!" << endl << endl << endl;
				break;
			}
			else {
				cout << "Illegal Input!" << endl << "Please re-enter:" << endl;
			}
		}
	}
	else if (st2 == "2") {
		cout << "Please enter the Description you want to update:";
		string Des;
		while (true) {
			getline(cin, Des);
			int len = Des.length();
			if (len > 200) {
				cout << "Commodity Description are not allowed to be longer than 200 characters!" << endl << "Please re-enter:";
			}
			else break;
		}
		cout << "Verify the modified information is correct!" << endl;
		cout << endl << endl;
		cout << "commodityID:" << CO[i].commodityID << endl <<
			"commodityName:" << CO[i].commodityName << endl <<
			"price:" << CO[i].price << endl <<
			"description:" << Des << endl;
		cout << endl << endl;
		cout << "Confirm to change?(y/n)";
		string option;
		while (true) {
			getline(cin, option);
			if (option == "y") {
				cout << "Update successfully!" << endl << endl << endl;
				string st0 = "UPDATE commodity SET description = " +
					Des + " WHERE commodityID = " + st1;
				SQL S;
				S.UPDATE(st0);
				break;
			}
			else if (option == "n") {
				cout << "Cancel update!" << endl << endl << endl;
				break;
			}
			else {
				cout << "Illegal Input!" << endl << "Please re-enter:" << endl;
			}
		}
	}
	else {
		cout << "Illegal Input!Return to the menu!" << endl;
		return;
	}

}
void Sellers::Remove_Commodity(string a){
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
	string st1;
	cout << "Please enter the Commodity ID you want to remove:";
	getline(cin, st1);
	ifstream IFS;
	IFS.open("commodity.txt", ios::in);
	char ch1[200];
	IFS.getline(ch1, 200);
	int num1 = 0;
	commodity CO[100];
	bool judge1 = Get(IFS, CO[num1]);
	while (!IFS.eof()) {
		IFS.seekg(-1, ios::cur);
		num1++;
		judge1 = Get(IFS, CO[num1]);
	}
	IFS.close();
	int j = 0;
	for (; j <= num1; j++) {
		if (CO[j].commodityID == st1)
			break;
	}
	if (CO[j].sellerID != US[i].userID) {
		cout << "This is not your published commodity! Cannot remove it!" << endl;
		cout << endl << endl;
		return;
	}
	cout << "Confirm that you want to remove this commodity?" << endl;
	cout << endl << endl;
	cout << setiosflags(ios::left);
	cout << setw(14) << "commodityID" <<
		setw(18) << "commodityName" <<
		setw(8) << "price" <<
		setw(13) << "addedDate" <<
		setw(9) << "number" <<
		setw(11) << "sellerID" <<
		setw(8) << "state" << endl;
	cout << setw(14) << CO[j].commodityID <<
		setw(18) << CO[j].commodityName <<
		fixed << setprecision(1) <<
		setw(8) << CO[j].price  <<
		setw(13) << CO[j].addedDate <<
		setprecision(0) << setw(9) << CO[j].number
		<< setw(11) << CO[j].sellerID;
	if (CO[j].state == 1)
		cout << setw(8) << "onSale" << endl;
	else cout << setw(8) << "remove" << endl;
	cout << endl << endl;
	cout << "Your option(y/n):";
	string option;
	while (true) {
		getline(cin, option);
		if (option == "y") {
			cout << "Remove successfully!" << endl << endl << endl;
			string st0 = "UPDATE commodity SET state = remove WHERE commodityID = " + st1;
			SQL S;
			S.UPDATE(st0);
			break;
		}
		else if (option == "n") {
			cout << "Cancel remove!" << endl << endl << endl;
			break;
		}
		else {
			cout << "Illegal Input!" << endl << "Please re-enter:" << endl;
		}
	}
}
void Sellers::Check_Orders(string a) {
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
	S.SELECT(st, "Sellers", US[i].userID);
}