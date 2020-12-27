#pragma once
#ifndef POSTFIX_H
#include "stack.h"
#include "strl.h"
#define POSTFIX_H
class expression {
private:
	stack process;
	strl outstr;
	strl instr;
public:
	expression(strl infix) {
		instr = infix;
	}

	void converttopf() {
		strl temp;
		int priority = 0;
		bool flag = false;
		for (int i = 0; i <= instr.getSize(); i++) {
			if (instr.at(i) != ' ' && i != instr.getSize()) temp.add(instr.at(i));
			else {
				if (temp.isEqual ("("))
					process.push(temp);
				else if (temp.isDigit())
					outstr.add(temp);
				else if (temp.isEqual(")")) {
					while (!process.isEmpty() && !process.getTop().getValue().isEqual("(")) {
						outstr.add(process.getTop().getValue());
						process.pop();
					}
					process.pop();
				}
				else {
					if (!temp.isEqual(" ")) {
						priority = temp.getOperationpriority();
						while (!process.isEmpty() && process.getTop().getpriority() >= priority) {
							outstr.add(process.getTop().getValue());
							process.pop();
						}
						process.push(temp);
					}
				}
				temp = "";
			}
		}
		while (!process.isEmpty()) {
			outstr.add(process.getTop().getValue());
			process.pop();
		}
	}

	strl calculate() { //calculating expresultsion in postfix form
		double result = 0;
		strl temp;
		for (int i = 0; i < outstr.getSize(); i++) {
			if (outstr.at(i) != ' ') temp.add(outstr.at(i));
			else {
				if (temp.isDigit()) {
					if (temp.isEqual("pi")) temp = 3.1415926535;
					else if (temp.isEqual("e")) temp = 2.71828182846;
					process.push(temp);
				}
				else if (temp.getOperationpriority() == 4) {
					result = temp.exe(process.getTop().getValue());
					process.pop();
					process.push(result);
				}
				else {
					result = temp.exe(process.getTop().getValue(), process.getTop().getNext()->getValue());
					process.pop();
					process.pop();
					process.push(result);
				}
				temp = "";
			}
		}
		return process.getTop().getValue();
	}

	strl getOutstr() {
		return outstr;
	}



};
#endif // !POSTFIX_H