#pragma once
#include"MathExpression.h"
#include"NormalArithmetic.h"

bool checkVarName(const string& name) {
	if ((name[0] >= 'a' && name[0] <= 'z') || (name[0] >= 'A' && name[0] <= 'Z')) {
		for (int i = 1; i < name.size(); i++) {
			if ((name[i] >= '0' && name[i] <= '9') || (name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A' && name[i] <= 'Z')) {
				continue;
			}
			else return false;
		}
	}
	else return false;
	return true;
}

class Token :public NormalArithmetic {
public:
	string type;
	MathExpression me;

	Token() {
		type.clear();
	}
	Token(const string& t, const MathExpression& value) :type(t) {
		if (type == "Integer") {
			if (value.denominator.size() == 1 && value.denominator.back() == 1) me = value;
			else {
				me.sign = value.sign;
				me.denominator.push_back(1);
				divideInt(value.numerator, value.denominator, me.numerator);
			}
		}
		else {
			me = value;
			if (value.denominator.size() == 1 && value.denominator.back() == 1) {
				me.denominator.push_front(0);
				if (me.numerator.back() != 0) me.numerator.push_front(0);
			}
		}
	}
	friend ostream& operator<<(ostream& os, const Token& token) {
		os << "type: " << token.type << "\n";
		os << "outcomeNum: " << token.me;
		return os;
	}
};