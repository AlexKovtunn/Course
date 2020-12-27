#include <fstream>
#include <iostream>
#include "strl.h"
#include "transformationtopostfix.h"


using namespace std;

int main() {
	fstream input, output;
	input.open("input.txt", ios::in);
	output.open("output.txt", ios::out);
	strl infix;
	infix.input(input);
	infix.output(output);
	if (infix.checkinfix(output)) {
		expression postfix(infix);
		output << "\nConverted expression in Postfix form: ";
		postfix.getOutstr().output(output);
		output << "= ";
		postfix.calculate().output(output);
	}
	output.close();
	input.close();
	return 0;
}