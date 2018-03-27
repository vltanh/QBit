#pragma once

#include <iomanip>
using namespace std;

class QBit {
public:
	static const int BYTESZ = 16;	// Kích thước số nguyên (16 bytes)
	static const int TYPESZ = 8;	// Kích thước một phần tử lưu trữ (unsigned char: 1 bytes)
protected:
	unsigned char data[BYTESZ];	// Lưu trữ 128 bit bằng 16 unsigned char * 8 bit
public:
	// Nhóm hàm khởi tạo
	QBit();
	QBit(const QBit& n);

	// Nhóm hàm phụ trợ
	void setBit(int pos, int bit);
	int getBit(int pos) const;

	// Nhóm toán tử
	QBit& operator =(const QBit& n);
	QBit operator <<(int k) const;
	QBit operator >>(int k) const;
	QBit operator ~() const;
	QBit operator |(const QBit& n) const;
	QBit operator &(const QBit& n) const;
	QBit operator ^(const QBit& n) const;
};

