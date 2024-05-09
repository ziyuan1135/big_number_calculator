#pragma once
#include"NormalArithmetic.h"
#include"MathExpression.h"
#include"Parser.h"
#include"Integer.h"
#include<string>
#include<sstream>
#include"Basic.h"

class Decimal :public Basic {
public:
	vector<string> list;
	MathExpression me;
	Decimal() { list.clear(); me = MathExpression(); }
	Decimal(const char* line) {
		list.clear();
		setting(line);
	}
	Decimal(const string& line) {
		list.clear();
		setting(line);
	}
	Decimal(const Integer& num) {
		list.clear();
		me = num.me;
		me.denominator.push_front(0);
		if (me.numerator.back() != 0) me.numerator.push_front(0);
	}

	MathExpression outcome(ostream& os) {
		os << "Decimal: ";
		return me;
	}
	void setting(const string& line) {
		string input;
		stringstream ss(line);
		while (ss >> input) { list.push_back(input); }
		if (list.size() == 0) cout << "Empty\n";
		else {
			MathExpression value = Parser::parse(0, list.size() - 1, list);
			me = value;
			if (value.denominator.size() == 1 && value.denominator.back() == 1) {
				me.denominator.push_front(0);
				if (me.numerator.back() != 0) me.numerator.push_front(0);
			}
		}
	}
	Decimal operator+(const Decimal& numInt) {
		Decimal result;
		result.me = me + numInt.me;
		return result;
	}
	Decimal operator-(const Decimal& numInt) {
		Decimal result;
		result.me = me - numInt.me;
		return result;
	}
	Decimal operator*(const Decimal& numInt) {
		Decimal result;
		result.me = me * numInt.me;
	}
	Decimal operator/(const Decimal& numInt) {
		Decimal result;
		result.me = me / numInt.me;
		return result;
	}
	friend Decimal operator+(const Integer& numInt, const Decimal& numDec) {
		Decimal result;
		result.me = numInt.me + numDec.me;
		return result;
	}
	friend Decimal operator-(const Integer& numInt, const Decimal& numDec) {
		Decimal result;
		result.me = numInt.me - numDec.me;
		return result;
	}
	friend Decimal operator*(const Integer& numInt, const Decimal& numDec) {
		Decimal result;
		result.me = numInt.me * numDec.me;
		return result;
	}
	friend Decimal operator/(const Integer& numInt, const Decimal& numDec) {
		Decimal result;
		result.me = numInt.me / numDec.me;
		return result;
	}
	friend ostream& operator<<(ostream& os, const Decimal& num) {
		os << num.me;
		return os;
	}
	friend istream& operator>>(istream& is, Decimal& num) {
		string line;
		cout << "class Decmial istream overloading: please input expression.\n";
		getline(is, line);
		num = Decimal(line);
		return is;
	}
};