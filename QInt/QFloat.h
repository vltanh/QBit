#pragma once

#include "QBit.h"

class QFloat : public QBit {
public:
	// Nhóm hàm khởi tạo
	QFloat() : QBit() {}

	// Nhóm hàm phụ trợ
	bool isNegative() const;
	bool isZero() const;

	// Nhóm các toán tử
	QFloat& operator = (const QFloat& f);
	QFloat operator + (const QFloat&);
	QFloat operator - (const QFloat&);
	QFloat operator * (const QFloat&);
	QFloat operator / (const QFloat&);

	// Nhóm hàm chuyển đổi
	string toDec();
	friend QFloat QFloatfromBin(string);
	void strDecToQFloat(string number);
	string DecToBinary();
};

QFloat QFloatfromBin(string);