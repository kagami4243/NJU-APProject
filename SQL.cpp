#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<cstring>
#include<map>
#include<sstream>
#include<iomanip>
#include<ctime>
#include"SQL.h"
#include"Data.h"
using namespace std;

void SQL::SELECT(string st, string st0) {
	Save_to_commands(st);
	if (st0 == "Administrator") {
		if (st.find(W) == string::npos) {
			//cout << -1 << endl;
			if (st.find("commodity") != -1)
				SELECT_ALL(st);
			else if (st.find("order") != -1)
				SELECT_ALL(st);
			else if (st.find("user") != -1)
				SELECT_ALL(st);
		}
		else SELECT_PART(st, "Administrator");
	}
	else if (st0 == "Buyers") {
		if (st.find(W) == string::npos) {
			if (st.find("commodity")) {
				string st0 = st + " WHERE state CONTAINS onSale";
				SELECT_PART(st0,"Buyers");
			}
			else if (st.find("order")) {
				string st0 = st + " WHERE buyerID CONTAINS";
			}
		}
		else SELECT_PART(st, "Buyers");
	}
}
void SQL::SELECT(string st, string st0, string a) {
	Save_to_commands(st);
	if (st0 == "Buyers") {
		if (st.find(W) == string::npos) {
			if (st.find("order")) {
				string st0 = st + " WHERE buyerID CONTAINS " + a;
				SELECT_PART(st0, "Buyers");
			}
		}
		//else SELECT_PART(st, "Buyers");
	}
	else if (st0 == "Sellers") {
		if (st.find(W) == string::npos) {
			if (st.find("commodity")) {
				string st0 = st + " WHERE sellerID CONTAINS " + a;
				SELECT_PART(st0, "Sellers");
			}
			else if (st.find("order")) {
				string st0 = st + " WHERE sellerID CONTAINS " + a;
				SELECT_PART(st0, "Sellers");
			}
		}
	}
}
void SQL::SELECT_ALL(string st) {
	if (st.find("commodity") != -1) {
		ifstream ifs;
		string st1[8];
		ifs.open("commodity.txt", ios::in);
		if (!ifs.is_open()) {
			cout << "can't open the file";
			exit(-1);
		}
		cout << endl << endl;
		Show_first(ifs, st1, "commodity", "Administrator");
		Show(ifs, "commodity", "Administrator");
		cout << endl << endl;
		ifs.close();
	}
	else if (st.find("order") != -1) {
		ifstream ifs;
		string st1[7];
		ifs.open("order.txt", ios::in);
		/*if (!ifs.is_open()) {
			cout << "can't open the file";
			exit(-1);
		}*/
		cout << endl << endl;
		Show_first(ifs, st1, "order", "Administrator");
		Show(ifs, "order", "Administrator");
		cout << endl << endl;
		ifs.close();
	}
	else if (st.find("user") != -1) {
		ifstream ifs;
		string st1[7];
		ifs.open("user.txt", ios::in);
		if (!ifs.is_open()) {
			cout << "can't open the file";
			exit(-1);
		}
		cout << endl << endl;
		Show_first(ifs, st1, "user", "Administrator");
		Show(ifs, "user", "Administrator");
		cout << endl << endl;
		ifs.close();
	}
}
void SQL::SELECT_PART(string st, string st0) {
	if (st0 == "Administrator") {
		if (st.find("commodity") != -1) {
			if (st.find("commodityName") != -1) {
				size_t i = st.find("CONTAINS");
				size_t j = i + 9;//the first position of character user enter
				string st1 = st.substr(j);//Interception of input characters
				ifstream ifs;
				ifs.open("commodity.txt", ios::in);
				if (!ifs.is_open()) {
					cout << "can't open the file";
					exit(-1);
				}
				Show(ifs, "commodity", "commodityName", st1, "Administrator");
			}
			else if (st.find("commodityID") != -1) {
				size_t i = st.find("CONTAINS");
				size_t j = i + 9;//the first position of character user enter
				string st1 = st.substr(j);//Interception of input characters
				ifstream ifs;
				ifs.open("commodity.txt", ios::in);
				if (!ifs.is_open()) {
					cout << "can't open the file";
					exit(-1);
				}
				Show(ifs, "commodity", "commodityID", st1, "Administrator");
			}
		}
		else if (st.find("user") != -1) {
			if (st.find("userID") != -1) {
				size_t i = st.find("CONTAINS");
				size_t j = i + 9;//the first position of character user enter
				string st1 = st.substr(j);//Interception of input characters
				ifstream ifs;
				ifs.open("user.txt", ios::in);
				if (!ifs.is_open()) {
					cout << "can't open the file";
					exit(-1);
				}
				Show(ifs, "user", "userID", st1, "Administrator");
			}
		}
	}
	else if (st0 == "Buyers") {
		if (st.find("commodity") != -1) {
			if (st.find("state") != -1) {
				size_t i = st.find("CONTAINS");
				size_t j = i + 9;//the first position of character user enter
				string st1 = st.substr(j);//Interception of input characters
				ifstream ifs;
				ifs.open("commodity.txt", ios::in);
				if (!ifs.is_open()) {
					cout << "can't open the file";
					exit(-1);
				}
				Show(ifs, "commodity", "state", st1, "Buyers");
			}
			else if (st.find("commodityName") != -1) {
				size_t i = st.find("CONTAINS");
				size_t j = i + 9;//the first position of character user enter
				string st1 = st.substr(j);//Interception of input characters
				ifstream ifs;
				ifs.open("commodity.txt", ios::in);
				if (!ifs.is_open()) {
					cout << "can't open the file";
					exit(-1);
				}
				Show(ifs, "commodity", "commodityName", st1, "Buyers");
			}
			else if (st.find("commodityID")) {
				size_t i = st.find("CONTAINS");
				size_t j = i + 9;//the first position of character user enter
				string st1 = st.substr(j);//Interception of input characters
				ifstream ifs;
				ifs.open("commodity.txt", ios::in);
				if (!ifs.is_open()) {
					cout << "can't open the file";
					exit(-1);
				}
				Show(ifs, "commodity", "commodityID", st1, "Buyers");
			}
		}
		else if (st.find("order")) {
			if (st.find("buyerID") != -1) {
				size_t i = st.find("CONTAINS");
				size_t j = i + 9;//the first position of character user enter
				string st1 = st.substr(j);//Interception of input characters
				ifstream ifs;
				ifs.open("order.txt", ios::in);
				if (!ifs.is_open()) {
					cout << "can't open the file";
					exit(-1);
				}
				Show(ifs, "order", "buyerID", st1, "Buyers");
			}
		}
	}
	else if (st0 == "Sellers") {
		if (st.find("commodity") != -1) {
			if (st.find("sellerID")!=-1) {
				size_t i = st.find("CONTAINS");
				size_t j = i + 9;//输入字符的第一个字符位置
				string st1 = st.substr(j);//截取输入字符
				ifstream ifs;
				ifs.open("commodity.txt", ios::in);
				if (!ifs.is_open()) {
					cout << "can't open the file";
					exit(-1);
				}
				Show(ifs, "commodity", "sellerID", st1, "Sellers");
			}
		}
		else if (st.find("order") != -1) {
			if (st.find("sellerID") != -1) {
				size_t i = st.find("CONTAINS");
				size_t j = i + 9;//the first position of character user enter
				string st1 = st.substr(j);//Interception of input characters
				ifstream ifs;
				ifs.open("order.txt", ios::in);
				if (!ifs.is_open()) {
					cout << "can't open the file";
					exit(-1);
				}
				Show(ifs, "order", "sellerID", st1, "Sellers");
			}
		}
	}
}
void Get(ifstream& IFS, string st0[], string st2) {
	if (st2 == "commodity") {
		char ch[200];
		int j = IFS.get();
		int i = 0;
		while (j != ',' && j != '\n' && !IFS.eof()) {
			ch[i] = j;
			//cout << ch[i] << endl;
			i++;
			j = IFS.get();
		}
		ch[i] = '\0';
		st0[0] = ch;
		//cout << ch << endl;
		j = IFS.get();
		i = 0;
		while (j != ',' && j != '\n' && !IFS.eof()) {
			ch[i] = j;
			//cout << ch[i] << endl;
			i++;
			j = IFS.get();
		}
		ch[i] = '\0';
		st0[1] = ch;
		//cout << ch << endl;
		j = IFS.get();
		i = 0;
		while (j != ',' && j != '\n' && !IFS.eof()) {
			ch[i] = j;
			//cout << ch1[i] << endl;
			i++;
			j = IFS.get();
		}
		ch[i] = '\0';
		st0[2] = ch;
		//cout << ch << endl;
		j = IFS.get();
		i = 0;
		while (j != ',' && j != '\n' && !IFS.eof()) {
			ch[i] = j;
			//cout << ch2[i] << endl;
			i++;
			j = IFS.get();
		}
		ch[i] = '\0';
		st0[3] = ch;
		//cout << ch << endl;
		j = IFS.get();
		i = 0;
		while (j != ',' && j != '\n' && !IFS.eof()) {
			ch[i] = j;
			//cout << ch[i] << endl;
			i++;
			j = IFS.get();
		}
		ch[i] = '\0';
		st0[4] = ch;
		//cout << ch << endl;
		//cout << CO.description<< endl;
		j = IFS.get();
		i = 0;
		while (j != ',' && j != '\n' && !IFS.eof()) {
			ch[i] = j;
			//cout << ch[i] << endl;
			i++;
			j = IFS.get();
		}
		ch[i] = '\0';
		st0[5] = ch;
		//cout << ch << endl;
		j = IFS.get();
		i = 0;
		while (j != ',' && j != '\n' && !IFS.eof()) {
			ch[i] = j;
			//cout << ch[i] << endl;
			i++;
			j = IFS.get();
		}
		ch[i] = '\0';
		st0[6] = ch;
		//cout << ch << endl;
		j = IFS.get();
		i = 0;
		while (j != ',' && j != '\n' && !IFS.eof()) {
			ch[i] = j;
			//cout << ch3[i] << endl;
			i++;
			j = IFS.get();
		}
		ch[i] = '\0';
		st0[7] = ch;
		//cout << ch << endl;
	}
	else if (st2 == "order") {
		char ch[200];
		int j = IFS.get();
		int i = 0;
		while (j != ',' && j != '\n' && !IFS.eof()) {
			ch[i] = j;
			//cout << ch[i] << endl;
			i++;
			j = IFS.get();
		}
		ch[i] = '\0';
		st0[0] = ch;
		//cout << ch << endl;
		j = IFS.get();
		i = 0;
		while (j != ',' && j != '\n' && !IFS.eof()) {
			ch[i] = j;
			//cout << ch[i] << endl;
			i++;
			j = IFS.get();
		}
		ch[i] = '\0';
		st0[1] = ch;
		//cout << ch << endl;
		j = IFS.get();
		i = 0;
		while (j != ',' && j != '\n' && !IFS.eof()) {
			ch[i] = j;
			//cout << ch1[i] << endl;
			i++;
			j = IFS.get();
		}
		ch[i] = '\0';
		st0[2] = ch;
		//cout << ch << endl;
		j = IFS.get();
		i = 0;
		while (j != ',' && j != '\n' && !IFS.eof()) {
			ch[i] = j;
			//cout << ch2[i] << endl;
			i++;
			j = IFS.get();
		}
		ch[i] = '\0';
		st0[3] = ch;
		//cout << ch << endl;
		j = IFS.get();
		i = 0;
		while (j != ',' && j != '\n' && !IFS.eof()) {
			ch[i] = j;
			//cout << ch[i] << endl;
			i++;
			j = IFS.get();
		}
		ch[i] = '\0';
		st0[4] = ch;
		//cout << ch << endl;
		//cout << CO.description<< endl;
		j = IFS.get();
		i = 0;
		while (j != ',' && j != '\n' && !IFS.eof()) {
			ch[i] = j;
			//cout << ch[i] << endl;
			i++;
			j = IFS.get();
		}
		ch[i] = '\0';
		st0[5] = ch;
		//cout << ch << endl;
		j = IFS.get();
		i = 0;
		while (j != ',' && j != '\n' && !IFS.eof()) {
			ch[i] = j;
			//cout << ch[i] << endl;
			i++;
			j = IFS.get();
		}
		ch[i] = '\0';
		st0[6] = ch;
	}
	else if (st2 == "user") {
	char ch[200];
	int j = IFS.get();
	int i = 0;
	while (j != ',' && j != '\n' && !IFS.eof()) {
		ch[i] = j;
		//cout << ch[i] << endl;
		i++;
		j = IFS.get();
	}
	ch[i] = '\0';
	st0[0] = ch;
	//cout << ch << endl;
	j = IFS.get();
	i = 0;
	while (j != ',' && j != '\n' && !IFS.eof()) {
		ch[i] = j;
		//cout << ch[i] << endl;
		i++;
		j = IFS.get();
	}
	ch[i] = '\0';
	st0[1] = ch;
	//cout << ch << endl;
	j = IFS.get();
	i = 0;
	while (j != ',' && j != '\n' && !IFS.eof()) {
		ch[i] = j;
		//cout << ch1[i] << endl;
		i++;
		j = IFS.get();
	}
	ch[i] = '\0';
	st0[2] = ch;
	//cout << ch << endl;
	j = IFS.get();
	i = 0;
	while (j != ',' && j != '\n' && !IFS.eof()) {
		ch[i] = j;
		//cout << ch2[i] << endl;
		i++;
		j = IFS.get();
	}
	ch[i] = '\0';
	st0[3] = ch;
	//cout << ch << endl;
	j = IFS.get();
	i = 0;
	while (j != ',' && j != '\n' && !IFS.eof()) {
		ch[i] = j;
		//cout << ch[i] << endl;
		i++;
		j = IFS.get();
	}
	ch[i] = '\0';
	st0[4] = ch;
	//cout << ch << endl;
	//cout << CO.description<< endl;
	j = IFS.get();
	i = 0;
	while (j != ',' && j != '\n' && !IFS.eof()) {
		ch[i] = j;
		//cout << ch[i] << endl;
		i++;
		j = IFS.get();
	}
	ch[i] = '\0';
	st0[5] = ch;
	//cout << ch << endl;
	j = IFS.get();
	i = 0;
	while (j != ',' && j != '\n' && !IFS.eof()) {
		ch[i] = j;
		//cout << ch[i] << endl;
		i++;
		j = IFS.get();
	}
	ch[i] = '\0';
	st0[6] = ch;
	}
}
bool Get(ifstream& IFS, commodity& CO) {
	char ch[200];
	int j = IFS.get();
	int i = 0;
	while (j != ',' && j != '\n' && !IFS.eof()) {
		ch[i] = j;
		//cout << ch[i] << endl;
		i++;
		j = IFS.get();
	}
	ch[i] = '\0';
	CO.commodityID.append(ch);
	//cout << CO.commodityID << endl;
	j = IFS.get();
	i = 0;
	while (j != ',' && j != '\n' && !IFS.eof()) {
		ch[i] = j;
		//cout << ch[i] << endl;
		i++;
		j = IFS.get();
	}
	ch[i] = '\0';
	CO.commodityName.append(ch);
	//cout << CO.commodityName << endl;
	j = IFS.get();
	i = 0;
	char ch1[20] = "";
	while (j != ',' && j != '\n' && !IFS.eof()) {
		ch1[i] = j;
		//cout << ch1[i] << endl;
		i++;
		j = IFS.get();
	}
	ch1[i] = '\0';
	stringstream ss1;
	ss1 << ch1;
	while (ss1 >> ch1) {
		double val = convert<double>(ch1);
		CO.price = val;
	}
	//cout << CO.price << endl;
	j = IFS.get();
	i = 0;
	char ch2[20] = "";
	while (j != ',' && j != '\n' && !IFS.eof()) {
		ch2[i] = j;
		//cout << ch2[i] << endl;
		i++;
		j = IFS.get();
	}
	ch2[i] = '\0';
	stringstream ss2;
	ss2 << ch2;
	while (ss2 >> ch2) {
		int val1 = convert<int>(ch2);
		CO.number = val1;
	}
	//cout << CO.number<< endl;
	j = IFS.get();
	i = 0;
	while (j != ',' && j != '\n' && !IFS.eof()) {
		ch[i] = j;
		//cout << ch[i] << endl;
		i++;
		j = IFS.get();
	}
	ch[i] = '\0';
	CO.description.append(ch);
	//cout << CO.description<< endl;
	j = IFS.get();
	i = 0;
	while (j != ',' && j != '\n' && j != EOF) {
		ch[i] = j;
		//cout << ch[i] << endl;
		i++;
		j = IFS.get();
	}
	ch[i] = '\0';
	CO.sellerID.append(ch);
	//cout << CO.sellerID << endl;
	j = IFS.get();
	i = 0;
	while (j != ',' && j != '\n' && j != EOF) {
		ch[i] = j;
		//cout << ch[i] << endl;
		i++;
		j = IFS.get();
	}
	ch[i] = '\0';
	CO.addedDate.append(ch);
	//cout << CO.addedDate << endl;
	j = IFS.get();
	i = 0;
	char ch3[100] = "";
	while (j != ',' && j != '\n' && j != EOF) {
		ch3[i] = j;
		//cout << ch3[i] << endl;
		i++;
		j = IFS.get();
	}
	ch3[i] = '\0';
	int s = strcmp(ch3, "onSale");
	//cout << "s=:" << s << endl;
	if (s == 0)
		CO.state = 1;
	else CO.state = 0;
	//cout << CO.state << endl;
	/*if (CO.state == 1)
		cout << "onSale" << endl;
	else
		cout << "Remove" << endl;*/
	if (IFS.eof())
		return false;
	else if (IFS.get() == EOF)
		return false;
	else {
		return true;
	}
}
bool Get(ifstream& IFS, order& OR) {
	char ch[200];
	IFS.getline(ch, 200);
	string st[7];
	string st0(ch);
	//cout << st0 << endl;
	for (int i = 0, j = 0; i < st0.length(); i++) {
		if (st0[i] == ',') {
			j++;
			continue;
		}
		st[j] += st0[i];
	}
	OR.orderID.append(st[0]);
	//cout << OR.orderID << endl;
	OR.commodityID.append(st[1]);
	//cout << OR.commodityID << endl;
	stringstream ss1;
	ss1 << st[2];
	while (ss1 >> st[2]) {
		double val = convert<double>(st[2]);
		OR.unitPrice = val;
	}
	//cout << OR.unitPrice << endl;
	stringstream ss2;
	ss2 << st[3];
	while (ss2 >> st[3]) {
		int val1 = convert<int>(st[3]);
		OR.number = val1;
	}
	//cout << OR.number << endl;
	OR.date.append(st[4]);
	//cout << OR.date << endl;
	OR.sellerID.append(st[5]);
	//cout << OR.sellerID << endl;
	OR.buyerID.append(st[6]);
	//cout << OR.buyerID << endl;
	//if (IFS.eof())
	//	return false;
	//int j = IFS.get();
	//if (IFS.eof())
	//	return false;
	//else {
	//	//IFS.seekg(-1, ios::cur);
	//	return true;
	//}
	return true;
}
bool Get(ifstream& IFS, user& US) {
	char ch[200];
	int j = IFS.get();
	//cout << j << endl;
	int i = 0;
	while (j != ',' && j != '\n' && !IFS.eof()) {
		ch[i] = j;
		//cout << ch[i] << endl;
		i++;
		j = IFS.get();
	}
	ch[i] = '\0';
	US.userID.append(ch);
	//cout << OR.orderID << endl;
	j = IFS.get();
	i = 0;
	while (j != ',' && j != '\n' && !IFS.eof()) {
		ch[i] = j;
		//cout << ch[i] << endl;
		i++;
		j = IFS.get();
	}
	ch[i] = '\0';
	US.username.append(ch);
	//cout << OR.commodityID << endl;
	j = IFS.get();
	i = 0;
	while (j != ',' && j != '\n' && !IFS.eof()) {
		ch[i] = j;
		//cout << ch[i] << endl;
		i++;
		j = IFS.get();
	}
	ch[i] = '\0';
	US.password.append(ch);
	//cout << OR.date << endl;
	j = IFS.get();
	i = 0;
	while (j != ',' && j != '\n' && !IFS.eof()) {
		ch[i] = j;
		//cout << ch[i] << endl;
		i++;
		j = IFS.get();
	}
	ch[i] = '\0';
	US.phoneNumber.append(ch);
	//cout << OR.date << endl;
	j = IFS.get();
	i = 0;
	while (j != ',' && j != '\n' && !IFS.eof()) {
		ch[i] = j;
		//cout << ch[i] << endl;
		i++;
		j = IFS.get();
	}
	ch[i] = '\0';
	US.address.append(ch);
	//cout << OR.date << endl;
	j = IFS.get();
	i = 0;
	char ch1[20] = "";
	while (j != ',' && j != '\n' && !IFS.eof()) {
		ch1[i] = j;
		//cout << ch1[i] << endl;
		i++;
		j = IFS.get();
	}
	ch1[i] = '\0';
	stringstream ss1;
	ss1 << ch1;
	while (ss1 >> ch1) {
		double val = convert<double>(ch1);
		US.balance = val;
	}
	//cout << OR.unitPrice << endl;
	j = IFS.get();
	i = 0;
	char ch3[100] = "";
	while (j != ',' && j != '\n' && j != EOF) {
		ch3[i] = j;
		//cout << ch3[i] << endl;
		i++;
		j = IFS.get();
	}
	ch3[i] = '\0';
	int s = strcmp(ch3, "active");
	//cout << "s=:" << s << endl;
	if (s == 0)
		US.userState = 1;
	else US.userState = 0;
	//cout << CO.state << endl;
	/*if (CO.state == 1)
		cout << "onSale" << endl;
	else
		cout << "Remove" << endl;*/
	if (IFS.eof())
		return false;
	else if (IFS.get() == EOF)
		return false;
	else {
		return true;
	}
}
bool Get(ifstream& IFS, shopping_cart& SH) {
	char ch[200];
	IFS.getline(ch, 200);
	string st[9];
	string st0(ch);
	for (int i = 0, j = 0; i < st0.length(); i++) {
		if (st0[i] == ',') {
			j++;
			continue;
		}
		st[j] += st0[i];
	}
	SH.commodityID.append(st[0]);
	SH.commodityName.append(st[1]);
	stringstream ss1;
	ss1 << st[2];
	while (ss1 >> st[2]) {
		double val = convert<double>(st[2]);
		SH.price = val;
	}
	stringstream ss2;
	ss2 << st[3];
	while (ss2 >> st[3]) {
		int val1 = convert<int>(st[3]);
		SH.number = val1;
	}
	SH.description.append(st[4]);
	SH.sellerID.append(st[5]);
	SH.addedDate.append(st[6]);
	if (st[7] == "onSale")
		SH.state = true;
	else SH.state = false;
	SH.buyerID.append(st[8]);
	return true;
}
bool Get(ifstream& IFS, message& ME) {
	char ch[200];
	IFS.getline(ch, 200);
	string st[4];
	string st0(ch);
	for (int i = 0, j = 0; i < st0.length(); i++) {
		if (st0[i] == ',') {
			j++;
			continue;
		}
		st[j] += st0[i];
	}
	ME.seller.append(st[0]);
	ME.receiver.append(st[1]);
	ME.date.append(st[2]);
	ME.content.append(st[3]);
	return true;
}
void SQL::Show_first(ifstream& IFS, string st[], string st1, string st0) {
	if (st0 == "Administrator") {
		if (st1 == "commodity") {
			Get(IFS, st, "commodity");
			cout << setiosflags(ios::left);
			cout << setw(14) << st[0] << setw(18) << st[1] <<
				setw(8) << st[2] << setw(9) << st[3] <<
				setw(11) << st[5] << setw(13) << st[6] <<
				setw(8) << st[7] << endl;
		}
		else if (st1 == "order") {
			Get(IFS, st, "order");
			cout << setiosflags(ios::left);
			cout << setw(10) << st[0] << setw(14) << st[1] <<
				setw(12) << st[2] << setw(9) << st[3] <<
				setw(13) << st[4] << setw(11) << st[5] <<
				setw(10) << st[6] << endl;
		}
		else if (st1 == "user") {
			Get(IFS, st, "user");
			cout << setiosflags(ios::left);
			cout << setw(9) << st[0] << setw(13) << st[1] <<
				setw(23) << st[3] << setw(43) << st[4] <<
				setw(10) << st[5] << setw(8) << st[6] << endl;
		}
	}
	else if (st0 == "Buyers") {
		if (st1 == "commodity") {
			Get(IFS, st, "commodity");
			cout << setiosflags(ios::left);
			cout << setw(14) << st[0] << setw(18)
				<< st[1] <<setw(8) << st[2] 
				<< setw(13) << st[6] <<
				setw(11) << st[5] << endl;
		}
		else if (st1 == "order") {
			Get(IFS, st, "order");
			cout << setiosflags(ios::left);
			cout << setw(10) << st[0] <<
				setw(14) << st[1] <<
				setw(12) << st[2] << setw(9) <<
				st[3] << setw(13) << st[4] <<
				setw(11) << st[5] << endl;
		}
	}
	else if (st0 == "Sellers") {
		if (st1 == "commodity") {
			Get(IFS, st, "commodity");
			cout << setiosflags(ios::left);
			cout << setw(14) << st[0] << setw(18) << st[1] <<
				setw(8) << st[2] << setw(9) << st[3] <<
				setw(13) << st[6] << setw(8) << st[7] << endl;
		}
		else if (st1 == "order") {
			Get(IFS, st, "order");
			cout << setiosflags(ios::left);
			cout << setw(10) << st[0] << setw(14) << st[1] <<
				setw(12) << st[2] << setw(9) << st[3] <<
				setw(13) << st[4] << setw(11) << st[6] << endl;
		}
	}
}
void SQL::Show(ifstream& IFS, string st, string st0) {
	if (st0 == "Administrator") {
		if (st == "commodity") {
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
			cout << setiosflags(ios::left);
			cout << setw(14) << CO[0].commodityID <<
				setw(18) << CO[0].commodityName <<
				setw(8) << CO[0].price << setw(9) <<
				CO[0].number << setw(11) << CO[0].sellerID <<
				setw(13) << CO[0].addedDate;
			if (CO[0].state == 1)
				cout << setw(9) << "onSale" << endl;
			else
				cout << setw(9) << "remove" << endl;
			for (int i = 1; i <= num; i++) {
				cout <<"M0"<< setw(12) << CO[i].commodityID <<
					setw(18) << CO[i].commodityName <<
					setw(8) << CO[i].price << setw(9) <<
					CO[i].number << setw(11) << CO[i].sellerID <<
					setw(13) << CO[i].addedDate;
				if (CO[i].state == 1)
					cout << setw(9) << "onSale" << endl;
				else
					cout << setw(9) << "remove" << endl;
			}
		}
		else if (st == "order") {
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
			cout << setiosflags(ios::left);
			cout << setw(10) << OR[0].orderID <<
				setw(14) << OR[0].commodityID <<
				setw(12) << OR[0].unitPrice << setw(9) <<
				OR[0].number << setw(13) << OR[0].date <<
				setw(11) << OR[0].sellerID << setw(10) <<
				OR[0].buyerID << endl;
			for (int i = 1; i <= num; i++) {
				cout << "T"<<setw(9) << OR[i].orderID <<
					setw(14) << OR[i].commodityID <<
					setw(12) << OR[i].unitPrice << setw(9) <<
					OR[i].number << setw(13) << OR[i].date <<
					setw(11) << OR[i].sellerID << setw(10) <<
					OR[i].buyerID << endl;
			}
		}
		else if (st == "user") {
			int num = 0;
			user US[100];
			bool judge = Get(IFS, US[num]);
			while (!IFS.eof()) {
				int j = IFS.get();
				if (j != -1)
				{
					//IFS.seekg(-1, ios::cur);
					num++;
					judge = Get(IFS, US[num]);
				}
			}
			IFS.close();
			cout << setiosflags(ios::left);
			for (int i = 0; i <= 0; i++) {
				cout << setw(9) << US[i].userID
					<< setw(13) << US[i].username
					<< setw(23) << US[i].phoneNumber
					<< setw(43) << US[i].address
					<< setw(10) << US[i].balance;
				if (US[i].userState == 1)
					cout << setw(12) << "active" << endl;
				else
					cout << setw(9) << "inactive" << endl;
			}
			for (int i = 1; i <= num; i++) {
				cout << "U0" << setw(7) << US[i].userID
					<< setw(13) << US[i].username
					<< setw(23) << US[i].phoneNumber
					<< setw(43) << US[i].address
					<< setw(10) << US[i].balance;
				if (US[i].userState == 1)
					cout << setw(12) << "active" << endl;
				else
					cout << setw(9) << "inactive" << endl;
			}
		}
	}
}
void SQL::Show(ifstream& IFS, string st1, string st2, string st3, string st0) {
	if (st0 == "Administrator") {
		if (st1 == "commodity") {
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
			if (st2 == "commodityName") {
				string st0[8];
				cout << setiosflags(ios::left);
				int judge = 0;
				for (int i = 0; i <= 0; i++) {
					if (CO[i].commodityName.find(st3) != -1) {
						judge++;
						if (judge == 1) {
							IFS.open("commodity.txt", ios::in);
							if (!IFS.is_open()) {
								cout << "can't open the file";
								exit(-1);
							}
							cout << endl << endl;
							Show_first(IFS, st0, "commodity", "Administrator");
							IFS.close();
						}
						cout << setw(14) << CO[i].commodityID <<
							setw(18) << CO[i].commodityName <<
							setw(8) << CO[i].price << setw(9) <<
							CO[i].number << setw(11) << CO[i].sellerID <<
							setw(13) << CO[i].addedDate;
						if (CO[i].state == 1)
							cout << setw(9) << "onSale" << endl;
						else
							cout << setw(9) << "remove" << endl;
					}
				}
				for (int i = 1; i <= num; i++) {
					if (CO[i].commodityName.find(st3) != -1) {
						judge++;
						if (judge == 1) {
							IFS.open("commodity.txt", ios::in);
							if (!IFS.is_open()) {
								cout << "can't open the file";
								exit(-1);
							}
							cout << endl << endl;
							Show_first(IFS, st0, "commodity", "Administrator");
							IFS.close();
						}
						cout << "M0" << setw(12) << CO[i].commodityID <<
							setw(18) << CO[i].commodityName <<
							setw(8) << CO[i].price << setw(9) <<
							CO[i].number << setw(11) << CO[i].sellerID <<
							setw(13) << CO[i].addedDate;
						if (CO[i].state == 1)
							cout << setw(9) << "onSale" << endl;
						else
							cout << setw(9) << "remove" << endl;
					}
				}
				cout << endl << endl;
				if (judge == 0)
				{
					cout << endl << endl;
					cout << "========================================================= " << endl;
					cout << "Can't find the commodities you want! Return to the menu!" << endl;
					cout << "========================================================= " << endl;
					cout << endl << endl;
				}
			}
			else if (st2 == "commodityID") {
				string st0[8];
				map<string, commodity> cI_c;
				for (int i = 0; i <= 0; i++) {
					cI_c.insert(pair<string, commodity>(CO[i].commodityID, CO[i]));
				}
				for (int i = 1; i <= num; i++) {
					CO[i].commodityID = "M0" + CO[i].commodityID;
					cI_c.insert(pair<string, commodity>(CO[i].commodityID, CO[i]));
				}
				cout << setiosflags(ios::left);
				auto iter = cI_c.find(st3);
				bool judge = false;
				while (iter != cI_c.end()) {
					IFS.open("commodity.txt", ios::in);
					if (!IFS.is_open()) {
						cout << "can't open the file";
						exit(-1);
					}
					cout << endl << endl;
					judge = true;
					if (judge)
						cout << "Are you sure want to remove the commodity?" << endl;
					Show_first(IFS, st0, "commodity", "Administrator");
					IFS.close();
					cout << setw(14) << iter->second.commodityID <<
						setw(18) << iter->second.commodityName <<
						setw(8) << iter->second.price << setw(9) <<
						iter->second.number << setw(11) << iter->second.sellerID <<
						setw(13) << iter->second.addedDate;
					if (iter->second.state == 1)
						cout << setw(8) << "onSale" << endl;
					else cout << setw(8) << "remove" << endl;
					cout << endl << endl;
					cI_c.erase(iter);
					iter = cI_c.find(st3);
				}
				if (judge) {
					cout << "Your option(y/n):";
					string option;
					getline(cin, option);
					if (option == "y") {
						string st4 = "UPDATE commodity SET state = remove WHERE commodityID = " + st3;
						SQL S;
						S.UPDATE(st4);
						cout << "Remove successfully!" << endl << endl << endl;
					}
					else if (option == "n")
						cout << "Cancel remove!" << endl << endl << endl;
					else
						cout << "Illegal Input! Return to the menu!" << endl << endl << endl;
				}
				if (!judge)
				{
					cout << endl << endl;
					cout << "==================================================================== " << endl;
					cout << "Can't find the Commodity ID you want to remove! Return to the menu!" << endl;
					cout << "==================================================================== " << endl;
					cout << endl << endl;
				}
			}
		}
		if (st1 == "user") {
			char ch[200];
			IFS.getline(ch, 200);
			int num = 0;
			user US[100];
			bool judge = Get(IFS, US[num]);
			while (!IFS.eof()) {
				int j = IFS.get();
				if (j != -1)
				{
					//IFS.seekg(-1, ios::cur);
					num++;
					judge = Get(IFS, US[num]);
				}
			}
			IFS.close();
			if (st2 == "userID") {
				string st0[7];
				map<string, user> ID_US;
				for (int i = 1; i <= num; i++) {
					US[i].userID = "U0" + US[i].userID;
				}
				for (int i = 0; i <= num; i++) {
					ID_US.insert(pair<string, user>(US[i].userID, US[i]));
				}
				cout << setiosflags(ios::left);
				auto iter = ID_US.find(st3);
				bool judge = false;
				while (iter != ID_US.end()) {
					IFS.open("user.txt", ios::in);
					if (!IFS.is_open()) {
						cout << "can't open the file";
						exit(-1);
					}
					cout << endl << endl;
					judge = true;
					if (judge)
						cout << "Are you sure want to ban the user?" << endl;
					Show_first(IFS, st0, "user", "Administrator");
					IFS.close();
					cout << setw(9) << iter->second.userID
						<< setw(13) << iter->second.username
						<< setw(23) << iter->second.phoneNumber
						<< setw(43) << iter->second.address
						<< setw(10) << iter->second.balance;
					if (iter->second.userState == 1)
						cout << setw(12) << "active" << endl;
					else
						cout << setw(9) << "inactive" << endl;
					ID_US.erase(iter);
					iter = ID_US.find(st3);
				}
				if (judge) {
					cout << "Your option(y/n):";
					string option;
					getline(cin, option);
					if (option == "y") {
						string st4 = "UPDATE commodity SET state = remove WHERE sellerID = " + st3;
						string st5 = "UPDATE user SET userState = inactive WHERE userID = " + st3;
						SQL S;
						S.UPDATE(st4);
						S.UPDATE(st5);
						cout << "Ban successfully!" << endl << endl << endl;
					}
					else if (option == "n")
						cout << "Cancel ban!" << endl << endl << endl;
					else
						cout << "Illegal Input! Return to the menu!" << endl << endl << endl;
				}
				if (!judge)
				{
					cout << endl << endl;
					cout << "============================================================ " << endl;
					cout << "Can't find the User ID you want to ban! Return to the menu!" << endl;
					cout << "============================================================ " << endl;
					cout << endl << endl;
				}
			}
		}
	}
	else if (st0 == "Buyers") {
		if (st1 == "commodity") {
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
			if (st2 == "state") {
				string st0[8];
				cout << setiosflags(ios::left);
				IFS.open("commodity.txt", ios::in);
				if (!IFS.is_open()) {
					cout << "can't open the file";
					exit(-1);
				}
				cout << endl << endl;
				Show_first(IFS, st0, "commodity", "Buyers");
				IFS.close();
				for (int i = 0; i <= 0; i++) {
					if (CO[i].state != 0) {
						cout << setw(14) << CO[i].commodityID <<
							setw(18) << CO[i].commodityName <<
							setw(8) << CO[i].price <<
							setw(13) << CO[i].addedDate <<
							setw(11) << CO[i].sellerID << endl;
					}
				}
				for (int i = 1; i <= num; i++) {
					if (CO[i].state != 0) {
						cout << "M0" << setw(12) << CO[i].commodityID <<
							setw(18) << CO[i].commodityName <<
							setw(8) << CO[i].price <<
							setw(13) << CO[i].addedDate <<
							setw(11) << CO[i].sellerID << endl;
					}
				}
				cout << endl << endl;
			}
			else if (st2 == "commodityName") {
				string st0[8];
				cout << setiosflags(ios::left);
				int judge = 0;
				for (int i = 0; i <= 0; i++) {
					if ((CO[i].commodityName.find(st3) != -1)&&(CO[i].state==1)) {
						judge++;
						if (judge == 1) {
							IFS.open("commodity.txt", ios::in);
							if (!IFS.is_open()) {
								cout << "can't open the file";
								exit(-1);
							}
							cout << endl << endl;
							Show_first(IFS, st0, "commodity", "Buyers");
							IFS.close();
						}
						cout << setw(14) << CO[i].commodityID <<
							setw(18) << CO[i].commodityName <<
							setw(8) << CO[i].price <<
							setw(13) << CO[i].addedDate <<
							setw(11) << CO[i].sellerID << endl;
					}
				}
				for (int i = 1; i <= num; i++) {
					if ((CO[i].commodityName.find(st3) != -1) && (CO[i].state == 1)) {
						judge++;
						if (judge == 1) {
							IFS.open("commodity.txt", ios::in);
							if (!IFS.is_open()) {
								cout << "can't open the file";
								exit(-1);
							}
							cout << endl << endl;
							Show_first(IFS, st0, "commodity", "Buyers");
							IFS.close();
						}
						cout << "M0" << setw(12) << CO[i].commodityID <<
							setw(18) << CO[i].commodityName <<
							setw(8) << CO[i].price <<
							setw(13) << CO[i].addedDate <<
							setw(11) << CO[i].sellerID << endl;
					}
				}
				cout << endl << endl;
				if (judge == 0)
				{
					cout << endl << endl;
					cout << "============================================================ " << endl;
					cout << "Can't find the Commodity Name you want! Return to the menu!" << endl;
					cout << "============================================================ " << endl;
					cout << endl << endl;
				}
			}
			else if (st2 == "commodityID") {
				string st0[8];
				map<string, commodity> cI_c;
				for (int i = 1; i <= num; i++) {
					CO[i].commodityID = "M0" + CO[i].commodityID;
				}
				for (int i = 0; i <= num; i++) {
					cI_c.insert(pair<string, commodity>(CO[i].commodityID, CO[i]));
				}
				cout << setiosflags(ios::left);
				auto iter = cI_c.find(st3);
				bool judge = false;
				while (iter != cI_c.end()) {
					if (iter->second.state == 0) {
						cout << endl << endl;
						cout << "========================================================== " << endl;
						cout << "Can't find the Commodity ID you want! Return to the menu!" << endl;
						cout << "==========================================================" << endl;
						break;
					}
					IFS.open("commodity.txt", ios::in);
					if (!IFS.is_open()) {
						cout << "can't open the file";
						exit(-1);
					}
					cout << endl << endl;
					IFS.close();
					judge = true;
					cout << "commodityID:" << iter->second.commodityID << endl <<
						"commodityName:" << iter->second.commodityName << endl <<
						"price:" << iter->second.price << endl <<
						"addedDate:" << iter->second.addedDate << endl <<
						"description:" << iter->second.description << endl <<
						"sellerID:" << iter->second.sellerID << endl;
					cout << endl << endl;
					break;
				}
				if (!judge)
				{
					cout << endl << endl;
					cout << "========================================================== " << endl;
					cout << "Can't find the Commodity ID you want! Return to the menu!" << endl;
					cout << "==========================================================" << endl;
				}
			}
		}
		else if (st1 == "order") {
			string st[7];
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
			if (st2 == "buyerID") {
				int judge = 0;
				for (int i = 0; i <= num; i++) {
					if (OR[i].buyerID.find(st3) != -1) {
						judge++;
						if (judge == 1) {
							cout << setiosflags(ios::left);
							IFS.open("order.txt", ios::in);
							if (!IFS.is_open()) {
								cout << "can't open the file";
								exit(-1);
							}
							cout << endl << endl;
							Show_first(IFS, st, "order", "Buyers");
							IFS.close();
						}
						cout << setiosflags(ios::left);
						if (i == 0) {
							cout << setw(10) << OR[i].orderID <<
								setw(14) << OR[i].commodityID <<
								setw(12) << OR[i].unitPrice << setw(9) <<
								OR[i].number << setw(13) << OR[i].date <<
								setw(11) << OR[i].sellerID << endl;
						}
						else {
							cout << "T" << setw(9) << OR[i].orderID <<
								setw(14) << OR[i].commodityID <<
								setw(12) << OR[i].unitPrice << setw(9) <<
								OR[i].number << setw(13) << OR[i].date <<
								setw(11) << OR[i].sellerID << endl;
						}
					}
				}
				if (!judge)
				{
					cout << endl << endl;
					cout << "============================================================ " << endl;
					cout << "You have not been purchased, no orders! Return to the menu!" << endl;
					cout << "============================================================ " << endl;
				}
				cout << endl << endl;
			}
		}
	}
	else if (st0 == "Sellers") {
		if (st1 == "commodity") {
			string st[8];
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
			if (st2 == "sellerID") {
				int judge = 0;
				for (int i = 0; i <= 0; i++) {
					if (CO[i].sellerID.find(st3) != -1) {
						judge++;
						if (judge == 1) {
							cout << setiosflags(ios::left);
							IFS.open("commodity.txt", ios::in);
							if (!IFS.is_open()) {
								cout << "can't open the file";
								exit(-1);
							}
							cout << endl << endl;
							Show_first(IFS, st, "commodity", "Sellers");
							IFS.close();
						}
						cout << setw(14) << CO[i].commodityID <<
							setw(18) << CO[i].commodityName <<
							fixed << setprecision(1) <<
							setw(8) << CO[i].price <<
							setprecision(0) << setw(9) << CO[i].number <<
							setw(13) << CO[i].addedDate;
						if (CO[i].state == 1)
							cout << setw(8) << "onSale" << endl;
						else cout << setw(8) << "remove" << endl;

					}
				}
				for (int i = 1; i <= num; i++) {
					if (CO[i].sellerID.find(st3) != -1) {
						judge++;
						if (judge == 1) {
							cout << setiosflags(ios::left);
							IFS.open("commodity.txt", ios::in);
							if (!IFS.is_open()) {
								cout << "can't open the file";
								exit(-1);
							}
							cout << endl << endl;
							Show_first(IFS, st, "commodity", "Sellers");
							IFS.close();
						}
						cout << "M0" << setw(12) << CO[i].commodityID <<
							setw(18) << CO[i].commodityName <<
							fixed << setprecision(1) <<
							setw(8) << CO[i].price <<
							setprecision(0) << setw(9) << CO[i].number <<
							setw(13) << CO[i].addedDate;
						if (CO[i].state == 1)
							cout << setw(8) << "onSale" << endl;
						else cout << setw(8) << "remove" << endl;

					}
				}
				if (!judge)
				{
					cout << endl << endl;
					cout << "=========================================================== " << endl;
					cout << "You have not updated the commodities! Return to the menu!" << endl;
					cout << "=========================================================== " << endl;
				}
				cout << endl << endl;
			}
		}
		else if (st1 == "order") {
			string st[7];
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
			if (st2 == "sellerID") {
				int judge = 0;
				for (int i = 0; i <= num; i++) {
					if (OR[i].sellerID.find(st3) != -1) {
						judge++;
						if (judge == 1) {
							cout << setiosflags(ios::left);
							IFS.open("order.txt", ios::in);
							if (!IFS.is_open()) {
								cout << "can't open the file";
								exit(-1);
							}
							cout << endl << endl;
							Show_first(IFS, st, "order", "Sellers");
							IFS.close();
						}
						if (i == 0) {
							cout << setw(10) << OR[i].orderID <<
								setw(14) << OR[i].commodityID <<
								setw(12) << fixed << setprecision(1) << OR[i].unitPrice << setw(9) <<
								setprecision(0) << OR[i].number << setw(13) << OR[i].date <<
								setw(11) << OR[i].buyerID << endl;
						}
						else {
							cout << "T" << setw(9) << OR[i].orderID <<
								setw(14) << OR[i].commodityID <<
								setw(12) << fixed << setprecision(1) << OR[i].unitPrice << setw(9) <<
								setprecision(0) << OR[i].number << setw(13) << OR[i].date <<
								setw(11) << OR[i].buyerID << endl;
						}
					}
				}
				if (!judge)
				{
					cout << endl << endl;
					cout << "====================================================== " << endl;
					cout << "You do not already have an order! Return to the menu!" << endl;
					cout << "====================================================== " << endl;
				}
				cout << endl << endl;
			}
		}
	}
}
void SQL::UPDATE(string st) {
	Save_to_commands(st);
	if (st.find("commodity") != -1) {
		ifstream ifs;
		ifs.open("commodity.txt", ios::in);
		if (!ifs.is_open()) {
			cout << "can't open the file";
			exit(-1);
		}
		char st1[200];
		ifs.getline(st1, 200);
		int num = 0;
		commodity CO[100];
		bool judge = Get(ifs, CO[num]);
		while (!ifs.eof()) {
			int j = ifs.get();
			if (j != -1)
			{
				//IFS.seekg(-1, ios::cur);
				num++;
				judge = Get(ifs, CO[num]);
			}
		}
		ifs.close();
		if (st.find("commodityID") != -1) {
			size_t i = st.find("commodityID");
			size_t j = i + 14;
			string st1 = st.substr(j);//Interception of Commodity ID characters
			//cout << "st1=" << st1 << endl;
			map<string, commodity> cN_c;
			for (int i = 1; i <= num; i++) {
				CO[i].commodityID = "M0" + CO[i].commodityID;
			}
			for (int i = 0; i <= num; i++) {
				cN_c.insert(pair<string, commodity>(CO[i].commodityID, CO[i]));
			}
			//update the corresponding data
			auto iter1 = cN_c.find(st1);
			if (iter1 != cN_c.end()) {
				if (st.find("state") != -1) {
					size_t i = st.find("state");
					size_t j = i + 8;
					if (st[j] == 'o')
						iter1->second.state = 1;
					else iter1->second.state = 0;
				}
				else if (st.find("price") != -1) {
					size_t i1 = st.find("price");
					size_t i2 = st.find("WHERE");
					size_t j = i1 + 8;
					string price = st.substr(j, i2 - j - 1);
					stringstream ss;
					ss << price;
					double p = 0;
					while (ss >> price) {
						p = convert<double>(price);
					}
					iter1->second.price = p;
				}
				else if (st.find("description") != -1) {
					size_t i1 = st.find("description");
					size_t i2 = st.find("WHERE");
					size_t j = i1 + 14;
					string Des = st.substr(j, i2 - j - 1);
					iter1->second.description = Des;
				}
				else if (st.find("number") != -1) {
					size_t i1 = st.find("number");
					size_t i2 = st.find("WHERE");
					size_t j = i1 + 9;
					string NUM = st.substr(j, i2 - j - 1);
					stringstream ss;
					int n;
					ss << NUM;
					while (ss >> NUM)
						n = convert<int>(NUM);
					iter1->second.number = n;
					if (n == 0) {
						iter1->second.state = 0;
						string st100 = "UPDATE commodity SET state = remove WHERE commodityID = " + iter1->second.commodityID;
						SQL S;
						S.UPDATE(st100);
					}
				}
			}
			//update the files
			ofstream ofs;
			ofs.open("commodity.txt", ios::out);
			ofs << "commodityID,commodityName,price,number,description,sellerID,addedDate,state" << endl;
			ofs.close();
			auto iter2 = cN_c.begin();
			while (iter2 != cN_c.end()) {
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
		}
		else if (st.find("sellerID") != -1) {
			size_t i = st.find("sellerID");
			size_t j = i + 11;
			string st1 = st.substr(j);//Interception of Seller ID characters
			//cout << "st1=" << st1 << endl;
			//update the corresponding data
			size_t m = st.find("state");
			size_t n = m + 8;
			for (int k = 0; k <= num; k++) {
				if (CO[k].sellerID == st1) {
					if (st[n] == 'o')
						CO[k].state = 1;
					else CO[k].state = 0;
				}
			}
			//update the files
			ofstream ofs;
			ofs.open("commodity.txt", ios::out);
			ofs << "commodityID,commodityName,price,number,description,sellerID,addedDate,state" << endl;
			ofs.close();
			for (int i = 0; i <= num; i++) {
				ofs.open("commodity.txt", ios::app);
				ofs << CO[i].commodityID << ','
					<< CO[i].commodityName << ','
					<< CO[i].price << ','
					<< CO[i].number << ','
					<< CO[i].description << ','
					<< CO[i].sellerID << ','
					<< CO[i].addedDate << ',';
				if (CO[i].state == 1)
					ofs << "onSale" << endl;
				else ofs << "remove" << endl;
				ofs.close();
			}
		}
		//update the 'shopping cart.txt'
		ifstream ifs1;
		ifs1.open("commodity.txt", ios::in);
		if (!ifs1.is_open()) {
			cout << "can't open the file";
			exit(-1);
		}
		char str2[200];
		ifs1.getline(str2, 200);
		int num1 = 0;
		commodity CO1[100];
		bool judge1 = Get(ifs1, CO1[num1]);
		while (!ifs1.eof()) {
			int j = ifs1.get();
			if (j != -1)
			{
				num1++;
				judge1 = Get(ifs1, CO1[num1]);
			}
		}
		for (int i = 1; i <= num1; i++)
			CO1[i].commodityID = "M0" + CO1[i].commodityID;
		ifstream ifs2;
		ifs2.open("shopping cart.txt", ios::in);
		if (!ifs2.is_open()) {
			cout << "can't open the file";
			exit(-1);
		}
		char str3[200];
		ifs2.getline(str3, 200);
		int num2 = 0;
		shopping_cart SH[100];
		bool judge2 = Get(ifs2, SH[num2]);
		while (!ifs2.eof()) {
			int j = ifs2.get();
			if (j != -1)
			{
				num2++;
				judge2 = Get(ifs2, SH[num2]);
			}
		}
		for (int i = 1; i <= num2; i++)
			SH[i].commodityID = "M" + SH[i].commodityID;
		for (int i = 0; i <= num1; i++) {
			for (int i1 = 0; i1 <= num2; i1++) {
				if (CO1[i].commodityID == SH[i1].commodityID) {
					SH[i1].commodityName = CO1[i].commodityName;
					SH[i1].price = CO1[i].price;
					SH[i1].description = CO1[i].description;
					SH[i1].state = CO1[i].state;
				}
			}
		}
		//update the 'shopping cart.txt'
		ofstream ofs;
		ofs.open("shopping cart.txt", ios::out);
		ofs << "commodityID,commodityName,price,number,description,sellerID,addedDate,state,buyerID" << endl;
		ofs.close();
		for (int i1 = 0; i1 <= num2;i1++) {
			ofs.open("shopping cart.txt", ios::app);
			ofs << SH[i1].commodityID << ',' <<
				SH[i1].commodityName << ',' <<
				SH[i1].price << ',' <<
				SH[i1].number << ',' <<
				SH[i1].description << ',' <<
				SH[i1].sellerID << ',' <<
				SH[i1].addedDate << ',';
			if (SH[i1].state == 1)
				ofs << "onSale" << ',';
			else ofs << "remove" << ',';
			ofs << SH[i1].buyerID << endl;
			ofs.close();
		}
	}
	else if (st.find("user") != -1) {
		ifstream ifs;
		ifs.open("user.txt", ios::in);
		if (!ifs.is_open()) {
			cout << "can't open the file";
			exit(-1);
		}
		char st1[200];
		ifs.getline(st1, 200);
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
		if (st.find("userID") != -1) {
			size_t i = st.find("userID");
			size_t j = i + 9;
			string st1 = st.substr(j);//Interception of User ID characters
			//cout << "st1=" << st1 << endl;
			map<string, user> ID_US;
			for (int i = 1; i <= num; i++) {
				US[i].userID = "U0" + US[i].userID;
			}
			for (int i = 0; i <= num; i++) {
				ID_US.insert(pair<string, user>(US[i].userID, US[i]));
			}
			//update the corresponding data
			auto iter1 = ID_US.find(st1);
			if (iter1 != ID_US.end()) {
				if (st.find("userState") != -1) {
					size_t i = st.find("userState");
					size_t j = i + 12;
					if (st[j] == 'a')
						iter1->second.userState = 1;
					else iter1->second.userState = 0;
				}
			}
			//update the files
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
		}

	}

}
void SQL::Save_to_commands(string st) {
	ofstream ofs("commands.txt", ios::app);
	time_t timep;
	struct tm* p;
	time(&timep);
	p = localtime(&timep);
	ofs << p->tm_year + 1900 << "-" <<
		setw(2) << setfill('0') << p->tm_mon << "-" <<
		setw(2) << setfill('0') << p->tm_mday << " " <<
		setw(2) << setfill('0') << p->tm_hour << ":" <<
		setw(2) << setfill('0') << p->tm_min << ":" <<
		setw(2) << setfill('0') << p->tm_sec << ":" << st << endl;
	ofs.close();
}
void SQL::INSERT_INTO(string st, string a) {
	Save_to_commands(st);
	if (st.find("commodity") != -1) {
		ifstream ifs;
		ifs.open("commodity.txt", ios::in);
		if (!ifs.is_open()) {
			cout << "can't open the file";
			exit(-1);
		}
		char st1[200];
		ifs.getline(st1, 200);
		if (ifs.eof()) {
			ifs.close();
			ofstream ofs;
			ofs.open("commodity.txt", ios::app);
			if (!ofs.is_open()) {
				cout << "can't open the file";
				exit(-1);
			}
			size_t first = st.find("(");
			size_t last = st.find(")");
			string st0[4];
			for (int j = first + 1, i = 0; j < last; j++) {
				char ch = st[j];
				if (ch == ',') {
					i++;
					continue;
				}
				else {
					st0[i] += ch;
				}
			}
			time_t timep;
			struct tm* p;
			time(&timep);
			p = localtime(&timep);
			ofs << endl << "M001" << "," <<
				st0[0] << "," << st0[1] << "," << st0[2] << "," <<
				st0[3] << "," << a << "," << p->tm_year + 1900 << "-" <<
				setw(2) << setfill('0') << p->tm_mon << "-" <<
				setw(2) << setfill('0') << p->tm_mday
				<< "," << "onSale" << endl;
		}
		else {
			int num = 0;
			commodity CO[100];
			bool judge = Get(ifs, CO[num]);
			while (!ifs.eof()) {
				int j = ifs.get();
				if (j != -1)
				{
					//IFS.seekg(-1, ios::cur);
					num++;
					judge = Get(ifs, CO[num]);
				}
			}
			ifs.close();
			ofstream ofs;
			ofs.open("commodity.txt", ios::app);
			if (!ofs.is_open()) {
				cout << "can't open the file";
				exit(-1);
			}
			size_t first = st.find("(");
			size_t last = st.find(")");
			string st0[4];
			for (int j = first + 1, i = 0; j < last; j++) {
				char ch = st[j];
				if (ch == ',') {
					i++;
					continue;
				}
				else {
					st0[i] += ch;
				}
			}
			time_t timep;
			struct tm* p;
			time(&timep);
			p = localtime(&timep);
			ofs << "M" << setw(3) << setfill('0') << num + 2 << "," <<
				st0[0] << "," << st0[1] << "," << st0[2] << "," <<
				st0[3] << "," << a << "," << p->tm_year + 1900 << "-" <<
				setw(2) << setfill('0') << p->tm_mon << "-" <<
				setw(2) << setfill('0') << p->tm_mday
				<< "," << "onSale" << endl;
		}
	}
	else if (st.find("order") != -1) {
		ifstream ifs;
		ifs.open("order.txt", ios::in);
		char ch100[200];
		ifs.getline(ch100, 200);
		if (ifs.eof()) {
			ofstream ofs;
			ofs.open("order.txt", ios::app);
			if (!ofs.is_open()) {
				cout << "can't open the file";
				exit(-1);
			}
			size_t first = st.find("(");
			size_t last = st.find(")");
			string st0[7];
			for (int j = first + 1, i = 0; j < last; j++) {
				char ch = st[j];
				if (ch == ',') {
					i++;
					continue;
				}
				else {
					st0[i] += ch;
				}
			}
			time_t timep;
			struct tm* p;
			time(&timep);
			p = localtime(&timep);
			ofs << endl << "T001" << "," << st0[1] << "," << st0[2] << ","
				<< st0[3] << "," << p->tm_year + 1900 << "-" <<
				setw(2) << setfill('0') << p->tm_mon << "-" <<
				setw(2) << setfill('0') << p->tm_mday
				<< "," << st0[5] << "," << st0[6] << endl;
		}
		else {
			ofstream ofs;
			ofs.open("order.txt", ios::app);
			if (!ofs.is_open()) {
				cout << "can't open the file";
				exit(-1);
			}
			size_t first = st.find("(");
			size_t last = st.find(")");
			string st0[7];
			for (int j = first + 1, i = 0; j < last; j++) {
				char ch = st[j];
				if (ch == ',') {
					i++;
					continue;
				}
				else {
					st0[i] += ch;
				}
			}
			time_t timep;
			struct tm* p;
			time(&timep);
			p = localtime(&timep);
			ofs << st0[0] << "," << st0[1] << "," << st0[2] << ","
				<< st0[3] << "," << p->tm_year + 1900 << "-" <<
				setw(2) << setfill('0') << p->tm_mon << "-" <<
				setw(2) << setfill('0') << p->tm_mday
				<< "," << st0[5] << "," << st0[6] << endl;
		}
	}
}