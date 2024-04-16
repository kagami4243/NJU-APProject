#include<string>
using namespace std;
bool Judge_English_And_Number(string st) {
	int len = st.length();
	for (int i = 0; i < len; i++) {
		if (st[i] < '0' || (st[i] > '9' && st[i] < 'A')
			|| (st[i] > 'Z' && st[i] < 'a') || st[i]>'z')
			return false;
	}
	return true;
}
bool Judge_English_small_And_Number(string st) {
	int len = st.length();
	for (int i = 0; i < len; i++) {
		if (st[i] < '0' || (st[i] > '9' && st[i] < 'a') || st[i]>'z')
			return false;
	}
	return true;
}
bool Judge_Number(string st) {
	int len = st.length();
	for (int i = 0; i < len; i++) {
		if (st[i] < '0' || st[i] > '9')
			return false;
	}
	return true;
}
bool Judge_English(string st) {
	int len = st.length();
	for (int i = 0; i < len; i++) {
		if (st[i] < 'A' || (st[i] > 'Z' && st[i] < 'a') || st[i] > 'z')
			return false;
	}
	return true;
}
bool Judge_One_Decimal(string st) {
	int len = st.length();
	for (int i = 0; i < len; i++) {
		if (st[i] < '.' || ((st[i] > '.') && (st[i] < '0')) || st[i] > '9')
			return false;
	}
	int a = st.find('.');
	if (a == 0)
		return false;
	else if (a == -1)
		return true;
	else if ((len - a) != 2)
		return false;
	else return true;
}