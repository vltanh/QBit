#pragma once

#include "QBit.h"
#include "Int.h"

class QInt : public QBit {
public:
	QInt() : QBit() {}

	QInt(const QInt& n) : QBit(n) {}
	QInt(const QBit& n) : QBit(n) {}
	QInt(int n);

	string toDec();
	friend QInt fromDec(string);

	string toBin();
	friend QInt fromBin(string);

	string toHex();
	friend QInt fromHex(string);

	void input();

	QInt& operator =(const QInt& n) {
		QBit::operator=(n);
		return (*this);
	}

	QInt operator +(const QInt&);
	QInt operator -(const QInt&);
	pair<QInt,QInt> operator *(const QInt&);
	pair<QInt,QInt> operator /(const QInt&);

	QInt operator !() const {
		QInt res = *this;
		if (res.data[BYTESZ - 1] & 1)
			res = QInt(~res) + QInt(1);
		return res;
	}

	bool neg() const {
		return data[BYTESZ - 1] & 1;
	}
};

pair<QInt,QInt> QInt::operator *(const QInt& n) {
	QInt A = QInt();
	QInt Q = *this;
	int q = 0;
	QInt M = n;

	for (int i = 0; i < TYPESZ*BYTESZ; i++) {
		if (((Q.data[0] >> (TYPESZ - 1)) & 1) ^ q) {
			if (q) A = A + M;
			else A = A - M;
		}
		int carry =  (A.data[0] >> (TYPESZ - 1)) & 1;

		int arith = A.data[BYTESZ - 1] & 1;
		A = (A >> 1);
		A.data[BYTESZ - 1] |= arith;

		q = (Q.data[0] >> (TYPESZ - 1)) & 1;
		Q = (Q >> 1);
		Q.data[BYTESZ - 1] |= carry;
	}

	return { A, Q };
}

pair<QInt,QInt> QInt::operator /(const QInt& n) {
	QInt A = QInt();
	QInt M = !n;
	QInt Q = !(*this);

	bool sign = n.neg() ^ neg();

	for (int i = 0; i < TYPESZ*BYTESZ; i++) {
		// Shift left [A,Q]
		int carry = Q.data[BYTESZ - 1] & 1;	//Save Q first bit
		A = A << 1;						
		A.data[0] |= carry << (TYPESZ - 1);	//Shift left A and set carry last bit
		Q = Q << 1;
		
		A = A - M;
		
		if (A.data[BYTESZ - 1] & 1) {	// If A < 0
			Q.data[0] &= ~(1 << (TYPESZ - 1));
			A = A + M;
		}
		else {
			Q.data[0] |= (1 << (TYPESZ - 1));
		}
	}

	if (sign) Q = QInt(~Q) + QInt(1);
	return { Q, A };
}

// Convert from Binary to QInt
// Input: string of '0's and '1's
// Output: QInt
QInt fromBin(string bin) {
	QInt res;
	for (int i = 0; i < QBit::TYPESZ * QBit::BYTESZ; i++) {
		int dataId = QBit::BYTESZ - 1 - i / QBit::TYPESZ;
		int bitId = i % QBit::TYPESZ;
		res.data[dataId] = res.data[dataId] | ((bin[i] - '0') << bitId);
	}
	return res;
}

// Convert from QInt to Binary
// Input: QInt
// Output: string of '0's and '1's
string QInt::toBin() {
	string res(TYPESZ*BYTESZ, '0');
	for (int i = 0; i < TYPESZ*BYTESZ; i++) {
		int dataId = BYTESZ - 1 - i / TYPESZ;
		int bitId = i % TYPESZ;
		res[i] = ((data[dataId] >> bitId) & 1) + '0';
	}
	return res;
}

// Convert from Hexadecimal to QInt
// Input: string of hexadecimal ('0' to '9' and 'A' or 'a' to 'F' or 'f')
// Output: QInt
QInt fromHex(string hex) {
	for (int i = 0; i < hex.size(); i++)
		if (hex[i] <= 'z' && hex[i] >= 'a')
			hex[i] = hex[i] - 'a' + 'A';

	QInt res;
	for (int i = 0; i < hex.size(); i++) {
		int n = (hex[i] >= '0' && hex[i] <= '9') ? (hex[i] - '0') : (hex[i] - 'A' + 10);
		for (int j = 0; j < 4; j++) {
			int bit = n % 2;
			int pos = 4 * i + (4 - j - 1);
			int dataId = QBit::BYTESZ - 1 - pos / QBit::TYPESZ;
			int bitId = pos % QBit::TYPESZ;
			res.data[dataId] = res.data[dataId] | (bit << bitId);
			n = n / 2;
		}
	}
	return res;
}

// Convert from QInt to Hexadecimal
// Input: QInt
// Output: string of hexadecimal ('0' to '9' and 'A' or 'a' to 'F' or 'f')
string QInt::toHex() {
	string dict(16, 0);
	for (int i = 0; i < 10; i++)
		dict[i] = i + '0';
	for (int i = 10; i < 16; i++)
		dict[i] = i - 10 + 'A';

	string res((TYPESZ * BYTESZ) >> 2, '0');
	for (int i = 0; i < res.size(); i++) {
		int val = 0;
		for (int j = 0; j < 4; j++) {
			int pos = 4 * i + (4 - j - 1);
			int dataId = BYTESZ - 1 - pos / 8;
			int bitId = pos % 8;
			int bit = ((data[dataId] >> bitId) & 1);

			val += (bit << j);
		}
		res[i] = dict[val];
	}
	return res;
}

string QInt::toDec() {
	Int res;
	res = res - (Int(data[BYTESZ - 1] & 1) << (TYPESZ*BYTESZ - 1));
	for (int i = 1; i < TYPESZ*BYTESZ; i++) {
		int dataId = BYTESZ - 1 - i / TYPESZ;
		int bitId = i % TYPESZ;
		int bit = ((data[dataId] >> bitId) & 1);
		res = res + (Int(bit) << (TYPESZ*BYTESZ - i - 1));
	}

	string a = string(res);
	if (a.size() == 0) a = "0";
	return a;
}

QInt fromDec(string s) {
	Int dec(s);
	int r;
	int i = 0;
	string bin;

	bool sign = dec.neg();

	QInt res;
	for (int i = 0; i < QBit::TYPESZ*QBit::BYTESZ; i++) {
		dec = dec.halved(r);
		int dataId = i / QBit::TYPESZ;
		int bitId = i % QBit::TYPESZ;
		res.data[dataId] |= (r << (QBit::TYPESZ - 1 - bitId));
	}

	if (sign) res = QInt(~res) + fromDec("1");
	return res;
}

QInt QInt::operator +(const QInt& b) {
	QInt c;
	int leftover = 0;
	for (int i = 0; i < TYPESZ*BYTESZ; i++) {
		int dataId = i / TYPESZ;
		int bitId = i % TYPESZ;
		leftover = leftover + ((data[dataId] >> (TYPESZ - 1 - bitId)) & 1) + ((b.data[dataId] >> (TYPESZ - 1 - bitId)) & 1);
		c.data[dataId] = c.data[dataId] | ((leftover % 2) << (TYPESZ - 1 - bitId));
		leftover = leftover / 2;
	}
	return c;
}

QInt QInt::operator -(const QInt& b) {
	QInt c = b;
	return (*this) + (QInt(~c) + fromDec("1"));
}

void QInt::input() {
	string s;
	cin >> s;
	QInt c = fromDec(s);
	for (int i = 0; i < BYTESZ; i++)
		data[i] = c.data[i];
}

QInt::QInt(int n) { operator=(fromDec(to_string(n))); }