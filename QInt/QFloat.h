#pragma once

#include "QBit.h"
#include "Float.h"

class QFloat : public QBit {
private:
	static const int S;
	static const int E;
public:
	QFloat() : QBit() {}

	QFloat(const QFloat& n) : QBit(n) {}
	QFloat(const QBit& n) : QBit(n) {}

	string toDec();
	QFloat fromDec(string);

	string toBin();
	QFloat fromBin(string);

	QFloat& operator =(const QFloat& n) {
		QBit::operator=(n);
		return (*this);
	}

	QFloat operator +(const QFloat&);
	QFloat operator -(const QFloat&);
	//pair<QInt, QInt> operator *(const QInt&);
	//pair<QInt, QInt> operator /(const QInt&);

	QFloat operator !();
	bool neg();
};