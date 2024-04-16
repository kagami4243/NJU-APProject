#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include"Administrator.h"
#include"Users.h"
void Main_Menu();
using namespace std;
int main() {
	string option;
	while (true) {
		Main_Menu();
		getline(cin, option);
		if (option == "1") {
			Administrator_Model();
		}
		else if (option == "2") {
			User_Register();
		}
		else if (option == "3") {
			User_Model();
		}
		else if (option == "4") {
			return 0;
		}
		else{
			cout << "Illegal input!Please re-enter!" << endl << endl << endl;
		}

	}
	return 0;
}
void Main_Menu() {
	cout << "==============================================================" << endl;
	cout << "1.Administrator login 2.User Registration 3.User Login 4.Exit" << endl;
	cout << "==============================================================" << endl;
	cout << endl << endl;
	cout << "Input operation:";
}