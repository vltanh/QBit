#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "QBit.h"
#include "QInt.h"
#include "Float.h"

int main() {
	cout << QBit::BYTESZ << " byte(s)" << endl;
	/*for (int i = -100; i < 100; i++) {
		cout << "Dec: \t";
		string s = to_string(i);
		cout << s << endl;
		QInt a = fromDec(s);
		string bin = a.toBin();
		string hex = a.toHex();
		string dec = fromHex(hex).toDec();
		cout << "Bin: \t" << bin << endl;
		cout << "Hex: \t" << hex << endl;
		cout << "Dec: \t" << dec << endl;
		cout << endl;
	}*/

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
	cout << "r:"; (a / b).second.print();*/

	string s1, s2;
	cin >> s1 >> s2;
	Float f1(s1), f2(s2);
	(f1 + f2).print(); cout << endl;
	(f1 - f2).print(); cout << endl;
	f2.doubled().print(); cout << endl;
	f2.halved().print(); cout << endl;
}