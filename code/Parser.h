#pragma once
#include<vector>
#include<unordered_map>
#include"Token.h"
#include"MathExpression.h"

class Parser {
public:
	static bool checkParentheses(const vector<string>& inputList) {
		int count = 0;
		for (int i = 0; i < inputList.size(); i++) {
			if (inputList[i] == "(") count++;
			else if (inputList[i] == ")") count--;
		}
		if (count == 0)return true;
		return false;
	}
	static bool isDigits(const string& str, int& decPos) {
		int count = 0;
		for (int i = 0; i < str.size(); i++) {
			if (str[i] < '0' || str[i] > '9') {
				if (str[i] == '.' && i != 0 && count == 0 && i != str.size() - 1) {
					count++;
					decPos = i;
				}
				else return false;
			}
		}
		return true;
	}
	static bool isDigits(const string& str) {
		int count = 0;
		for (int i = 0; i < str.size(); i++) {
			if (str[i] < '0' || str[i] > '9') {
				if (str[i] == '.' && i != 0 && count == 0 && i != str.size() - 1) count++;
				else return false;
			}
		}
		return true;
	}
	static bool isValid(const int& index, const vector<string>& inputList) {
		string operatorList[] = { "+","-","*","/","^" };
		for (int i = 0; i < 5; i++) {
			if (inputList[index] == operatorList[i]) return false;
		}
		return true;
	}
	static bool eliminateSign(int& j, int end, int& sign, const vector<string>& inputList) {
		while (inputList[j] == "+" || inputList[j] == "-") {
			if (inputList[j] == "-") sign *= -1;
			j++;
			if (j > end) return false;
		}
		return true;
	}
	static MathExpression parse(int begin, int end, const vector<string>& inputList, const unordered_map<string, Token>& TokenTable) {
		if (begin == end) {
			int decPos = -1;
			if (isDigits(inputList[begin], decPos)) {
				if (decPos != -1) {
					return MathExpression(inputList[begin], decPos);
				}
				else return MathExpression(inputList[begin]);
			}
			else {
				auto it = TokenTable.find(inputList[begin]);
				if (it != TokenTable.end()) {
					return it->second.me;
				}
				else cout << "ERROR: node isn't a number\n";
				return MathExpression();
			}
		}

		int parentheses = 0;
		// procedure1: find "+" OR "-"
		for (int i = end; i >= begin; i--) {
			if (inputList[i] == ")") parentheses++;
			else if (inputList[i] == "(") parentheses--;
			if (inputList[i] == "+" && parentheses == 0 && (i - 1) >= begin && isValid(i - 1, inputList)) {
				if ((i + 1) > end) {
					cout << "ERROR: operator ADD doesn't find id!\n";
					return MathExpression();
				}
				else return(parse(begin, i - 1, inputList, TokenTable) + parse(i + 1, end, inputList, TokenTable));
			}
			else if (inputList[i] == "-" && parentheses == 0 && (i - 1) >= begin && isValid(i - 1, inputList)) {
				if ((i + 1) > end) {
					cout << "ERROR: operator SUBTRACT doesn't find id!\n";
					return MathExpression();
				}
				else return (parse(begin, i - 1, inputList, TokenTable) - parse(i + 1, end, inputList, TokenTable));
			}
		}

		// procedure2: find "*" OR "/"
		for (int i = end; i >= begin; i--) {
			if (inputList[i] == ")") parentheses++;
			else if (inputList[i] == "(") parentheses--;
			if (inputList[i] == "*" && parentheses == 0) {
				if ((i + 1) > end || (i - 1) < begin) {
					cout << "ERROR: operator MUL doesn't find id!\n";
					return MathExpression();
				}
				else return(parse(begin, i - 1, inputList, TokenTable) * parse(i + 1, end, inputList, TokenTable));
			}
			else if (inputList[i] == "/" && parentheses == 0) {
				if ((i + 1) > end || (i - 1) < begin) {
					cout << "ERROR: operator DIVIDE doesn't find id!\n";
					return MathExpression();
				}
				return(parse(begin, i - 1, inputList, TokenTable) / parse(i + 1, end, inputList, TokenTable));
			}
		}

		// procedure3: find sign "+" OR "-"
		int sign = 1, j = begin;
		if (inputList[begin] == "+" || inputList[begin] == "-") {
			if (!eliminateSign(j, end, sign, inputList)) {
				cout << "ERROR: operator sign doesn't match!\n";
				return MathExpression();
			}
			else return parse(j, end, inputList, TokenTable).signConvert(sign);
		}

		// procedure4: find operator "^"
		for (int i = begin; i <= end; i++) {
			if (inputList[i] == ")") parentheses++;
			else if (inputList[i] == "(") parentheses--;
			if (inputList[i] == "^" && parentheses == 0) {
				if (((i + 1) > end) || ((i - 1) < begin)) {
					cout << "ERROR: operator EXP doesn't find id!\n";
					return MathExpression();
				}
				return exp(parse(begin, i - 1, inputList, TokenTable), parse(i + 1, end, inputList, TokenTable));
			}
		}

		// procedure5: find operator "!"
		if (inputList[end] == "!") return degree(parse(begin, end - 1, inputList, TokenTable));

		// procedure6: find operator "()"
		if (inputList[begin] == "(" && inputList[end] == ")") {
			if (begin + 1 == end) {
				cout << "ERROR: operator () doesn't find id!\n";
				return MathExpression();
			}
			else return(parse(begin + 1, end - 1, inputList, TokenTable));
		}

		cout << "Doesn't find any matched operator!\n";
		return MathExpression();
	}

