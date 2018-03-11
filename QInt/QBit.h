#pragma once

#include <iomanip>
using namespace std;

class QBit {
public:
	static const int BYTESZ = 2;
	static const int TYPESZ = 8;
protected:
	unsigned char data[BYTESZ];
public:
	QBit() {
		for (int i = 0; i < BYTESZ; i++)
			data[i] = 0;
	}

	QBit(const QBit& n) {
		for (int i = 0; i < BYTESZ; i++)
			data[i] = n.data[i];
	}

	QBit& operator =(const QBit& n) {
		for (int i = 0; i < BYTESZ; i++)
			data[i] = n.data[i];
		return (*this);
	}

	QBit operator ~() {
		QBit res = *this;
		for (int i = 0; i < BYTESZ; i++)
			res.data[i] = ~data[i];
		return res;
	}

	QBit operator <<(int k) {
		QBit res = *this;
		while (k--) {
			int leftover = 0;
			for (int i = 0; i < BYTESZ; i++) {
				res.data[i] = (res.data[i] >> 1) | leftover;
				leftover = (data[i] & 1) << (TYPESZ - 1);
			}
		}
		return res;
	}

	QBit operator >>(int k) {
		QBit res = *this;
		while (k--) {
			int leftover = 0;
			for (int i = BYTESZ - 1; i > -1; i--) {
				res.data[i] = (res.data[i] << 1) | leftover;
				leftover = (data[i] & (1 << (TYPESZ - 1))) >> (TYPESZ - 1);
			}
		}
		return res;
	}

	QBit operator |(const QBit& n) {
		QBit res = *this;
		for (int i = 0; i < BYTESZ; i++)
			res.data[i] |= n.data[i];
		return res;
	}

	virtual string toDec();
	virtual string toBin();
	virtual string toHex();

	virtual void print() {
		cout << setw(10) << right;
		cout << toDec() << '\t' << toBin() << '\t' << toHex() << endl;
		cout << left;
	}

	virtual void input();
};

