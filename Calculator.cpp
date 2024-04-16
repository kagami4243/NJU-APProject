#define _CRT_SECURE_NO_WARNINGS
#include"Calculator.h"
string Calculate::calculate(string st) {
	string judge = IsLegal(st);
	if (judge != "correct")
		return judge;
	else return getResult(st);
}
string Calculate::getResult(string st) {
	string st1 = solve_Negative(st);
	getPostfix(st1);
	//for (int i = 0; i < postfix.size(); i++) {
	//	cout << postfix[i] << endl;
	//}
	string temp;
	for (int i = 0; i < postfix.size(); i++) {
		temp = postfix[i];
		if (temp[0] >= '0' && temp[0] <= '9') {
			double number = atof(temp.c_str());
			figure.push(number);
		}
		else if (temp == "+") {
			op1 = figure.top();
			figure.pop();
			op2 = figure.top();
			figure.pop();
			figure.push(op1 + op2);
		}
		else if (temp == "-") {
			op1 = figure.top();
			figure.pop();
			op2 = figure.top();
			figure.pop();
			figure.push(op2 - op1);
		}
		else if (temp == "*") {
			op1 = figure.top();
			figure.pop();
			op2 = figure.top();
			figure.pop();
			figure.push(op1 * op2);
		}
		else if (temp == "/") {
			op1 = figure.top();
			figure.pop();
			op2 = figure.top();
			figure.pop();
			if (op1 == 0)
				return "Can't put 0 as the divisor!";
			else figure.push(op2 / op1);
		}
	}
	double res = figure.top();
	string st0;
	stringstream ss;
	ss << res;
	while (ss >> res)
		st0 = convert<string>(res);
	return st0;
}
void Calculate::getPostfix(string st) {
	for (int i = 0; i < st.length(); i++) {
		switch (st[i]) {
		case'+':
		case'-':
		case'*':
		case'/':
			if (signal.empty() || signal.top() == '(' ||
				(get_Level(st[i]) > get_Level(signal.top())))
				signal.push(st[i]);
			else {
				while (!signal.empty() && (get_Level(st[i]) <= get_Level(signal.top()))) {
					//cout << get_Level(st[i]) << endl;
					//cout << get_Level(signal.top()) << endl;
					string temp = "";
					temp += signal.top();
					postfix.push_back(temp);
					signal.pop();
				}
				signal.push(st[i]);
			}
			break;
		case'(':
			signal.push(st[i]);
			break;
		case')':
			while (!signal.empty() && signal.top() != '(') {
				string temp = "";
				temp += signal.top();
				postfix.push_back(temp);
				signal.pop();
			}
			if (!signal.empty() && signal.top() == '(')
				signal.pop();
			break;
		case' ':
			break;
		default:
			string temp = "";
			for (int j = i; j < st.length(); j++) {
				if (st[j] == ' ')
					continue;
				else if ((st[j] >= '0' && st[j] <= '9') || st[j] == '.') {
					i = j;
					temp += st[j];
				}
				else break;
			}
			postfix.push_back(temp);
			break;
		}
	}
	while (!signal.empty()) {
		string temp = "";
		temp += signal.top();
		postfix.push_back(temp);
		signal.pop();
	}
}
int Calculate::get_Level(char ch) {
	if (ch == '+' || ch == '-')
		return 1;
	else if (ch == '*' || ch == '/')
		return 2;
	else if (ch == '(')
		return 0;
}
string Calculate::IsLegal(string st) {
	int leftNumber = 0, rightNumber = 0;
	if (st == "")
		return "Illegal Input!";
	bool JUDGE = false;
	for (int i = 0; i < st.length(); i++) {
		if (st[i] != ' ') {
			JUDGE = true;
			break;
		}
	}
	if(!JUDGE)
		return "Illegal Input!";
	for (int i = 0; i < st.length(); i++) {
		//judge characters that are not legal
		if ((st[i] < '0' || st[i]>'9') && st[i] != '+' && st[i] != '-' && st[i] != '*' && st[i] != '/' && st[i] != '(' && st[i] != ')' && st[i] != ' ' && st[i] != '.')
			return "Contains characters that are not legal!";
		//
		if (st[i] == '+' || st[i] == '-' || st[i] == '*' || st[i] == '/')
		{   //Operator is not available at the bottom
			if (i == st.length() - 1)
				return "Operator to misuse!";
			int j = i + 1;
			bool judge = true;
			if (st[j] == ' ')
				judge = false;
			if (!judge) {
				for (; j < st.length(); j++) {
					if (st[j] != ' ')
						break;
				}
			}
			//judge whether / 0
			if (st[i] == '/' && st[j] == '0')
				return "Can't put 0 as the divisor!";
			//judge whether the operator is used together
			if (st[j] == '+' || st[j] == '-' || st[j] == '*' || st[j] == '/')
				return "Operator to misuse!";
			//judge if the operator as a closing right parenthesis
			if (st[j] == ')')
				return "Incorrect brackets use!";
		}
		//
		if (st[i] == '+' || st[i] == '*' || st[i] == '/') {
			//Operator is not available on top ( except - )
			if (i == 0)
				return "Operator to misuse!";
			int j = i - 1;
			for (; j >= 0; j--) {
				if (st[j] != ' ')
					break;
			}
			if (j == -1)
				return "Operator to misuse!";
			//Operator is not available as a single operation ( except - )
			if ((st[j] < '0' || st[j]>'9') && st[j] != ')')
				return "Operator to misuse!";
		}
		//
		if (st[i] == '(') {
			leftNumber++;
			//Determine if the parentheses matches
			int temp_left = leftNumber, temp_right = 0;
			for (int temp = i; temp < st.length(); temp++) {
				if (st[temp] == ')') {
					temp_right++;
				}
			}
			if (temp_right < (temp_left - rightNumber))
				return "Incorrect brackets use!";
			//left parenthesis is not available at the bottom
			if (i == st.length() - 1)
				return "Incorrect brackets use!";
			int j = i + 1;
			bool judge = true;
			if (st[j] == ' ')
				judge = false;
			if (!judge) {
				for (; j < st.length(); j++) {
					if (st[j] != ' ')
						break;
				}
			}
			//After the left parenthesis is not available for the operator and the decimal point
			if (st[j] == '+' || st[j] == '*' || st[j] == '/')
				return "Operator to misuse!";
			else if (st[j] == ')')
				return "Incorrect brackets use!";

		}
		//
		if (st[i] == ')') {
			rightNumber++;
			//Determine if the parentheses matches
			int temp_left = 0, temp_right = rightNumber;
			for (int temp = 0; temp < i; temp++) {
				if (st[temp] == '(') {
					temp_left++;
				}
			}
			if (temp_left < (temp_right - leftNumber))
				return "Incorrect brackets use!";
			//right parenthesis is not available at the top
			if (i == 0)
				return "Incorrect brackets use!";
			if (i != st.length() - 1) {
				int j = i + 1;
				bool judge = true;
				if (st[j] == ' ')
					judge = false;
				if (!judge) {
					for (; j < st.length(); j++) {
						if (st[j] != ' ')
							break;
					}
				}
				//Determine if the closing right parenthesis is attached directly to digital
				if (st[j] >= '0' && st[i] <= '9')
					return "The operator of the lack of need!";
			}
		}
		//
		if (st[i] == '.') {
			//Determine if the decimal point at the top or not as a number before the decimal point
			if (i - 1 < 0 || st[i - 1] < '0' || st[i - 1]>'9')
				return "Incorrect Number!";
			//Determine if the decimal point in the last or not as a number after the decimal point
			else if (i + 1 >= st.length() || st[i + 1] < '0' || st[i + 1]>'9')
				return "Incorrect Number!";
			//judge whether the number is one Decimal
			else if (i + 2 < st.length()) {
				if ((st[i + 2] >= '0' && st[i] <= '9') || st[i + 2] == '.')
					return "Incorrect Number!";
			}
		}
		//
		if (st[i] >= '0' && st[i] <= '9') {
			int j = i + 1;
			if (j < st.length()) {
				bool judge = true;
				if (st[j] == ' ')
					judge = false;
				if (!judge) {
					for (; j < st.length(); j++) {
						if (st[j] != ' ')
							break;
					}
				}
				//Judging whether a space between the two figures apart
				if (j != (i + 1) && st[j] >= '0' && st[j] <= '9')
					return "Incorrect Number!";
				//Determine if left parentheses is after the number
				if (st[j] == '(')
					return "The operator of the lack of need!";
			}
		}
	}
	return "correct";
}
string Calculate::solve_Negative(string st) {
	for (int i = 0; i < st.length(); i++) {
		if (st[i] == '-') {
			if (i == 0) {
				st.insert(0, 1, '0');
			}
			else {
				int j = i - 1;
				for (; j >= 0; j--) {
					if (st[j] != ' ')
						break;
				}
				if (st[j] == '(')
					st.insert(i, 1, '0');
			}
		}
	}
	return st;
}