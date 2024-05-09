#pragma once
#include"NormalArithmetic.h"

class MathExpression :public NormalArithmetic {
public:
	int sign;
	deque<int> numerator;
	deque<int> denominator;
	MathExpression() { numerator.clear(); denominator.clear(); sign = 1; }
	MathExpression(const string& id) :sign(1) {
		int start = 0, end = id.size() - 1;
		while (start != end && id[start] == '0') {
			start++;
		}
		for (int i = end; i >= start; i--) numerator.push_back(id[i] - '0');
		denominator.push_back(1);
		//cout << "constructor: "; 
		//checkInfo();
	}
	MathExpression(const string& id, const int& posDot) :sign(1) {
		int start = 0, end = id.size() - 1;
		while ((end != posDot + 1) && id[end] == '0') end--;
		while ((start != end) && (id[start] == '0' || id[start] == '.')) start++;
		int numDec = end - posDot;
		for (int i = end; i >= start; i--) {
			if (i == posDot) continue;
			numerator.push_back(id[i] - '0');
		}
		for (int i = 0; i < numDec; i++) denominator.push_back(0);
		denominator.push_back(1);
	}

	void checkInfo() {
		cout << "sign: " << sign << "\n";
		cout << "num: ";
		for (int i = numerator.size() - 1; i >= 0; i--) cout << numerator[i] << " ";
		cout << "\nden: ";
		for (int i = denominator.size() - 1; i >= 0; i--) cout << denominator[i] << " ";
		cout << "\n";
	}
	friend MathExpression degree(const MathExpression& me) {
		MathExpression result("1");
		deque<int> count, maxNum;
		count.push_front(2);
		if (me.sign < 0) {
			cout << "Degree Error: sign can't be negative.\n";
			return MathExpression();
		}
		if (me.denominator.size() != 1 && !modIsZero(me.numerator, me.denominator, maxNum)) {
			cout << "Degree Error: Number can't be divisible.\n";
			return MathExpression();
		}
		else {
			if (maxNum.size() == 0) maxNum = me.numerator;
			//cout << "Max Num: ";
			//for (int i = maxNum.size() - 1; i >= 0; i--) cout << maxNum[i]; cout << endl;
			while (!isGreater(count, maxNum)) {
				result.numerator = mulR(result.numerator, count);
				increaseOne(count);
				//result.checkInfo();
				//cout << "count: ";
				//for(int i = count.size() - 1; i >= 0; i--) cout << count[i];
				//cout << endl;
			}
			// cancel auto convertion type with bellowing
			//if (me.denominator.size() != 1) {
			//	result.denominator.push_front(0);
			//	result.numerator.push_front(0);
			//}
			return result;
		}
	}
	friend MathExpression exp(const MathExpression& num, const MathExpression& expNum) {
		MathExpression result;
		deque<int> quotient, count;
		count.push_back(1);
		if (num.denominator.size() == 0 || expNum.denominator.size() == 0) return result;
		if (modIsZero(expNum.numerator, expNum.denominator, quotient)) {
			if (quotient.size() == 1 && quotient.back() == 0) return MathExpression("1");
			if (expNum.sign == -1 && num.numerator.size() == 1 && num.numerator.back() == 0) {
				cout << "Exp Error: negative expNum will cause zero in denominator.\n";
				return result;
			}
			else if (expNum.sign == -1 && num.denominator.size() == 1 && num.denominator.back() == 1) {
				result = MathExpression("0");
				return result;
			}
			else if (expNum.sign == -1) {
				result.denominator = num.numerator;
				result.numerator = num.denominator;
			}
			else result = num;
			while (!isGreaterOrEqual(count, quotient)) {
				if (expNum.sign == 1) {
					result.numerator = mulR(result.numerator, num.numerator);
					result.denominator = mulR(result.denominator, num.denominator);
				}
				else {
					result.numerator = mulR(result.numerator, num.denominator);
					result.denominator = mulR(result.denominator, num.numerator);
				}
				increaseOne(count);
			}
			return result;
		}
		else {
			cout << "Exp Error: expNum must be integer.\n";
			return result;
		}
	}
	MathExpression signConvert(const int& convert) {
		sign *= convert;
		return *this;
	}
	friend ostream& operator<<(ostream& os, const MathExpression& me) {
		deque<int> decResult;
		if (me.denominator.size() == 0) return os;
		int decPos, count = 0;
		bool go = false;
		if (me.sign == -1 && !(me.numerator.size() == 1 && me.numerator.back() == 0)) os << "-";
		if (me.denominator.back() == 1 && me.denominator.size() == 1) {
			for (int i = me.numerator.size() - 1; i >= 0; i--) os << me.numerator[i];
		}
		else {
			divide(me.numerator, me.denominator, decResult, decPos);
			for (int i = 0; i < decResult.size(); i++) {
				if (i == decPos) {
					os << "." << decResult[i];
					go = true;
				}
				else os << decResult[i];
				if (go) count++;
			}
			//os << "\nCount: " << count;
		}
		os << '\n';
		return os;
	}
	//MathExpression operator+(const MathExpression& addNum) {}
	friend MathExpression operator+(const MathExpression& num, const MathExpression& addNum) {
		MathExpression result;
		if (num.denominator.size() == 0 || addNum.denominator.size() == 0) return result;
		deque<int> num01, num02;
		// decide sign
		if (num.sign == -1 && addNum.sign == -1) result.sign = -1;
		else if (addNum.sign == -1) {
			result = addNum;
			result.sign = 1;
			return (num - result);
		}
		else if (num.sign == -1) {
			result = num;
			result.sign = 1;
			return (addNum - result);
		}

		if (num.denominator != addNum.denominator) {
			mul(num.denominator, addNum.denominator, result.denominator);
			mul(addNum.denominator, num.numerator, num01);
			mul(num.denominator, addNum.numerator, num02);
			add(num01, num02, result.numerator);
		}
		else {
			result.denominator = num.denominator;
			add(num.numerator, addNum.numerator, result.numerator);
		}
		//cout << "add: ";
		//result.checkInfo();
		return result;
	}
	//MathExpression operator-(const MathExpression& minusNum) {}
	friend MathExpression operator- (const MathExpression& num, const MathExpression& minusNum) {
		MathExpression result;
		if (num.denominator.size() == 0 || minusNum.denominator.size() == 0) return result;
		deque<int> num01, num02;
		if (num.sign == 1 && minusNum.sign == -1) {
			result = minusNum;
			result.sign = 1;
			return (num + result);
		}
		else if (num.sign == -1 && minusNum.sign == 1) {
			result = minusNum;
			result.sign = -1;
			return (num + result);
		}

		if (num.denominator != minusNum.denominator) {
			mul(num.denominator, minusNum.denominator, result.denominator);
			mul(minusNum.denominator, num.numerator, num01);
			mul(num.denominator, minusNum.numerator, num02);
			if (num.sign == 1 && minusNum.sign == 1) {
				if (isGreaterOrEqual(num01, num02)) subtract(num01, num02, result.numerator);
				else {
					result.sign = -1;
					subtract(num02, num01, result.numerator);
				}
			}
			else if (num.sign == -1 && minusNum.sign == -1) {
				if (isGreaterOrEqual(num02, num01)) subtract(num02, num01, result.numerator);
				else {
					result.sign = -1;
					subtract(num01, num02, result.numerator);
				}
			}
		}
		else {
			result.denominator = num.denominator;
			if (num.sign == 1 && minusNum.sign == 1) {
				if (isGreaterOrEqual(num.numerator, minusNum.numerator)) subtract(num.numerator, minusNum.numerator, result.numerator);
				else {
					result.sign = -1;
					subtract(minusNum.numerator, num.numerator, result.numerator);
				}
			}
			else if (num.sign == -1 && minusNum.sign == -1) {
				if (isGreaterOrEqual(minusNum.numerator, num.numerator)) subtract(minusNum.numerator, num.numerator, result.numerator);
				else {
					result.sign = -1;
					subtract(num.numerator, minusNum.numerator, result.numerator);
				}
			}
		}
		//cout << "minus: ";
		//result.checkInfo();
		return result;
	}
	friend MathExpression operator*(const MathExpression& num, const MathExpression& mulNum) {
		MathExpression result;
		if (num.denominator.size() == 0 || mulNum.denominator.size() == 0) return result;
		mul(num.denominator, mulNum.denominator, result.denominator);
		mul(num.numerator, mulNum.numerator, result.numerator);
		result.sign = num.sign * mulNum.sign;
		//cout << "mul: ";
		//result.checkInfo();
		return result;
	}
	friend MathExpression operator/(const MathExpression& num, const MathExpression& divideNum) {
		MathExpression result;
		if (num.denominator.size() == 0 || divideNum.denominator.size() == 0) return result;
		if (divideNum.numerator.size() == 1 && divideNum.numerator.back() == 0) {
			cout << "divide operator error: denominator can't be zero!\n";
			return result;
		}
		result.sign = num.sign * divideNum.sign;
		if (num.denominator.size() == 1 && num.denominator.back() == 1 && divideNum.denominator.size() == 1 && divideNum.denominator.back() == 1) {
			result.denominator.push_back(1);
			divideInt(num.numerator, divideNum.numerator, result.numerator);
			//cout << "divide Int: ";
			//result.checkInfo();
			return result;
		}
		mul(divideNum.denominator, num.numerator, result.numerator);
		mul(num.denominator, divideNum.numerator, result.denominator);
		//cout << "Nume&Deno mul: ";
		//result.checkInfo();
		return result;
	}
};