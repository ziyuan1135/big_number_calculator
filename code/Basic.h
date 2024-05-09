#pragma once
#include"NormalArithmetic.h"
#include"MathExpression.h"
#include"Parser.h"
#include<string>
#include<sstream>

class Basic {
public:
	virtual  MathExpression outcome(ostream& os) {
		os << "Virtual functoin of Basic class";
		return MathExpression();
	}
	friend ostream& operator<<(ostream& os, Basic& num) {
		os << num.outcome(os);
		return os;
	}
};