	static MathExpression parse(int begin, int end, const vector<string>& inputList) {
		if (begin == end) {
			int decPos = -1;
			if (isDigits(inputList[begin], decPos)) {
				if (decPos != -1) {
					return MathExpression(inputList[begin], decPos);
				}
				else return MathExpression(inputList[begin]);
			}
			else {
				cout << "ERROR: node isn't a number\n";
				return MathExpression();
			}
		}

		int parentheses = 0;
		// procedure1: find "+" OR "-"
		for (int i = end; i >= begin; i--) {
			if (inputList[i] == ")") parentheses++;
			else if (inputList[i] == "(") parentheses--;
			if (inputList[i] == "+" && parentheses == 0 && (i - 1) >= begin && isValid(i - 1, inputList)) {
				if ((i + 1) > end) {
					cout << "ERROR: operator ADD doesn't find id!\n";
					return MathExpression();
				}
				else return(parse(begin, i - 1, inputList) + parse(i + 1, end, inputList));
			}
			else if (inputList[i] == "-" && parentheses == 0 && (i - 1) >= begin && isValid(i - 1, inputList)) {
				if ((i + 1) > end) {
					cout << "ERROR: operator SUBTRACT doesn't find id!\n";
					return MathExpression();
				}
				else return (parse(begin, i - 1, inputList) - parse(i + 1, end, inputList));
			}
		}

		// procedure2: find "*" OR "/"
		for (int i = end; i >= begin; i--) {
			if (inputList[i] == ")") parentheses++;
			else if (inputList[i] == "(") parentheses--;
			if (inputList[i] == "*" && parentheses == 0) {
				if ((i + 1) > end || (i - 1) < begin) {
					cout << "ERROR: operator MUL doesn't find id!\n";
					return MathExpression();
				}
				else return(parse(begin, i - 1, inputList) * parse(i + 1, end, inputList));
			}
			else if (inputList[i] == "/" && parentheses == 0) {
				if ((i + 1) > end || (i - 1) < begin) {
					cout << "ERROR: operator DIVIDE doesn't find id!\n";
					return MathExpression();
				}
				return(parse(begin, i - 1, inputList) / parse(i + 1, end, inputList));
			}
		}

		// procedure3: find sign "+" OR "-"
		int sign = 1, j = begin;
		if (inputList[begin] == "+" || inputList[begin] == "-") {
			if (!eliminateSign(j, end, sign, inputList)) {
				cout << "ERROR: operator sign doesn't match!\n";
				return MathExpression();
			}
			else return parse(j, end, inputList).signConvert(sign);
		}

		// procedure4: find operator "^"
		for (int i = end; i >= begin; i--) {
			if (inputList[i] == ")") parentheses++;
			else if (inputList[i] == "(") parentheses--;
			if (inputList[i] == "^" && parentheses == 0) {
				if (((i + 1) > end) || ((i - 1) < begin)) {
					cout << "ERROR: operator EXP doesn't find id!\n";
					return MathExpression();
				}
				return exp(parse(begin, i - 1, inputList), parse(i + 1, end, inputList));
			}
		}

		// procedure5: find operator "!"
		if (inputList[end] == "!") return degree(parse(begin, end - 1, inputList));

		// procedure6: find operator "()"
		if (inputList[begin] == "(" && inputList[end] == ")") {
			if (begin + 1 == end) {
				cout << "ERROR: operator () doesn't find id!\n";
				return MathExpression();
			}
			else return(parse(begin + 1, end - 1, inputList));
		}

		cout << "Doesn't find any matched operator!\n";
		return MathExpression();
	}
};
