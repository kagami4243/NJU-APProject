#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<map>
#include<fstream>
#include<sstream>
#include<iomanip>
#include"Data.h"
#include"Buyers.h"
#include"Sellers.h"
#include"Information.h"
#include"SQL.h"
#include"Users.h"
#include"Judge.h"
#include"Message.h"
using namespace std;
void User_Register() {
	ifstream ifs;
	ifs.open("user.txt", ios::in);
	char ch[200];
	ifs.getline(ch, 200);
	if (ifs.eof()) {
		ifs.close();
		string a, b, c, d;
		cout << "Please enter User Name:";
		while (true) {
			getline(cin, a);
			int len = a.length();
			if (len > 10) {
				cout << "User Name are not allowed to be longer than 10 characters!" << endl << "Please re-enter:";
			}
			else if (!Judge_English(a)) {
				cout << "Contains illegal characters! User Name are allowed to only contains letters!" << endl << "Please re-enter:";
			}
			else if (a == "")
				cout << "Contains illegal characters! User Name are allowed to only contains letters!" << endl << "Please re-enter:";
			else break;
		}
		cout << "Please enter Password:";
		while (true) {
			getline(cin, b);
			int password_len = b.length();
			if (password_len > 20) {
				cout << "Password are not allowed to be longer than 20 characters!" << endl << "Please re-enter:";
			}
			else if (!Judge_English_small_And_Number(b)) {
				cout << "Contains illegal characters! Password are allowed to only contains lower English letters and numbers!" << endl << "Please re-enter:";
			}
			else if (b == "")
				cout << "Contains illegal characters! Password are allowed to only contains lower English letters and numbers!" << endl << "Please re-enter:";
			else break;
		}
		cout << "Please enter TelephoneNumber:";
		while (true) {
			getline(cin, c);
			int P_number_len = c.length();
			if (P_number_len > 20) {
				cout << "TelephoneNumber are not allowed to be longer than 20 characters!" << endl << "Please re-enter:";
			}
			else if (!Judge_Number(c)) {
				cout << "Contains illegal characters! TelephoneNumber are allowed to only contains numbers!" << endl << "Please re-enter:";
			}
			else if (c == "")
				cout << "Contains illegal characters! TelephoneNumber are allowed to only contains numbers!" << endl << "Please re-enter:";
			else break;
		}
		cout << "Please enter Address:";
		while (true) {
			getline(cin, d);
			int address_len = d.length();
			if (address_len > 40) {
				cout << "Address are not allowed to be longer than 40 characters!" << endl << "Please re-enter:";
			}
			else if (!Judge_English(d)) {
				cout << "Contains illegal characters! Address are allowed to only contains English letters!" << endl << "Please re-enter:";
			}
			else if (d == "")
				cout << "Contains illegal characters! Address are allowed to only contains English letters!" << endl << "Please re-enter:";
			else break;
		}
		ofstream ofs;
		ofs.open("user.txt", ios::app);
		ofs << endl << "U001" << ',' << a << ',' << b << ',' << c << ','
			<< d << ',' << "0.0" << ',' << "active" << endl;
		cout << "-----Register Successfully-----" << endl << endl << endl;
	}
	else {
		int num = 0;
		user US[100];
		bool judge = Get(ifs, US[num]);
		while (judge) {
			num++;
			ifs.seekg(-1, ios::cur);
			judge = Get(ifs, US[num]);
		}
		ifs.close();
		map<string, string> userName;
		for (int i = 0; i <= num; i++)
			userName.insert(pair<string, string>(US[i].username, US[i].password));
		string a, b, c, d;
		cout << "Please enter User Name:";
		while (true) {
			getline(cin, a);
			int len = a.length();
			auto iter = userName.find(a);
			if (iter != userName.end()) {
				cout << "User Name has existed!" << endl << "Please re-enter:";
			}
			else if (len > 10) {
				cout << "User Name are not allowed to be longer than 10 characters!" << endl << "Please re-enter:";
			}
			else if (!Judge_English(a)) {
				cout << "Contains illegal characters! User Name are allowed to only contains letters!" << endl << "Please re-enter:";
			}
			else if (a == "")
				cout << "Contains illegal characters! User Name are allowed to only contains letters!" << endl << "Please re-enter:";
			else break;
		}
		cout << "Please enter Password:";
		while (true) {
			getline(cin, b);
			int password_len = b.length();
			if (password_len > 20) {
				cout << "Password are not allowed to be longer than 20 characters!" << endl << "Please re-enter:";
			}
			else if (!Judge_English_small_And_Number(b)) {
				cout << "Contains illegal characters! Password are allowed to only contains lower English letters and numbers!" << endl << "Please re-enter:";
			}
			else if (b == "")
				cout << "Contains illegal characters! Password are allowed to only contains lower English letters and numbers!" << endl << "Please re-enter:";
			else break;
		}
		cout << "Please enter TelephoneNumber:";
		while (true) {
			getline(cin, c);
			int P_number_len = c.length();
			if (P_number_len > 20) {
				cout << "TelephoneNumber are not allowed to be longer than 20 characters!" << endl << "Please re-enter:";
			}
			else if (!Judge_Number(c)) {
				cout << "Contains illegal characters! TelephoneNumber are allowed to only contains numbers!" << endl << "Please re-enter:";
			}
			else if (c == "")
				cout << "Contains illegal characters! TelephoneNumber are allowed to only contains numbers!" << endl << "Please re-enter:";
			else break;
		}
		cout << "Please enter Address:";
		while (true) {
			getline(cin, d);
			int address_len = d.length();
			if (address_len > 40) {
				cout << "Address are not allowed to be longer than 40 characters!" << endl << "Please re-enter:";
			}
			else if (!Judge_English(d)) {
				cout << "Contains illegal characters! Address are allowed to only contains English letters!" << endl << "Please re-enter:";
			}
			else if (d == "")
				cout << "Contains illegal characters! Address are allowed to only contains English letters!" << endl << "Please re-enter:";
			else break;
		}
		ofstream ofs;
		ofs.open("user.txt", ios::app);
		auto iter = userName.begin();
		stringstream ss;
		ss << setw(3) << setfill('0') << num + 2;
		string st;
		ss >> st;
		ofs << 'U' << st << ',' << a << ',' << b << ',' << c << ','
			<< d << ',' << "0.0" << ',' << "active" << endl;
		cout << "-----Register Successfully-----" << endl << endl << endl;
	}
	return;
}
void User_Model() {
	User US;
	string a, b;
	cout << "Please enter User Name:";
	getline(cin, a);
	cout << "Please enter Password:";
	getline(cin, b);
	bool judge=US.Login(a,b);
	if (judge)
		cout << "-----Login Successfully-----" << endl << endl << endl;
	else {
		cout << "------Incorrect user name or password------" << endl << endl << endl;
		return;
	}
	string option;
	while (true) {
		US.Menu();//uesr menu
		getline(cin, option);
		if (option == "1") {
			Buyers_Model(a);//Buyers_Model
		}
		else if (option == "2") {
			Sellers_Model(a);//Sellers_Model
		}
		else if (option == "3") {
			Infor_Mana(a);//Information Magager
		}
		else if (option == "4") {
			Message_Model(a);//Information Magager
		}
		else if (option == "5") {
			return;//Cancel Login
		}
		else {
			cout << "Illegal Input! Please re-enter:" << endl << endl << endl;
		}
	}
}
bool User::Login(string a, string b) {
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
	map<string, user> ID_PASSPORT;
	for (int i = 0; i <= num; i++)
		ID_PASSPORT.insert(pair<string, user>(US[i].username, US[i]));
	auto iter = ID_PASSPORT.find(a);
	if (iter != ID_PASSPORT.end()) {
		if (iter->second.userState == 0)
			return false;
		if (iter->second.password == b)
			return true;
		else return false;
	}
	else return false;
}
void User::Menu() {
	cout << "=============================================================================" << endl;
	cout << "1.I'm a buyer 2.I'm a seller 3.Personal information manager 4.Message 5.Exit " << endl;
	cout << "=============================================================================" << endl << endl << endl;
	cout << "Input operation:";
}

