#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"Information.h"
#include<fstream>
#include<iomanip>
#include<sstream>
#include"Calculator.h"
#include"SQL.h"
#include"Judge.h"
#include"Data.h"
using namespace std;
void Infor_Mana(string a) {
	ifstream ifs;
	ifs.open("user.txt", ios::in);
	char ch[200];
	ifs.getline(ch, 200);
	int num = 0;
	user US[100];
	bool judge = Get(ifs, US[num]);
	while (!ifs.eof()) {
		ifs.seekg(-1, ios::cur);
		num++;
		judge = Get(ifs, US[num]);
	}
	ifs.close();
	int i = 0;
	for (; i <= num; i++) {
		if (US[i].username == a)
			break;
	}
	Information iNFOR;
	string option;
	while (true) {
		iNFOR.Menu(); //Personal information menu
		getline(cin, option);
		if (option == "1") {
			iNFOR.Check(US[i].userID);//View personal information
		}
		else if (option == "2") {
			iNFOR.Modify(US[i].userID);//update personal information
		}
		else if (option == "3") {
			iNFOR.reCharge(US[i].userID);//charge
		}
		else if (option == "4") {
			return;
		}
		else {
			cout << "Illegal input!Please re-enter!" << endl << endl << endl;
		}
	}
}
void Information::Menu() {
	cout << "===============================================================================================" << endl;
	cout << "1.View Personal Information 2.Update Personal Information 3.Recharge 4.Return to the main menu" << endl;
	cout << "===============================================================================================" << endl << endl << endl;
	cout << "Input operator:";
}
void Information::Check(string a) {
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
		if (US[i].userID == a)
			break;
	}
	string ST = GET_EXPRESSION(a);
	Calculate CA;
	string Balance = CA.calculate(ST);
	cout << endl << endl;
	cout << "username:" << US[i].username << endl <<
		"phonenumber:" << US[i].phoneNumber << endl <<
		"address:" << US[i].address << endl <<
		"balance:" << US[i].balance << endl;
	cout << endl << endl;
}
void Information::Modify(string a) {
	string option;
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
	map<string, user> name_US;
	map<string, user> ID_US;
	for (int i = 0; i <= num; i++) {
		name_US.insert(pair<string, user>(US[i].username, US[i]));
		ID_US.insert(pair<string, user>(US[i].userID, US[i]));
	}
	string new_Name, new_Phonenumber, new_Address, new_password;
	cout << "Select the modified properties(1.User Name 2.PhoneNumber 3.Address 4.Password):";
	while (true) {
		getline(cin, option);
		if (option == "1") {
			cout << "Please enter the modified User Name:";
			while (true) {
				getline(cin, new_Name);
				int len = new_Name.length();
				auto iter = name_US.find(new_Name);
				if (iter != name_US.end()) {
					cout << "The user name has already existed!" << endl << "Please re-enter:";
				}
				else if (len > 10) {
					cout << "User Name are not allowed to be longer than 10 characters!" << endl << "Please re-enter:";
				}
				else if (!Judge_English(new_Name)) {
					cout << "Contains illegal characters! User Name are allowed to only contains letters!" << endl << "Please re-enter:";
				}
				else if (new_Name == "")
					cout << "Contains illegal characters! User Name are allowed to only contains letters!" << endl << "Please re-enter:";
				else break;
			}
			cout << "Update successfully!" << endl;
			cout << endl << endl;
			auto iter = ID_US.find(a);
			if (iter != ID_US.end()) {
				iter->second.username = new_Name;
			}
			ofstream ofs;
			ofs.open("user.txt", ios::out);
			ofs << "userID,username,password,phoneNumber,address,balance,userState" << endl;
			ofs.close();
			auto iter2 = ID_US.begin();
			while (iter2 != ID_US.end()) {
				ofs.open("user.txt", ios::app);
				ofs << iter2->second.userID << ',' <<
					iter2->second.username << ',' <<
					iter2->second.password << ',' <<
					iter2->second.phoneNumber << ',' <<
					iter2->second.address << ',' <<
					iter2->second.balance << ',';
				if (iter2->second.userState == 1)
					ofs << "active" << endl;
				else ofs << "inactive" << endl;
				iter2++;
				ofs.close();
			}
			break;
		}
		else if (option == "2") {
			cout << "Please enter the modified TelephoneNumber:";
			while (true) {
				getline(cin, new_Phonenumber);
				int P_number_len = new_Phonenumber.length();
				if (P_number_len > 20) {
					cout << "TelephoneNumber are not allowed to be longer than 20 characters!" << endl << "Please re-enter:";
				}
				else if (!Judge_Number(new_Phonenumber)) {
					cout << "Contains illegal characters! TelephoneNumber are allowed to only contains numbers!" << endl << "Please re-enter:";
				}
				else if (new_Phonenumber == "")
					cout << "Contains illegal characters! TelephoneNumber are allowed to only contains numbers!" << endl << "Please re-enter:";
				else break;
			}
			cout << "Update successfully!" << endl;
			cout << endl << endl;
			auto iter = ID_US.find(a);
			if (iter != ID_US.end()) {
				iter->second.phoneNumber = new_Phonenumber;
			}
			ofstream ofs;
			ofs.open("user.txt", ios::out);
			ofs << "userID,username,password,phoneNumber,address,balance,userState" << endl;
			ofs.close();
			auto iter2 = ID_US.begin();
			while (iter2 != ID_US.end()) {
				ofs.open("user.txt", ios::app);
				ofs << iter2->second.userID << ',' <<
					iter2->second.username << ',' <<
					iter2->second.password << ',' <<
					iter2->second.phoneNumber << ',' <<
					iter2->second.address << ',' <<
					iter2->second.balance << ',';
				if (iter2->second.userState == 1)
					ofs << "active" << endl;
				else ofs << "inactive" << endl;
				iter2++;
				ofs.close();
			}
			break;
		}
		else if (option == "3") {
			cout << "Please enter the modified Address:";
			while (true) {
				getline(cin, new_Address);
				int address_len = new_Address.length();
				if (address_len > 40) {
					cout << "Address are not allowed to be longer than 40 characters!" << endl << "Please re-enter:";
				}
				else if (!Judge_English(new_Address)) {
					cout << "Contains illegal characters! Address are allowed to only contains English letters!" << endl << "Please re-enter:";
				}
				else if (new_Address == "")
					cout << "Contains illegal characters! Address are allowed to only contains English letters!" << endl << "Please re-enter:";
				else break;
			}
			cout << "Update successfully!" << endl;
			cout << endl << endl;
			auto iter = ID_US.find(a);
			if (iter != ID_US.end()) {
				iter->second.address = new_Address;
			}
			ofstream ofs;
			ofs.open("user.txt", ios::out);
			ofs << "userID,username,password,phoneNumber,address,balance,userState" << endl;
			ofs.close();
			auto iter2 = ID_US.begin();
			while (iter2 != ID_US.end()) {
				ofs.open("user.txt", ios::app);
				ofs << iter2->second.userID << ',' <<
					iter2->second.username << ',' <<
					iter2->second.password << ',' <<
					iter2->second.phoneNumber << ',' <<
					iter2->second.address << ',' <<
					iter2->second.balance << ',';
				if (iter2->second.userState == 1)
					ofs << "active" << endl;
				else ofs << "inactive" << endl;
				iter2++;
				ofs.close();
			}
			break;
		}
		else if (option == "4") {
			cout << "Please enter the modified Password:";
			while (true) {
				getline(cin, new_password);
				int password_len = new_password.length();
				if (password_len > 20) {
					cout << "Password are not allowed to be longer than 20 characters!" << endl << "Please re-enter:";
				}
				else if (!Judge_English_small_And_Number(new_password)) {
					cout << "Contains illegal characters! Password are allowed to only contains lower English letters and numbers!" << endl << "Please re-enter:";
				}
				else if (new_password == "")
					cout << "Contains illegal characters! Password are allowed to only contains lower English letters and numbers!" << endl << "Please re-enter:";
				else break;
			}
			cout << "Update successfully!" << endl;
			cout << endl << endl;
			auto iter = ID_US.find(a);
			if (iter != ID_US.end()) {
				iter->second.password = new_password;
			}
			ofstream ofs;
			ofs.open("user.txt", ios::out);
			ofs << "userID,username,password,phoneNumber,address,balance,userState" << endl;
			ofs.close();
			auto iter2 = ID_US.begin();
			while (iter2 != ID_US.end()) {
				ofs.open("user.txt", ios::app);
				ofs << iter2->second.userID << ',' <<
					iter2->second.username << ',' <<
					iter2->second.password << ',' <<
					iter2->second.phoneNumber << ',' <<
					iter2->second.address << ',' <<
					iter2->second.balance << ',';
				if (iter2->second.userState == 1)
					ofs << "active" << endl;
				else ofs << "inactive" << endl;
				iter2++;
				ofs.close();
			}
			break;
		}
		else {
			cout << "Illegal Input!" << endl << "Please re-enter:";
		}
	}
}
void Information::reCharge(string a) {
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
	map<string, user> name_US;
	map<string, user> ID_US;
	for (int i = 0; i <= num; i++)
		ID_US.insert(pair<string, user>(US[i].userID, US[i]));
	cout << "Please enter the money you want to recharge:";
	string number;
	getline(cin, number);
	if (!Judge_One_Decimal(number)) {
		cout << "Illegal Input!Recharge amount must be a decimal number !" << endl;
		return;
	}
	else cout << "Recharge successfully!" << endl;
	cout << endl << endl;
	double NUMBER = 0;
	stringstream ss;
	ss << number;
	while (ss >> number)
		NUMBER = convert<double>(number);
	auto iter = ID_US.find(a);
	double new_balance = 0;
	if (iter != ID_US.end()) {
		new_balance = iter->second.balance + NUMBER;
	}
	iter->second.balance = new_balance;
	ofstream ofs;
	ofs.open("user.txt", ios::out);
	ofs << "userID,username,password,phoneNumber,address,balance,userState" << endl;
	ofs.close();
	auto iter2 = ID_US.begin();
	while (iter2 != ID_US.end()) {
		ofs.open("user.txt", ios::app);
		ofs << iter2->second.userID << ',' <<
			iter2->second.username << ',' <<
			iter2->second.password << ',' <<
			iter2->second.phoneNumber << ',' <<
			iter2->second.address << ',' <<
			iter2->second.balance << ',';
		if (iter2->second.userState == 1)
			ofs << "active" << endl;
		else ofs << "inactive" << endl;
		iter2++;
		ofs.close();
	}
	ofstream ofs1;
	ofs1.open("charge.txt", ios::app);
	time_t nowtime;
	struct tm* p;
	time(&nowtime);
	p = localtime(&nowtime);
	ofs1 << number << "," << p->tm_year + 1900 << "-" <<
		setw(2) << setfill('0') << p->tm_mon << "-" <<
		setw(2) << setfill('0') << p->tm_mday
		<<  "," << iter->second.userID << endl;
	ofs1.close();
}
string Information::GET_EXPRESSION(string a) {
	ifstream IFS;
	IFS.open("order.txt", ios::in);
	char ch[200];
	IFS.getline(ch, 200);
	int num = 0;
	order OR[100];
	bool judge = Get(IFS, OR[num]);
	while (!IFS.eof()) {
		int j = IFS.get();
		if (j != -1)
		{
			//IFS.seekg(-1, ios::cur);
			num++;
			judge = Get(IFS, OR[num]);
		}
	}
	IFS.close();
	for (int i = 1; i <= num; i++)
		OR[i].orderID = "T0" + OR[i].orderID;
	Expression EX[100];
	for (int i = 0; i < 100; i++) {
		EX[i].number = "";
		EX[i].price_number = 0;
		for (int j = 0; j < 100; j++)
			EX[i].price[j] = "";
	}
	int ex = 0;
	string CHARGE[100];
	int CHARGE_TIME = 0;
	//cout << "num = " << num << endl;
	for (int i = 0; i < num; i++) {
		//cout << "buyerID = " << OR[i].buyerID << endl;
		if (OR[i].buyerID == a) {
			stringstream ss;
			ss << OR[i].number;
			string NUMBER;
			while (ss >> OR[i].number)
				NUMBER = convert<string>(OR[i].number);
			int j = 0;
			bool judge = false;
			for (; j < ex; j++) {
				if (NUMBER == EX[j].number) {
					judge = true;
					stringstream ss1;
					ss1 << fixed << setprecision(1) << OR[i].unitPrice;
					string PRICE;
					while (ss1 >> OR[i].unitPrice)
						PRICE = convert<string>(OR[i].unitPrice);
					EX[j].price[EX[j].price_number] = "-" + PRICE;
					EX[j].price_number++;
				}
			}
			if (!judge) {
				EX[ex].number = NUMBER;
				ex++;
				stringstream ss1;
				ss1 << fixed << setprecision(1) << OR[i].unitPrice;
				string PRICE;
				while (ss1 >> OR[i].unitPrice)
					PRICE = convert<string>(OR[i].unitPrice);
				EX[j].price[EX[j].price_number] = "-" + PRICE;
				EX[j].price_number++;
			}
		}
		else if (OR[i].sellerID == a) {
			stringstream ss;
			ss << OR[i].number;
			string NUMBER;
			while (ss >> OR[i].number)
				NUMBER = convert<string>(OR[i].number);
			int j = 0;
			for (; j < ex; j++) {
				if (NUMBER == EX[j].number) {
					stringstream ss1;
					ss1 << fixed << setprecision(1) << OR[i].unitPrice;
					string PRICE;
					while (ss1 >> OR[i].unitPrice)
						PRICE = convert<string>(OR[i].unitPrice);
					EX[j].price[EX[j].price_number] = PRICE;
					EX[j].price_number++;
				}
			}
			bool judge1 = false;
			if (!judge1) {
				EX[ex].number = NUMBER;
				ex++;
				stringstream ss1;
				ss1 << fixed << setprecision(1) << OR[i].unitPrice;
				string PRICE;
				while (ss1 >> OR[i].unitPrice)
					PRICE = convert<string>(OR[i].unitPrice);
				EX[j].price[EX[j].price_number] = PRICE;
				EX[j].price_number++;
			}
		}
	}
	//cout << "ex = " << ex << endl;
	ifstream ifs;
	ifs.open("charge.txt", ios::in);
	char line[100];
	ifs.getline(line, 100);
	while (!ifs.eof()) {
		string st1 = "", st2 = "", st3 = "";
		ifs.getline(line, 100);
		if (ifs.eof())
			break;
		int i = 0;
		for (; line[i] != ','; i++) {
			st1 += line[i];
		}
		i++;
		for (; line[i] != ','; i++) {
			st2 += line[i];
		}
		i++;
		for (; line[i] != '\0' && line[i] != ','; i++) {
			st3 += line[i];
		}
		if (st3 == a) {
			CHARGE[CHARGE_TIME] = st1;
			CHARGE_TIME++;
		}
	}
	ifs.close();
	string NEED;
	for (int i = 0; i < CHARGE_TIME; i++) {
		if (i == 0)
			NEED += CHARGE[i];
		else NEED += "+" + CHARGE[i];
	}
	for (int i = 0; i < ex; i++) {
		if (NEED != "") {
			NEED += "+";
		}
		if (EX[i].price_number == 1) {
			if (EX[i].price[0][0] == '-')
				NEED += EX[i].number + "*" + "(" + EX[i].price[0] + ")";
			else NEED += EX[i].number + "*" + EX[i].price[0];
		}
		else {
			for (int j = 0; j < EX[i].price_number; j++) {
				NEED += EX[i].number + "*" + "(";
				if (EX[i].price[j][0] == '-') {
					NEED += "(" + EX[i].price[j] + ")";
					if (j != EX[i].price_number - 1)
						NEED += "+";
				}
				else {
					NEED += EX[i].price[j];
					if (j != EX[i].price_number - 1)
						NEED += "+";
				}
			}
			NEED += ")";
		}
	}
	//cout << NEED << endl;
	return NEED;
}
