#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<sstream>
#include<ctime>
#include<iomanip>
#include<string>
#include<map>
#include"SQL.h"
#include"Data.h"
#include"Judge.h"
#include"Message.h"

void Message_Model(string a) {
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
	Message ME;
	string option;
	while (true) {
		ME.Menu();//message menu
		getline(cin, option);
		if (option == "1") {
			ME.send_message(US[i].userID);//send messages to others
		}
		else if (option == "2") {
			ME.view_messages_by_others(US[i].userID);//View to the message by others
			
		}
		else if (option == "3") {
			ME.View_messages_from_myself_and_others(US[i].userID);//View messages from myself and others
		}
		else if (option == "4") {
			break;
		}
		else {
			cout << "Illegal input!Please re-enter!" << endl << endl << endl;
		}
		cout << endl << endl;
	}
}
void Message::Menu() {
	cout << "============================================================================================================" << endl;
	cout << "1.Send messages 2.View messages by others 3.View messages from myself and others 4.Return to the main menu " << endl;
	cout << "============================================================================================================" << endl << endl << endl;
	cout << "Input operation:";
}
void Message::send_message(string a) {
	cout << "Enter the User ID you want to send a message:";
	string st1;
	getline(cin, st1);
	if (st1 == a) {
		cout << "Can't send message to yourself!" << endl;
		return;
	}
	ifstream IFS;
	IFS.open("user.txt", ios::in);
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
	bool judge1 = false;
	for (int i = 1; i <= num; i++)
		US[i].userID = "U0" + US[i].userID;
	//cout << US[0].userID << endl;
	int i = 0;
	for (; i <= num; i++) {
		if (US[i].userID == st1)
		{
			judge1 = true;
			break;
		}
	}
	if (!judge1) {
		cout << "Can't find the User ID you want to send a message!" << endl;
		return;
	}
	if (US[i].userState == 0) {
		cout << "The user had been banned! Can't send messages to him or her!" << endl;
	}
	cout << "Enter the content you want to send:";
	string content;
	while (true) {
		getline(cin, content);
		int len = content.length();
		if (len > 200) {
			cout << "Commodity Description are not allowed to be longer than 200 characters!" << endl << "Please re-enter:";
		}
		else if (content == "") {
			cout << "Illegal Input !" << endl << "Please re-enter:";
		}
		else break;
	}
	cout << "Successfully!" << endl;
	ofstream ofs;
	ofs.open("message.txt", ios::app);
	if (!ofs.is_open()) {
		cout << "can't open the file";
		exit(-1);
	}
	time_t timep;
	struct tm* p;
	time(&timep);
	p = localtime(&timep);
	ofs << a << "," << st1 << ",";
	ofs << p->tm_year + 1900 << "-" <<
		setw(2) << setfill('0') << p->tm_mon << "-" <<
		setw(2) << setfill('0') << p->tm_mday << "-" <<
		setw(2) << setfill('0') << p->tm_hour << ":" <<
		setw(2) << setfill('0') << p->tm_min << ":" <<
		setw(2) << setfill('0') << p->tm_sec << ",";
	ofs << content << endl;
	
}
void Message::view_messages_by_others(string a) {
	ifstream IFS;
	IFS.open("message.txt", ios::in);
	if (!IFS.is_open()) {
		cout << "can't open the file";
		exit(-1);
	}
	//get the first line
	char ch[200];
	IFS.getline(ch, 200);
	//cout << ch << endl;
	string st[4];
	stringstream ss;
	string st0;
	ss << ch;
	while (ss >> ch)
		st0 = convert<string>(ch);
	//cout << st0 << endl;
	for (int i = 0, j = 0; i < st0.length(); i++) {
		if (st0[i] == ',') {
			j++;
			continue;
		}
		st[j] += st0[i];
	}
	int message_number = 0;
	//cout the details
	int num = 0;
	message ME[100];
	bool judge = Get(IFS, ME[num]);
	while (!IFS.eof()) {
		int j = IFS.get();
		if (j != -1)
		{
			//IFS.seekg(-1, ios::cur);
			num++;
			judge = Get(IFS, ME[num]);
		}
	}
	IFS.close();
	for (int i = 1; i <= num; i++)
		ME[i].seller = "U" + ME[i].seller;
	cout << "Whose messages do you want to view?(1.All people 2.Someone)";
	string st1;
	getline(cin, st1);
	if (st1 == "1") {
		cout << endl << endl;
		for (int i = 0; i <= num; i++) {
			if (ME[i].receiver == a) {
				message_number++;
				if (message_number == 1) {
					cout << setiosflags(ios::left);
					cout << setw(9) << st[0] << setw(11) << st[1]
						<< setw(24) << st[2] << st[3] << endl;
				}
				cout << setiosflags(ios::left);
				cout << setw(9) << ME[i].seller << setw(11) << ME[i].receiver
					<< setw(24) << ME[i].date << ME[i].content << endl;
			}
		}
	}
	else if (st1 == "2") {
		cout << "Enter the User ID you want to view the messages:";
		string st2;
		getline(cin, st2);
		cout << endl << endl;
		for (int i = 0; i <= num; i++) {
			if (ME[i].receiver == a && ME[i].seller == st2) {
				message_number++;
				if (message_number == 1) {
					cout << setiosflags(ios::left);
					cout << setw(9) << st[0] << setw(11) << st[1]
						<< setw(24) << st[2] << st[3] << endl;
				}
				cout << setiosflags(ios::left);
				cout << setw(9) << ME[i].seller << setw(11) << ME[i].receiver
					<< setw(24) << ME[i].date << ME[i].content << endl;
			}
		}
	}
	else {
		cout << "Illegal Input! Return to the menu!" << endl;
		return;
	}
	if (message_number == 0) {
		cout << "You have no messages!" << endl;
		return;
	}
}
void Message::View_messages_from_myself_and_others(string a) {
	ifstream IFS;
	IFS.open("message.txt", ios::in);
	if (!IFS.is_open()) {
		cout << "can't open the file";
		exit(-1);
	}
	//get the first line
	char ch[200];
	IFS.getline(ch, 200);
	//cout << ch << endl;
	string st[4];
	stringstream ss;
	string st0;
	ss << ch;
	while (ss >> ch)
		st0 = convert<string>(ch);
	//cout << st0 << endl;
	for (int i = 0, j = 0; i < st0.length(); i++) {
		if (st0[i] == ',') {
			j++;
			continue;
		}
		st[j] += st0[i];
	}
	int message_number = 0;
	//cout the details
	int num = 0;
	message ME[100];
	bool judge = Get(IFS, ME[num]);
	while (!IFS.eof()) {
		int j = IFS.get();
		if (j != -1)
		{
			//IFS.seekg(-1, ios::cur);
			num++;
			judge = Get(IFS, ME[num]);
		}
	}
	IFS.close();
	for (int i = 1; i <= num; i++)
		ME[i].seller = "U" + ME[i].seller;
	cout << "Whose messages do you want to view?(1.All people 2.Someone)";
	string st1;
	getline(cin, st1);
	if (st1 == "1") {
		cout << endl << endl;
		for (int i = 0; i <= num; i++) {
			if (ME[i].receiver == a|| ME[i].seller==a) {
				message_number++;
				if (message_number == 1) {
					cout << setiosflags(ios::left);
					cout << setw(9) << st[0] << setw(11) << st[1]
						<< setw(24) << st[2] << st[3] << endl;
				}
				cout << setiosflags(ios::left);
				cout << setw(9) << ME[i].seller << setw(11) << ME[i].receiver
					<< setw(24) << ME[i].date << ME[i].content << endl;
			}
		}
	}
	else if (st1 == "2") {
		cout << "Enter the User ID you want to view the messages:";
		string st2;
		getline(cin, st2);
		cout << endl << endl;
		for (int i = 0; i <= num; i++) {
			if ((ME[i].receiver == a && ME[i].seller == st2) || (ME[i].seller == a && ME[i].receiver == st2)) {
				message_number++;
				if (message_number == 1) {
					cout << setiosflags(ios::left);
					cout << setw(9) << st[0] << setw(11) << st[1]
						<< setw(24) << st[2] << st[3] << endl;
				}
				cout << setiosflags(ios::left);
				cout << setw(9) << ME[i].seller << setw(11) << ME[i].receiver
					<< setw(24) << ME[i].date << ME[i].content << endl;
			}
		}
	}
	else {
		cout << "Illegal Input! Return to the menu!" << endl;
		return;
	}
	if (message_number == 0) {
		cout << "You have no messages!" << endl;
		return;
	}

}

