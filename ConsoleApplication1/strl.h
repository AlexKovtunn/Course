#pragma once
#include <fstream>
#include <cmath>
#ifndef STRL_H
#define STRL_H
const int N = 128;
using namespace std;
class strl {
private:
	char arr[N];
	size_t size;
public:
	strl() {
		size = 0;
	}

	strl(const char mass[N]) {
		size = 0;
		while (size < N && arr[size] != '\0') arr[size] = mass[size++];
	}

	strl(double value) { //parsing double to string using sprintf
		char temp[N];
		sprintf_s(temp, "%f", value);
		int i = 0;
		while (i < N && ((temp[i] >= '0' && temp[i] <= '9') || temp[i] == '.' || temp[i] == '-'))
			arr[i] = temp[i++];
		size = i;
	}

	char at(int i) {
		return arr[i];
	}

	void add(strl plus){
		for (size_t i = 0; i < plus.getSize(); i++)
			arr[size + i] = plus.arr[i];
		size += plus.getSize() + 1;
		arr[size - 1] = ' ';
	}

	bool isEqual(strl comparable) {
		if (size != comparable.size) return false;
		for (int i = 0; i < size; i++)
			if (arr[i] != comparable.arr[i]) return false;
		return true;
	}

	size_t getSize() {
		return size;
	}

	void input(fstream& f) {
		size = 0;
		char s = ' ';
		f >> noskipws;
		while (!f.eof()) {
			f >> s;
			if (s != '\n' && !f.eof()) arr[size++] = s;
			else break;
		}
	}

	void output(fstream& f) {
		int i = 0;
		while (i < size) f << arr[i++];
	}

	bool isDigit() {
		if ((arr[0] >= '0' && arr[0] <= '9') || isEqual("pi") || isEqual("e")) return true;
		else if (arr[0] == '-' && arr[1] >= '0' && arr[1] <= '9') return true;
		else return false;
	}

	bool isOperation() {
		if (getOperationpriority() == -1) return false;
		else return true;
	}

	int getOperationpriority() {
		if (isEqual("(") || isEqual(")")) return 0;
		else if (isEqual("+") || isEqual("-")) return 1;
		else if (isEqual("*") || isEqual("/") || isEqual("%")) return 2;
		else if (isEqual("^")) return 3;
		else if (isEqual("cos") || isEqual("sin") || isEqual("tg") || isEqual("ctg") || isEqual("ln") || isEqual("log") || isEqual("sqrt")) return 4;
		else return -1;
	}

	double exe(strl first_operand) { //carrying out operations with single operand
		double operand = atof(first_operand.arr);
		if (isEqual("cos")) return cos(operand);
		if (isEqual("sin")) return sin(operand);
		if (isEqual("tg")) return tan(operand);
		if (isEqual("ctg")) return 1 / tan(operand);
		if (isEqual("ln")) return log(operand);
		if (isEqual("log")) return log10(operand);
		if (isEqual("sqrt")) return sqrt(operand);
	}

	double exe(strl first_operand, strl second_operand) { //carrying out operations with 2 operands
		double second = atof(first_operand.arr); // in case we are taking two operands they already swapped in stack
		double first = atof(second_operand.arr); // we need to swap them again
		if (isEqual("+")) return first + second;
		if (isEqual("-")) return first - second;
		if (isEqual("*")) return first * second;
		if (isEqual("/")) return first / second;
		if (isEqual("%")) return fmod(first, second);
		if (isEqual("^")) return pow(first, second);
	}

	bool checkinfix(fstream& toOut) {
		int bracketsCount = 0;
		strl cur;
		for (int i = 0; i <= size; i++) {
			if (arr[i] != ' ' && i != size) cur.add(arr[i]);
			else {
				if (!cur.isOperation() && !cur.isDigit()) {
					toOut << "\nUnknown character detected at " << i << " position is ";
					cur.output(toOut);
					return false;
				}
				else {
					if (cur.isEqual("(")) bracketsCount += 1;
					else if (cur.isEqual(")")) {
						if (bracketsCount > 0) bracketsCount -= 1;
						else {
							toOut << "\nIncorrect placement of brackets";
							return false;
						}
					}
				}
				cur = "";
			}
		}
		if (!bracketsCount) return true;
		else {
			toOut << "\nIncorrect placement of brackets";
			return false;
		}
	}

};
#endif // !STRL_H