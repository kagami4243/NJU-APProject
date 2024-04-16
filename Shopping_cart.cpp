#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<sstream>
#include<ctime>
#include<iomanip>
#include<string>
#include<map>
#include"Buyers.h"
#include"SQL.h"
#include"Data.h"
#include"Judge.h"
#include"Shopping_cart.h"
using namespace std;

void Shopping_cart_Model(string a){
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
	Shopping_cart SH;
	string option;
	while (true) {
		SH.Menu();//shopping cart menu
		getline(cin, option);
		if (option == "1") {
			SH.view_shopping_cart(US[i].userID);//view shopping cart
		}
		else if (option == "2") {
			SH.move_into(US[i].userID);//move into shopping cart
		}
		else if (option == "3") {
			SH.remove(US[i].userID);//remove shopping cart
		}
		else if (option == "4") {
			SH.empty(US[i].userID);//empty shopping cart
		}
		else if (option == "5") {
			break;
		}
		else {
			cout << "Illegal input!Please re-enter!" << endl << endl << endl;
		}
		cout << endl << endl;
	}
}
void Shopping_cart::Menu() {
	cout << "======================================================================================================================" << endl;
	cout << "1.View shopping cart 2.Move into shopping cart 3.Remove shopping cart 4.Empty shopping cart 5.Return to the main menu " << endl;
	cout << "======================================================================================================================" << endl << endl << endl;
	cout << "Input operation:";
}
void Shopping_cart::view_shopping_cart(string a) {
	ifstream IFS;
	IFS.open("shopping cart.txt", ios::in);
	if (!IFS.is_open()) {
		cout << "can't open the file";
		exit(-1);
	}
	cout << endl << endl;
	//get the first line
	char ch[200];
	IFS.getline(ch, 200);
	string st[9];
	stringstream ss;
	string st0;
	ss << ch;
	while (ss >> ch)
		st0 = convert<string>(ch);
	for (int i = 0, j = 0; i < st0.length(); i++) {
		if (st0[i] == ',') {
			j++;
			continue;
		}
		st[j] += st0[i];
	}
	int shopping_cart_number = 0;
	//cout the details
	int num = 0;
	shopping_cart SH[100];
	bool judge = Get(IFS, SH[num]);
	while (!IFS.eof()) {
		int j = IFS.get();
		if (j != -1)
		{
			//IFS.seekg(-1, ios::cur);
			num++;
			judge = Get(IFS, SH[num]);
		}
	}
	IFS.close();
	for (int i = 1; i <= num; i++)
		SH[i].commodityID = "M" + SH[i].commodityID;
	for (int i = 0; i <= num; i++) {
		if (a == SH[i].buyerID) {
			shopping_cart_number++;
			if (shopping_cart_number == 1) {
				cout << setiosflags(ios::left);
				cout << setw(14) << st[0] << setw(18) << st[1] <<
					setw(8) << st[2] << setw(9) << st[3] <<
					setw(11) << st[5] << setw(13) << st[6] <<
					setw(8) << st[7] << endl;
			}
			cout << setiosflags(ios::left);
			cout << setw(14) << SH[i].commodityID <<
				setw(18) << SH[i].commodityName <<
				setw(8) << SH[i].price << setw(9) <<
				SH[i].number << setw(11) << SH[i].sellerID <<
				setw(13) << SH[i].addedDate;
			if (SH[i].state == 1)
				cout << setw(9) << "onSale" << endl;
			else
				cout << setw(9) << "remove" << endl;
		}
	}
	if (shopping_cart_number == 0) {
		cout << "-----------------There is nothing in your shopping cart !-------------------" << endl;
	}
}
void Shopping_cart::move_into(string a) {
	ifstream IFS;
	string st1;
	cout << "Please enter the Commodity ID you want move into the shopping cart :";
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
		return;
	}
	if (CO[j].sellerID == a)
	{
		cout << "Unable to purchase your own commodities!" << endl;
		return;
	}
	if (CO[j].state == 0)
	{
		cout << "Could not find the item you want!" << endl;
		return;
	}
	string st2;
	int n = 0;
	cout << "Please enter the number you want :";
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
	cout << "Successfully !" << endl;
	ifstream ifs;
	ifs.open("shopping cart.txt", ios::in);
	if (!ifs.is_open()) {
		cout << "can't open the file";
		exit(-1);
	}
	char cha1[200];
	ifs.getline(cha1, 200);
	if (ifs.eof()) {
		ifs.close();
		ofstream ofs;
		ofs.open("shopping cart.txt", ios::app);
		if (!ofs.is_open()) {
			cout << "can't open the file";
			exit(-1);
		}
		ofs << endl << CO[j].commodityID << "," <<
			CO[j].commodityName << "," << CO[j].price << ","
			<< n << "," << CO[j].description << "," <<
			CO[j].sellerID << "," << CO[j].addedDate
			<< ",";
		if (CO[j].state == 1) {
			ofs << "onSale" << "," << a << endl;
		}
		else
			ofs << "remove" << "," << a << endl;
	}
	else {
		ifs.close();
		char cha5[200];
		ifstream IFS1;
		IFS1.open("shopping cart.txt", ios::in);
		if (!IFS1.is_open()) {
			cout << "can't open the file";
			exit(-1);
		}
		IFS1.getline(cha5, 200);
		int numb1 = 0;
		shopping_cart SH1[100];
		bool judge5 = Get(IFS1, SH1[numb1]);
		while (!IFS1.eof()) {
			int j = IFS1.get();
			if (j != -1)
			{
				numb1++;
				judge5 = Get(IFS1, SH1[numb1]);
			}
		}
		IFS.close();
		for (int i = 1; i <= numb1; i++)
			SH1[i].commodityID = "M" + SH1[i].commodityID;
		bool find = false;
		for (int i = 0; i <= numb1; i++) {
			if (SH1[i].commodityID == st1 && SH1[i].buyerID == a) {
				SH1[i].number += n;
				find = true;
			}
		}
		if (find) {
			ofstream ofs;
			ofs.open("shopping cart.txt", ios::out);
			ofs << "commodityID,commodityName,price,number,description,sellerID,addedDate,state,buyerID" << endl;
			ofs.close();
			for (int i = 0; i <= numb1; i++) {
				ofs.open("shopping cart.txt", ios::app);
				ofs << SH1[i].commodityID << ',' <<
					SH1[i].commodityName << ',' <<
					SH1[i].price << ',' <<
					SH1[i].number << ',' <<
					SH1[i].description << ',' <<
					SH1[i].sellerID << ',' <<
					SH1[i].addedDate << ',';
				if (SH1[i].state == 1)
					ofs << "onSale" << ',';
				else ofs << "remove" << ',';
				ofs << SH1[i].buyerID << endl;
				ofs.close();
			}
			return;
		}
		ofstream ofs;
		ofs.open("shopping cart.txt", ios::app);
		if (!ofs.is_open()) {
			cout << "can't open the file";
			exit(-1);
		}
		ofs << CO[j].commodityID << "," <<
			CO[j].commodityName << "," << CO[j].price << ","
			<< n << "," << CO[j].description << "," <<
			CO[j].sellerID << "," << CO[j].addedDate
			<< ",";
		if (CO[j].state == 1) {
			ofs << "onSale" << "," << a << endl;
		}
		else
			ofs << "remove" << "," << a << endl;
	}
}
void Shopping_cart::remove(string a) {
	string st1;
	cout << "Please enter the Commodity ID you want remove the shopping cart :";
	getline(cin, st1);
	ifstream IFS1;
	IFS1.open("shopping cart.txt", ios::in);
	if (!IFS1.is_open()) {
		cout << "can't open the file";
		exit(-1);
	}
	char cha5[200];
	IFS1.getline(cha5, 200);
	int numb1 = 0;
	shopping_cart SH1[100];
	bool judge5 = Get(IFS1, SH1[numb1]);
	while (!IFS1.eof()) {
		int j = IFS1.get();
		if (j != -1)
		{
			numb1++;
			judge5 = Get(IFS1, SH1[numb1]);
		}
	}
	IFS1.close();
	for (int i = 1; i <= numb1; i++)
		SH1[i].commodityID = "M" + SH1[i].commodityID;
	int NUM = -1;
	for (int i = 0; i <= numb1; i++) {
		if (SH1[i].commodityID == st1 && SH1[i].buyerID == a)
			NUM = i;
	}
	if (NUM == -1) {
		cout << "Can't find the Commodity ID you want remove the shopping cart!" << endl;
		return;
	}
	ofstream ofs;
	ofs.open("shopping cart.txt", ios::out);
	ofs << "commodityID,commodityName,price,number,description,sellerID,addedDate,state,buyerID" << endl;
	ofs.close();
	for (int i = 0; i <NUM; i++) {
		ofs.open("shopping cart.txt", ios::app);
		ofs << SH1[i].commodityID << ',' <<
			SH1[i].commodityName << ',' <<
			SH1[i].price << ',' <<
			SH1[i].number << ',' <<
			SH1[i].description << ',' <<
			SH1[i].sellerID << ',' <<
			SH1[i].addedDate << ',';
		if (SH1[i].state == 1)
			ofs << "onSale" << ',';
		else ofs << "remove" << ',';
		ofs << SH1[i].buyerID << endl;
		ofs.close();
	}
	for (int i = NUM + 1; i <= numb1; i++) {
		ofs.open("shopping cart.txt", ios::app);
		ofs << SH1[i].commodityID << ',' <<
			SH1[i].commodityName << ',' <<
			SH1[i].price << ',' <<
			SH1[i].number << ',' <<
			SH1[i].description << ',' <<
			SH1[i].sellerID << ',' <<
			SH1[i].addedDate << ',';
		if (SH1[i].state == 1)
			ofs << "onSale" << ',';
		else ofs << "remove" << ',';
		ofs << SH1[i].buyerID << endl;
		ofs.close();
	}
	cout << "Successfully!" << endl;
}
void Shopping_cart::empty(string a) {
	ifstream IFS1;
	IFS1.open("shopping cart.txt", ios::in);
	if (!IFS1.is_open()) {
		cout << "can't open the file";
		exit(-1);
	}
	char cha5[200];
	IFS1.getline(cha5, 200);
	int numb1 = 0;
	shopping_cart SH[100];
	bool judge5 = Get(IFS1, SH[numb1]);
	while (!IFS1.eof()) {
		int j = IFS1.get();
		if (j != -1)
		{
			numb1++;
			judge5 = Get(IFS1, SH[numb1]);
		}
	}
	IFS1.close();
	for (int i = 1; i <= numb1; i++)
		SH[i].commodityID = "M" + SH[i].commodityID;
	for (int i = 0; i <= numb1; i++) {
		if (SH[i].state == 0) {
			cout << "There're commodities that you can't purchase in your shopping cart!" << endl;
			return;
		}
	}
	ifstream IFS;
	IFS.open("commodity.txt", ios::in);
	char ch[200];
	IFS.getline(ch, 200);
	int num = 0;
	commodity CO[100];
	bool judge = Get(IFS, CO[num]);
	while (!IFS.eof()) {
		int j = IFS.get();
		if (j != -1)
		{
			//IFS.seekg(-1, ios::cur);
			num++;
			judge = Get(IFS, CO[num]);
		}
	}
	IFS.close();
	for (int i = 1; i <= num; i++)
		CO[i].commodityID = "M0" + CO[i].commodityID;
	map<string, commodity> MAP;
	for (int i = 0; i <= num; i++) {
		MAP.insert(pair<string, commodity>(CO[i].commodityID, CO[i]));
	}
	ifstream ifs;
	ifs.open("user.txt", ios::in);
	char ch1[200];
	ifs.getline(ch1, 200);
	int num1 = 0;
	user US[100];
	bool judge1 = Get(ifs, US[num1]);
	while (!ifs.eof()) {
		int j = ifs.get();
		if (j != -1)
		{
			//IFS.seekg(-1, ios::cur);
			num1++;
			judge1 = Get(ifs, US[num1]);
		}
	}
	ifs.close();
	for (int i = 1; i <= num1; i++)
		US[i].userID = "U0" + US[i].userID;
	//cout << US[1].userID << endl;
	map<string, user> MAP_us;
	for (int i = 0; i <= num1; i++) {
		MAP_us.insert(pair<string, user>(US[i].userID, US[i]));
	}
	for (int i = 0; i <= numb1; i++) {
		auto iter = MAP.find(SH[i].commodityID);
		auto iter1 = MAP_us.find(SH[i].buyerID);
		if (iter != MAP.end()&& iter1 != MAP_us.end()) {
			if (iter->second.number < SH[i].number) {
				cout << "Insufficient number of commodity whose Commodity  ID is " + SH[i].commodityID << endl;
				return;
			}
			if (iter1->second.balance < SH[i].price * SH[i].number) {
				cout << "Insufficient balance!";
				return;
			}
			iter->second.number -= SH[i].number;
			iter1->second.balance -= SH[i].price * SH[i].number;
			if (iter->second.number == 0)
				iter->second.state = 0;
		}
	}
	cout << "Successfully!" << endl;
	//update commodity.txt
	ofstream ofs;
	ofs.open("commodity.txt", ios::out);
	ofs << "commodityID,commodityName,price,number,description,sellerID,addedDate,state" << endl;
	ofs.close();
	auto iter2 = MAP.begin();
	while (iter2 != MAP.end()) {
		ofs.open("commodity.txt", ios::app);
		ofs << iter2->second.commodityID << ',' <<
			iter2->second.commodityName << ',' <<
			iter2->second.price << ',' <<
			iter2->second.number << ',' <<
			iter2->second.description << ',' <<
			iter2->second.sellerID << ',' <<
			iter2->second.addedDate << ',';
		if (iter2->second.state == 1)
			ofs << "onSale" << endl;
		else ofs << "remove" << endl;
		iter2++;
		ofs.close();
	}
	//update user.txt
	ofstream ofs1;
	ofs1.open("user.txt", ios::out);
	ofs1 << "userID,username,password,phoneNumber,address,balance,userState" << endl;
	ofs1.close();
	auto iter3 = MAP_us.begin();
	while (iter3 != MAP_us.end()) {
		ofs1.open("user.txt", ios::app);
		ofs1 << iter3->second.userID << ',' <<
			iter3->second.username << ',' <<
			iter3->second.password << ',' <<
			iter3->second.phoneNumber << ',' <<
			iter3->second.address << ',' <<
			iter3->second.balance << ',';
		if (iter3->second.userState == 1)
			ofs1 << "active" << endl;
		else ofs1 << "inactive" << endl;
		iter3++;
		ofs1.close();
	}
	//update shopping cart.txt
	int remove_num = 0;
	for (int i = 0; i <= numb1; i++) {
		if (SH[i].buyerID == a)
			remove_num++;
	}
	if (num1 == remove_num) {
		ofstream OFS;
		OFS.open("shopping cart.txt", ios::out);
		OFS << "commodityID,commodityName,price,number,description,sellerID,addedDate,state,buyerID";
		OFS.close();
		return;
	}
	ofstream OFS;
	OFS.open("shopping cart.txt", ios::out);
	OFS << "commodityID,commodityName,price,number,description,sellerID,addedDate,state,buyerID" << endl;
	OFS.close();
	for (int i = 0; i <= numb1; i++) {
		if (SH[i].buyerID != a) {
			OFS.open("shopping cart.txt", ios::app);
			OFS << SH[i].commodityID << ',' <<
				SH[i].commodityName << ',' <<
				SH[i].price << ',' <<
				SH[i].number << ',' <<
				SH[i].description << ',' <<
				SH[i].sellerID << ',' <<
				SH[i].addedDate << ',';
			if (SH[i].state == 1)
				ofs << "onSale" << ',';
			else ofs << "remove" << ',';
			OFS << SH[i].buyerID << endl;
			OFS.close();
		}
	}
	//update order.txt
	time_t timep;
	struct tm* p;
	time(&timep);
	p = localtime(&timep);
	for (int i = 0; i <= numb1; i++) {
		if (SH[i].buyerID == a) {
			ifstream ifstr;
			ifstr.open("order.txt", ios::in);
			if (!ifstr.is_open()) {
				cout << "can't open the file";
				exit(-1);
			}
			char cha100[200];
			ifstr.getline(cha100, 200);
			if (ifstr.eof()) {
				ifstr.close();
				OFS.open("order.txt", ios::app);
				if (!OFS.is_open()) {
					cout << "can't open the file";
					exit(-1);
				}
				OFS << endl << "T001" << ',' <<
					SH[i].commodityID << ',' <<
					SH[i].price << ',' <<
					SH[i].number << ',' <<
					p->tm_year + 1900 << "-" <<
					setw(2) << setfill('0') << p->tm_mon << "-" <<
					setw(2) << setfill('0') << p->tm_mday << ',' <<
					SH[i].sellerID << ',' <<
					SH[i].buyerID << endl;
				OFS.close();
			}
			else {
				int numBER = 0;
				order OR[100];
				bool JUDGE = Get(ifstr, OR[numBER]);
				while (!ifstr.eof()) {
					int j = ifstr.get();
					if (j != -1)
					{
						//ifstr.seekg(-1, ios::cur);
						numBER++;
						JUDGE = Get(ifstr, OR[numBER]);
					}
				}
				ifstr.close();
				int now_num = 1000 + numBER + 2;
				string num;
				stringstream ss;
				ss << now_num;
				while (ss >> now_num) {
					num = convert<string>(now_num);
				}
				string new_num = num.substr(1, 3);
				OFS.open("order.txt", ios::app);
				OFS << "T" << new_num << ',' <<
					SH[i].commodityID << ',' <<
					SH[i].price << ',' <<
					SH[i].number << ',' <<
					p->tm_year + 1900 << "-" <<
					setw(2) << setfill('0') << p->tm_mon << "-" <<
					setw(2) << setfill('0') << p->tm_mday << ',' <<
					SH[i].sellerID << ',' <<
					SH[i].buyerID << endl;
				OFS.close();
			}
		}
	}
}
