#pragma once
#ifndef _DATA_H_
#define _DATA_H_
#include<string>
#include<map>
using namespace std;
struct user {
	string userID;
	string username;
	string password;
	string phoneNumber;
	string address;
	double balance;
	bool userState;

};
struct commodity {
	string commodityID="";
	string commodityName="";
	double price;
	int number;
	string description;
	string sellerID;
	string addedDate;
	bool state;
};
struct order {
	string orderID;
	string commodityID;
	double unitPrice;
	int number;
	string date;
	string sellerID;
	string buyerID;
};
struct shopping_cart {
	string commodityID = "";
	string commodityName = "";
	double price;
	int number;
	string description;
	string sellerID;
	string addedDate;
	bool state;
	string buyerID;
};
struct message {
	string seller;
	string receiver;
	string content;
	string date;
};
template<typename out_type, typename in_value>
out_type convert(const in_value& t) {
	stringstream stream;
	stream << t;
	out_type result;
	stream >> result;
	return result;
}
#endif