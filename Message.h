#pragma once
#ifndef _MESSAGE_
#define _MESSAGE_
#include<string>
using namespace std;
void Message_Model(string a);
class Message {
public:
	void Menu();//Message Menu
	void send_message(string a);//send message to others
	void view_messages_by_others(string a);//View to the message by others
	void View_messages_from_myself_and_others(string a);//View messages from myself and others
};
#endif