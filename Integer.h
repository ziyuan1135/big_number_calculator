#pragma once
#include"NormalArithmetic.h"
#include"MathExpression.h"
#include"Parser.h"
#include<string>
#include<sstream>
#include"Basic.h"

class Integer :public Basic {
public:
	vector<string> list;
	MathExpression me;
	Integer() { list.clear(); me = MathExpression(); }
	Integer(const char* line) {
		list.clear();
		setting(line);
	}
	Integer(const string& line) {
		list.clear();
		setting(line);
	}

	MathExpression outcome(ostream& os) {
		os << "Integer: ";
		return me;
	}
	void setting(const string& line) {
		string input;
		stringstream ss(line);
		while (ss >> input) { list.push_back(input); }
		if (list.size() == 0) cout << "Empty\n";
		else {
			MathExpression value = Parser::parse(0, list.size() - 1, list);
			if (value.denominator.size() == 1 && value.denominator.back() == 1) me = value;
			else {
				me.sign = value.sign;
				me.denominator.push_back(1);
				NormalArithmetic::divideInt(value.numerator, value.denominator, me.numerator);
			}
		}
	}
	Integer operator+(const Integer& add) {
		Integer result;
		result.me = me + add.me;
		return result;
	}
	Integer operator-(const Integer& minus) {
		Integer result;
		result.me = me - minus.me;
		return result;
	}
	Integer operator*(const Integer& mul) {
		Integer result;
		result.me = me * mul.me;
		return result;
	}
	Integer operator/(const Integer& divide) {
		Integer result;
		result.me = me / divide.me;
		return result;
	}
	friend ostream& operator<<(ostream& os, const Integer& num) {
		os << num.me;
		return os;
	}
	friend istream& operator>>(istream& is, Integer& num) {
		cout << "class integer istream overloading: please input expression.\n";
		string line;
		getline(is, line);
		num = Integer(line);
		return is;
	}
};