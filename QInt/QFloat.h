#pragma once

#include "QBit.h"

class QFloat : public QBit {
public:
	// Nhóm hàm khởi tạo
	QFloat() : QBit() {}
	QFloat(string);

	// Nhóm hàm phụ trợ
	bool isNegative() const;
	bool isZero() const;
	bool isNaN() const;
	bool isInf() const;

	// Nhóm các toán tử
	QFloat& operator = (const QFloat& f);
	QFloat operator + (const QFloat&);
	QFloat operator - (const QFloat&);
	QFloat operator * (const QFloat&);
	QFloat operator / (const QFloat&);

	// Nhóm hàm chuyển đổi
	string toDec();
	friend QFloat QFloatfromBin(string);
	QFloat& strDecToQFloat(string number);
	string DecToBinary();

	friend QFloat QFloatfromString(string, string);
	string toString(string);

	QFloat& fromBitStr(string);
	string toBitString();
};

QFloat QFloatfromBin(string);
QFloat QFloatfromString(string, string);