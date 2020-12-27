#pragma once
#include "strl.h"
#ifndef element_H
#define element_H
class element {
private:
	strl value;
	int priority;
	element* next;
public:
	element(strl element_value, element* element_next) {
		value = element_value;
		next = element_next;
		priority = element_value.getOperationpriority();
	}

	element(double value, element* element_next) {
		value = value;
		next = element_next;
		priority = -1;
	}

	int getpriority() {
		return priority;
	}

	strl getValue() {
		return value;
	}

	~element() {

	}

	bool isBracket() {
		if (value.isEqual("(") || value.isEqual(")")) return true;
		else return false;
	}

	element* getNext() {
		return next;
	}
};
#endif // !element_H