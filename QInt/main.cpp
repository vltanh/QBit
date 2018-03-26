#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
using namespace std;

#include "QBit.h"
#include "QInt.h"
#include "Float.h"

string operate(const vector<string>& opt) {
	if (opt[2] == ">>" || opt[2] == "<<") {
		QInt a = fromString(opt[1], opt[0]);
		int b = stoi(opt[3]);

		if (opt[2] == ">>") return static_cast<QInt>(a >> b).toString(opt[0]);
		if (opt[2] == "<<") return static_cast<QInt>(a << b).toString(opt[0]);
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

	string cmd;
	while (getline(inp, cmd)) {
		vector<string> opt;
		size_t pos = 0;
		while ((pos = cmd.find(" ")) != string::npos) {
			opt.push_back(cmd.substr(0, pos));
			cmd.erase(0, pos + 1);
		}
		opt.push_back(cmd);
		
		if (opt.size() == 4)
			out << operate(opt) << endl;
		else if (opt.size() == 3)
			out << convert(opt) << endl;
	}

	/*cout << QBit::BYTESZ << " byte(s)" << endl;
	cout << "Input: ";
	string s;
	cin >> s;
	QInt a = fromHex(s);
	string bin = a.toBin();
	string hex = a.toHex();
	string dec = fromHex(hex).toDec();
	cout << "Bin: \t" << bin << endl;
	cout << "Hex: \t" << hex << endl;
	cout << "Dec: \t" << dec << endl;
	cout << endl;*/

	/*QInt a, b;
	string s1, s2;
	cin >> s1 >> s2;
	a = fromDec(s1); b = fromDec(s2);
	cout << "a:"; a.print();
	cout << "b:"; b.print();
	cout << "--------------------------------------------------" << endl;
	cout << "+:"; (a + b).print();
	cout << "-:"; (a - b).print();
	cout << "*:"; (a * b).second.print();
	cout << "/:"; (a / b).first.print();
	cout << "r:"; (a / b).second.print();
	cout << "l:"; static_cast<QInt>(a << 2).print();
	cout << "r:"; static_cast<QInt>(a >> 2).print();
	cout << "&:"; static_cast<QInt>(a & b).print();
	cout << "|:"; static_cast<QInt>(a | b).print();
	cout << "^:"; static_cast<QInt>(a ^ b).print();
	cout << "~:"; static_cast<QInt>(~a).print();
	cout << "~:"; static_cast<QInt>(~b).print();*/

	/*string s1, s2;
	cin >> s1 >> s2;
	Float f1(s1), f2(s2);
	(f1 + f2).print(); cout << endl;
	(f1 - f2).print(); cout << endl;
	f2.doubled().print(); cout << endl;
	f2.halved().print(); cout << endl;*/
}