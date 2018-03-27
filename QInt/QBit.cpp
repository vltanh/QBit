#include "QBit.h"

//  -------------------
// | Nhóm hàm khởi tạo |
//  -------------------

// Khởi tạo mặc định bằng 0
QBit::QBit() {
	for (int i = 0; i < BYTESZ; i++)
		data[i] = 0;
}

// Khởi tạo sao chép
QBit::QBit(const QBit& n) {
	for (int i = 0; i < BYTESZ; i++)
		data[i] = n.data[i];
}

//  ------------------
// | Nhóm hàm phụ trợ |
//  ------------------

// Hàm đặt bit tại vị trí pos (từ 0, trái qua)
void QBit::setBit(int pos, int bit) {
	int dataId = pos / TYPESZ;
	int bitId = pos % TYPESZ;
	data[dataId] ^= (-bit ^ data[dataId]) & (1UL << (TYPESZ - 1 - bitId));
}

// Hàm lấy bit tại vị trí pos (từ 0, trái qua)
int QBit::getBit(int pos) const {
	int dataId = pos / TYPESZ;
	int bitId = pos % TYPESZ;
	if (dataId < 0 || dataId >= BYTESZ) return 0;
	return (data[dataId] >> (TYPESZ - 1 - bitId)) & 1;
}

//  ------------------
// | Nhóm các toán tử |
//  ------------------

// Toán tử gán =
QBit& QBit::operator =(const QBit& n) {
	for (int i = 0; i < BYTESZ; i++)
		data[i] = n.data[i];
	return (*this);
}

// Phép dịch trái
QBit QBit::operator <<(int k) const {
	QBit res = *this;
	for (int i = 0; i < BYTESZ*TYPESZ; i++)
		res.setBit(i, getBit(i - k));
	return res;
}

// Phép dịch phải
QBit QBit::operator >>(int k) const {
	QBit res = *this;
	for (int i = 0; i < BYTESZ*TYPESZ; i++)
		res.setBit(i, getBit(i + k));
	return res;
}

// Hàm not (nghịch đảo mọi bit)
QBit QBit::operator ~() const {
	QBit res = *this;
	for (int i = 0; i < BYTESZ; i++)
		res.data[i] = ~data[i];
	return res;
}

// Hàm or
QBit QBit::operator |(const QBit& n) const {
	QBit res = *this;
	for (int i = 0; i < BYTESZ; i++)
		res.data[i] |= n.data[i];
	return res;
}

// Hàm and
QBit QBit::operator &(const QBit& n) const {
	QBit res = *this;
	for (int i = 0; i < BYTESZ; i++)
		res.data[i] &= n.data[i];
	return res;
}

// Hàm xor
QBit QBit::operator ^(const QBit& n) const {
	QBit res = *this;
	for (int i = 0; i < BYTESZ; i++)
		res.data[i] ^= n.data[i];
	return res;
}