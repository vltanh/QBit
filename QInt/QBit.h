#pragma once

#include <iomanip>
using namespace std;

class QBit {
public:
	static const int BYTESZ = 16;
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

	void setBit(int pos, int x) {

	}

	int getBit(int pos) {
	
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
			int leftover;
			int carry = 0;
			for (int i = 0; i < BYTESZ; i++) {
				leftover = res.data[i] & 1;
				res.data[i] >>= 1;
				res.data[i] ^= (-carry ^ res.data[i]) & (1UL << (TYPESZ - 1));
				carry = leftover;
			}
		}
		return res;
	}

	QBit operator >>(int k) {
		QBit res = *this;
		while (k--) {
			int leftover;
			int carry = 0;
			for (int i = BYTESZ - 1; i > -1; i--) {
				leftover = (res.data[i] & (1 << (TYPESZ - 1))) >> (TYPESZ - 1);
				res.data[i] <<= 1;
				res.data[i] ^= (-carry ^ res.data[i]) & (1UL << 0);
				carry = leftover;
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

	QBit operator &(const QBit& n) {
		QBit res = *this;
		for (int i = 0; i < BYTESZ; i++)
			res.data[i] &= n.data[i];
		return res;
	}

	QBit operator ^(const QBit& n) {
		QBit res = *this;
		for (int i = 0; i < BYTESZ; i++)
			res.data[i] ^= n.data[i];
		return res;
	}
};

