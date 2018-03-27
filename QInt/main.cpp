#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
using namespace std;

#include "QBit.h"
#include "QInt.h"

string operate(const vector<string>& opt) {
	if (opt[2] == ">>" || opt[2] == "<<") {
		QInt a = fromString(opt[1], opt[0]);
		int b = stoi(opt[3]);

		if (opt[2] == ">>") return static_cast<QInt>(a >> b).toString(opt[0]);
		if (opt[2] == "<<") return static_cast<QInt>(a << b).toString(opt[0]);
	}
	else if (opt[1] == "~") {
		QInt a = fromString(opt[2], opt[0]);
		return static_cast<QInt>(~a).toString(opt[0]);
	}
	else {
		QInt a, b;
		a = fromString(opt[1], opt[0]);
		b = fromString(opt[3], opt[0]);

		if (opt[2] == "+") return (a + b).toString(opt[0]);
		if (opt[2] == "-") return (a - b).toString(opt[0]);
		if (opt[2] == "*") return (a * b).second.toString(opt[0]);
		if (opt[2] == "/") return (a / b).first.toString(opt[0]);
		if (opt[2] == "&") return static_cast<QInt>(a & b).toString(opt[0]);
		if (opt[2] == "|") return static_cast<QInt>(a | b).toString(opt[0]);
		if (opt[2] == "^") return static_cast<QInt>(a ^ b).toString(opt[0]);
	}
}

string convert(const vector<string>& opt) {
	QInt n = fromString(opt[2], opt[0]);
	return n.toString(opt[1]);
}

int main(int argc, char** argv) {
	ifstream inp(argv[1]);
	ofstream out(argv[2]);

	//ifstream inp("input.txt");
	//ofstream out("output.txt");

	string cmd;
	while (getline(inp, cmd)) {
		vector<string> opt;
		size_t pos = 0;
		while ((pos = cmd.find(" ")) != string::npos) {
			opt.push_back(cmd.substr(0, pos));
			cmd.erase(0, pos + 1);
		}
		opt.push_back(cmd);
		
		if (opt.size() == 4 || opt[1] == "~")
			out << operate(opt) << endl;
		else if (opt.size() == 3)
			out << convert(opt) << endl;
	}
}