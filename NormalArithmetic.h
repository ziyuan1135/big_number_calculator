#pragma once
#include<iostream>
#include<deque>
using namespace std;

class NormalArithmetic {
public:
	static deque<int> mulR(const deque<int>& num01, const deque<int>& num02) {
		deque<int> result;
		int size = num01.size() + num02.size() - 1, carry = 0;
		for (int i = 0; i < size; i++) result.push_back(0);
		for (int i = 0; i < num01.size(); i++) {
			if (num01[i] == 0)continue;
			for (int j = 0; j < num02.size(); j++) {
				result[i + j] = result[i + j] + num01[i] * num02[j];
			}
		}
		for (int i = 0; i < size; i++) {
			result[i] += carry;
			carry = result[i] / 10;
			result[i] %= 10;
		}
		if (carry != 0) result.push_back(carry);
		return result;
	}
	static void mul(const deque<int>& deno01, const deque<int>& deno02, deque<int>& resultDeno) {
		int size = deno01.size() + deno02.size() - 1, carry = 0;
		if ((deno01.size() == 1 && deno01[0] == 0) || (deno02.size() == 1 && deno02[0] == 0)) {
			resultDeno.push_back(0);
			return;
		}
		for (int i = 0; i < size; i++) resultDeno.push_back(0);
		for (int i = 0; i < deno01.size(); i++) {
			if (deno01[i] == 0) continue;
			for (int j = 0; j < deno02.size(); j++) {
				resultDeno[i + j] = resultDeno[i + j] + deno01[i] * deno02[j];
			}
		}
		for (int i = 0; i < size; i++) {
			resultDeno[i] += carry;
			carry = resultDeno[i] / 10;
			resultDeno[i] %= 10;
		}
		if (carry != 0) resultDeno.push_back(carry);
	}
	static void add(const deque<int>& num01, const deque<int>& num02, deque<int>& resultNum) {
		int size, carry = 0, sum;
		if (num01.size() > num02.size()) size = num01.size();
		else size = num02.size();
		for (int i = 0; i < size; i++) {
			if (i >= num01.size()) sum = num02[i] + carry;
			else if (i >= num02.size()) sum = num01[i] + carry;
			else sum = num01[i] + num02[i] + carry;
			carry = sum / 10;
			sum %= 10;
			resultNum.push_back(sum);
		}
		if (carry != 0) resultNum.push_back(carry);
	}
	static bool isGreaterOrEqual(const deque<int>& lhs, const deque<int>& rhs) {
		if (lhs.size() > rhs.size()) return true;
		else if (lhs.size() < rhs.size()) return false;
		else {
			for (int i = lhs.size() - 1; i >= 0; i--) {
				if (lhs[i] > rhs[i]) return true;
				else if (lhs[i] < rhs[i]) return false;
			}
		}
		return true;
	}
	static void subtract(const deque<int>& num01, const deque<int>& num02, deque<int>& resultNum) {
		int borrow = 0, sum;
		for (int i = 0; i < num01.size(); i++) {
			if (i >= num02.size()) sum = num01[i] - borrow;
			else sum = num01[i] - num02[i] - borrow;
			if (sum < 0) {
				sum += 10;
				borrow = 1;
			}
			else borrow = 0;
			resultNum.push_back(sum);
		}
		while (resultNum.back() == 0 && resultNum.size() != 1) resultNum.pop_back();
	}
	static void Dmul(const deque<int>& num, const int& k, deque<int>& result) {
		int sum, carry = 0;
		for (int i = 0; i < num.size(); i++) {
			sum = num[i] * k + carry;
			carry = sum / 10;
			sum %= 10;
			result.push_back(sum);
		}
		if (carry != 0) result.push_back(carry);
	}
	static deque<int> Dsubtract(const deque<int>& num01, const deque<int>& num02) {
		deque<int> result;
		int borrow = 0, sum;
		for (int i = 0; i < num01.size(); i++) {
			if (i >= num02.size()) sum = num01[i] - borrow;
			else sum = num01[i] - num02[i] - borrow;
			if (sum < 0) {
				sum += 10;
				borrow = 1;
			}
			else borrow = 0;
			result.push_back(sum);
		}
		while (result.back() == 0 && result.size() != 1) result.pop_back();
		return result;
	}
	static void divide(const deque<int>& num01, const deque<int>& num02, deque<int>& resultNum, int& decPos) {
		deque<int> currentDividen;
		int count = -1, it = num01.size() - 1;
		bool decPoint = false;
		while (!isGreaterOrEqual(currentDividen, num02)) {
			if (it >= 0) currentDividen.push_front(num01[it--]);
			else {
				currentDividen.push_front(0);
				resultNum.push_back(0);
				if (!decPoint) decPos = resultNum.size();
				decPoint = true;
				count++;
			}
			if (currentDividen.back() == 0) currentDividen.pop_back();
			if (count == 100) return;
		}
		while (count < 100) {
			if (isGreaterOrEqual(currentDividen, num02)) {
				for (int i = 9; i > 0; i--) {
					deque<int> temp;
					Dmul(num02, i, temp);
					if (isGreaterOrEqual(currentDividen, temp)) {
						currentDividen = Dsubtract(currentDividen, temp);
						resultNum.push_back(i);
						break;
					}
				}
			}
			else resultNum.push_back(0);
			if (it >= 0) currentDividen.push_front(num01[it--]);
			else {
				currentDividen.push_front(0);
				if (!decPoint) decPos = resultNum.size();
				decPoint = true;
			}
			if (decPoint) count++;
			if (currentDividen.back() == 0) currentDividen.pop_back();
		}
	}
	static void divideInt(const deque<int>& num01, const deque<int>& num02, deque<int>& resultNum) {
		deque<int> currentDividen;
		int it = num01.size() - 1;
		while (!isGreaterOrEqual(currentDividen, num02)) {
			if (it >= 0) currentDividen.push_front(num01[it--]);
			else {
				resultNum.push_back(0);
				return;
			}
		}
		while (true) {
			if (isGreaterOrEqual(currentDividen, num02)) {
				for (int i = 9; i > 0; i--) {
					deque<int> temp;
					Dmul(num02, i, temp);
					if (isGreaterOrEqual(currentDividen, temp)) {
						currentDividen = Dsubtract(currentDividen, temp);
						resultNum.push_front(i);
						break;
					}
				}
			}
			else resultNum.push_front(0);
			if (it >= 0) currentDividen.push_front(num01[it--]);
			else break;
			if (currentDividen.back() == 0) currentDividen.pop_back();
		}
	}
	static bool modIsZero(const deque<int>& num01, const deque<int>& num02, deque<int>& resultNum) {
		deque<int> currentDivden;
		int it = num01.size() - 1;
		if (num01.size() == 1 && num01.back() == 0) {
			resultNum.push_back(0);
			return true;
		}
		while (!isGreaterOrEqual(currentDivden, num02)) {
			if (it >= 0) currentDivden.push_front(num01[it--]);
			else {
				resultNum.push_back(0);
				return false;
			}
		}
		while (true) {
			if (isGreaterOrEqual(currentDivden, num02)) {
				for (int i = 9; i > 0; i--) {
					deque<int> temp;
					Dmul(num02, i, temp);
					if (isGreaterOrEqual(currentDivden, temp)) {
						currentDivden = Dsubtract(currentDivden, temp);
						resultNum.push_front(i);
						break;
					}
				}
			}
			else resultNum.push_front(0);
			if (it >= 0) currentDivden.push_front(num01[it--]);
			else {
				if (currentDivden.size() == 1 && currentDivden.back() == 0) return true;
				return false;
			}
			if (currentDivden.back() == 0) currentDivden.pop_back();
		}
	}
	static bool isGreater(const deque<int>& num01, const deque<int>& num02) {
		if (num01.size() > num02.size()) return true;
		else if (num01.size() < num02.size()) return false;
		else {
			for (int i = num01.size() - 1; i >= 0; i--) {
				if (num01[i] != num02[i]) return (num01[i] > num02[i]);
			}
		}
		return false;
	}
	static void increaseOne(deque<int>& num) {
		int carry = 1, it = 0;
		while (carry == 1) {
			num[it] += carry;
			if (num[it] >= 10) {
				num[it++] -= 10;
				carry = 1;
			}
			else carry = 0;
			if (it > num.size() - 1) break;
		}
		if (carry != 0) num.push_back(carry);
	}
};