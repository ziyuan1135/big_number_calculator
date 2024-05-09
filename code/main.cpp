#include<iostream>
#include<string>
#include<sstream>
#include"MathExpression.h"
#include"NormalArithmetic.h"
#include"Parser.h"
#include"Token.h"
#include"Integer.h"
#include"Decimal.h"
#include"Basic.h"

using namespace std;
vector<string> inputList;
unordered_map<string, Token> TokenTable;

void decription() {
	cout << "�\�� : �i���|�h�B���h�B�����B��A�i�H�ŧi�ܼƶi��B��" << endl;
	cout << "�ܼƮ榡 : Set Integer/Decimal �ܼƦW�� = Number " << endl;
	cout << "�W�w : " << endl;
	cout << "	1.�ܼƫ��A��Integer�MDecimal��ءA�ݿ�J���㫬�A�W��" << endl;
	cout << "	2.�ܼƦW�٤��o������r" << endl;
	cout << "	3.�C�@��Input�ݭn�@�ӪŮ�j�}" << endl;
	cout << "Example : 1 + 1 , 100 ! , 100 ^ 5 , 100 + ( 10 * 5 ) / 5" << endl;
}

int main() {
	string line, input;
	int pos01, pos02;
	deque<int> test01, test02, result;
	MathExpression me01("12345"), me02("123.00", 3), r;
	decription();
	//parser
	while (getline(cin, line)) {
		stringstream ss(line);
		string name;
		inputList.clear();
		while (ss >> input) {
			inputList.push_back(input);
		}
		if (inputList.size() == 0) continue;
		if (inputList[0] == "Set" && inputList.size() >= 5) {
			if (inputList[1] == "Integer" || inputList[1] == "Decimal") {
				if (checkVarName(inputList[2])) {
					if (inputList[3] == "=") {
						r = Parser::parse(4, inputList.size() - 1, inputList, TokenTable);
						if (r.denominator.size() != 0) {
							TokenTable[inputList[2]] = Token(inputList[1], r);
							//cout << TokenTable[inputList[2]] << endl;
						}
					}
					else cout << "Input Error: Var must be followed by symbol of assingment(\"=\").\n\n";
				}
				else cout << "Input Error: Var name must start with alphabet and follow digits or letters (optional)\n\n";
			}
			else cout << "Input Error: Type doesn't match \"Integer\" OR \"Decimal\".\n\n";
		}
		else if (inputList.size() >= 3 && inputList[1] == "=") {
			auto search = TokenTable.find(inputList[0]);
			if (search != TokenTable.end()) {
				r = Parser::parse(2, inputList.size() - 1, inputList, TokenTable);
				if (r.denominator.size() != 0) {
					search->second = Token(search->second.type, r);
					//cout << "Modify: " << search->first << ", " << search->second << endl;
				}
			}
			else cout << "the Var name isn't found.\n\n";
		}
		else if (Parser::checkParentheses(inputList)) {
			cout << Parser::parse(0, inputList.size() - 1, inputList, TokenTable) << endl;
		}
		else cout << "parentheses doesn't match!\n\n";
	}

}
/*int main() {
	Integer x;
	Decimal y;

	//cin >> x; // 123456789
	//cin >> y; // 3.1415926

	//cout << x + y << endl;
	//cout << x - y << endl;
	//cout << x * y << endl;
	//cout << x / y << endl;

	x = "123 * 8 + 456";
	y = "- 1.0 / 3 - 45 / 13.0";

	vector<Basic*> nums;
	nums.push_back(&x);
	nums.push_back(&y);
	for (const auto& num : nums)
		cout << *num << endl;
}*/