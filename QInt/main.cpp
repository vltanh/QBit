#define _CRT_SECURE_NO_WARNINGS

//#define TEST
#define QFLOAT
//#define QINT

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
using namespace std;

#include "QInt.h"
#include "QFloat.h"

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

#ifdef QINT
int main(int argc, char** argv) {
	//ifstream inp(argv[1]);
	//ofstream out(argv[2]);

	ifstream inp("input_test.txt");
	ofstream out("output.txt");

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
#endif

#ifdef QFLOAT

int main() {
	string s1, s2;
	cin >> s1 >> s2;
	//QFloat a = QFloatfromBin(s1);
	//QFloat b = QFloatfromBin(s2);
	QFloat a, b;
	//a.strDecToQFloat(s1);
	//b.strDecToQFloat(s2);
	a = QFloatfromBin(s1);
	b = QFloatfromBin(s2);
	cout << a.toDec() << endl;
	cout << b.toDec() << endl;
	//QFloat c = a + b;
	//QFloat aa = QFloatfromBin(a.DecToBinary());
	//QFloat bb = QFloatfromBin(b.DecToBinary());
	//cout << aa.toDec() << endl;
	//cout << bb.toDec() << endl;
	cout << (a*b).DecToBinary() << endl;
	cout << (a * b).toDec() << endl;
}

#endif

#ifdef TEST

#include <time.h>
#include <random>

int main() {
	ofstream out("input_test.txt");
	srand(time(NULL));

	vector<string> base = { "2", "10", "16" };
	vector<vector<string>> radix = { {"0", "1"},
										{"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"},
									{ "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F" } };
	vector<int> maxlen = { 128, 32, 30 };
	vector<string> ope = { "+", "-", "*", "/", "<<", ">>", "~", "^", "&", "|" };

	for (int i = 0; i < 100; i++) {
		if (rand() % 2) {
			int p = rand() % 3;
			int opt = rand() % ope.size();
			if (ope[opt] == ">>" || ope[opt] == "<<") {
				string res1;
				int length = (rand() % 2) ? (maxlen[p] / 2 + rand() % (maxlen[p] / 2)) : maxlen[p];
				if (p == 1 && rand() % 2) res1 += "-";
				while (length--)
					res1 = res1 + radix[p][rand() % radix[p].size()];

				out << base[p] << " " << res1 << " " << ope[opt] << " " << rand() % 10 << endl;
			}
			else if (ope[opt] == "~") {
				string res1;
				int length = (rand() % 2) ? (maxlen[p] / 2 + rand() % (maxlen[p] / 2)) : maxlen[p];
				if (p == 1 && rand() % 2) res1 += "-";
				while (length--)
					res1 = res1 + radix[p][rand() % radix[p].size()];

				out << base[p] << " " << ope[opt] << " " << res1 << endl;
			}
			else {
				string res1;
				int length = (rand() % 2) ? (maxlen[p] / 2 + rand() % (maxlen[p] / 2)) : maxlen[p];
				if (p == 1 && rand() % 2) res1 += "-";
				while (length--)
					res1 = res1 + radix[p][rand() % radix[p].size()];

				string res2;
				length = (rand() % 2) ? (maxlen[p] / 2 + rand() % (maxlen[p] / 2)) : maxlen[p];
				if (p == 1 && rand() % 2) res2 += "-";
				while (length--)
					res2 = res2 + radix[p][rand() % radix[p].size()];

				out << base[p] << " " << res1 << " " << ope[opt] << " " << res2 << endl;
			}
		}
		else {
			int p1 = rand() % 3;
			int p2 = rand() % 3;
			while (p2 == p1) p2 = rand() % 3;
			out << base[p1] << " " << base[p2] << " ";
			string res;
			int length = (rand() % 2) ? (maxlen[p1] / 2 + rand() % (maxlen[p1] / 2)) : maxlen[p1];
			if (p1 == 1 && rand() % 2) res += "-";
			while (length--)
				res = res + radix[p1][rand() % radix[p1].size()];
			out << res << endl;
		}
	}
}

#endif