#pragma once

#include "QBit.h"
#include "Int.h"

class QInt : public QBit {
public:
	// Nhóm hàm khởi tạo
	QInt() : QBit() {}
	QInt(const QInt& n) : QBit(n) {}
	QInt(const QBit& n) : QBit(n) {}
	QInt(int n);
	QInt(const Int&);

	// Nhóm hàm biểu diễn ở các hệ cơ số dưới dạng chuỗi
	string toDec() const;
	string toBin() const;
	string toHex() const;
	string toString(string) const;

	// Nhóm hàm nhập vào từ các hệ cơ số dưới dạng chuỗi
	friend QInt fromDec(string);
	friend QInt fromBin(string);
	friend QInt fromHex(string);
	friend QInt fromString(string, string);

	// Nhóm các toán tử
	QInt& operator =(const QInt& n);
	QInt operator +(const QInt&) const;
	QInt operator -(const QInt&) const;
	pair<QInt,QInt> operator *(const QInt&) const;
	pair<QInt,QInt> operator /(const QInt&) const;
	QInt operator !() const;

	// Nhóm hàm phụ trợ khác
	bool isNegative() const;
	bool isZero() const;
};

QInt fromBin(string);
QInt fromDec(string);
QInt fromHex(string);
QInt fromString(string, string);