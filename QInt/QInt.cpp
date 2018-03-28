#include "QInt.h"

//  -------------------
// | Nhóm hàm khởi tạo |
//  -------------------

// Khởi tạo từ số nguyên
QInt::QInt(int n) { 
	operator=(fromDec(to_string(n))); 
}

QInt::QInt(const Int& n) {
	operator=(fromDec(string(n)));
}

//  ---------------------------------------------------
// | Nhóm hàm biểu diễn ở các hệ cơ số dưới dạng chuỗi |
//  ---------------------------------------------------

// Biểu diễn dạng nhị phân
string QInt::toBin() const {
	string res;
	int i = 0;
	while (((data[BYTESZ - 1 - i / TYPESZ] >> (i % TYPESZ)) & 1) == 0) i++;
	for (; i < TYPESZ*BYTESZ; i++) {
		int dataId = BYTESZ - 1 - i / TYPESZ;
		int bitId = i % TYPESZ;
		res = res + char(((data[dataId] >> bitId) & 1) + '0');
	}

	if (res.size() == 0) return "0";
	return res;
}

// Biểu diễn dạng thập lục phân
string QInt::toHex() const {
	// Tạo ánh xạ ứng với kí số
	string dict(16, 0);
	for (int i = 0; i < 10; i++)
		dict[i] = i + '0';
	for (int i = 10; i < 16; i++)
		dict[i] = i - 10 + 'A';

	int flag = false;
	string res;
	for (int i = 0; i < ((TYPESZ * BYTESZ) >> 2); i++) {
		int val = 0;
		for (int j = 0; j < 4; j++) {
			int pos = 4 * i + (4 - j - 1);
			int dataId = BYTESZ - 1 - pos / 8;
			int bitId = pos % 8;
			int bit = ((data[dataId] >> bitId) & 1);
			val += (bit << j);
		}
		if (val != 0 || flag) {
			res = res + dict[val];
			flag = true;
		}
	}

	if (res.size() == 0) return "0";
	return res;
}

// Biểu diễn dạng thập phân
string QInt::toDec() const {
	Int res;

	// Sử dụng công thức:
	// a = -bit[n]*2^(n) + bit[n-2]*2^(n-2) + ... + bit[0]*2^0
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

// Biểu diễn dưới dạng cơ số b
string QInt::toString(string b) const {
	if (b == "2") return toBin();
	else if (b == "10") return toDec();
	else if (b == "16") return toHex();
}

//  ---------------------------------------------------
// | Nhóm hàm nhập vào từ các hệ cơ số dưới dạng chuỗi |
//  ---------------------------------------------------

// Nhập từ hệ nhị phân
QInt fromBin(string bin) {
	QInt res;
	int pos = 0;
	for (int i = bin.size() - 1; i > -1; i--)
		res.setBit(pos++, bin[i] - '0');
	return res;

	/*QInt res;
	int i = bin.size() - 1;
	while (i > -1) {
		int pos = (bin.size() - 1) - i;
		int dataId = pos / QBit::TYPESZ;
		int bitId = (QBit::TYPESZ - 1) - pos % QBit::TYPESZ;
		res.data[dataId] = res.data[dataId] | ((bin[i] - '0') << bitId);
		i--;
	}
	return res;*/
}

// Nhập từ hệ thập lục phân
QInt fromHex(string hex) {
	// Chuẩn hóa chuỗi nhập vào, chuyển ký tự thường thành in hoa
	for (int i = 0; i < hex.size(); i++)
		if (hex[i] <= 'z' && hex[i] >= 'a')
			hex[i] = hex[i] - 'a' + 'A';
	
	QInt res;
	int pos = 0;
	for (int i = hex.size() - 1; i > -1; i--) {
		int n = (hex[i] >= '0' && hex[i] <= '9') ? (hex[i] - '0') : (hex[i] - 'A' + 10);
		for (int j = 0; j < 4; j++) {
			int bit = n & 1;
			res.setBit(pos, bit);
			pos++;
			n = n >> 1;
		}
	}

	/*QInt res;
	for (int i = 0; i < hex.size(); i++) {
		int n = (hex[i] >= '0' && hex[i] <= '9') ? (hex[i] - '0') : (hex[i] - 'A' + 10);
		for (int j = 0; j < 4; j++) {
			int bit = n % 2;
			int pos = ((i + (QBit::TYPESZ*QBit::BYTESZ >> 2) - hex.size()) << 2) + (4 - j - 1);
			int dataId = QBit::BYTESZ - 1 - pos / QBit::TYPESZ;
			int bitId = pos % QBit::TYPESZ;
			res.data[dataId] = res.data[dataId] | (bit << bitId);
			n = n / 2;
		}
	}*/
	return res;
}

// Nhập từ hệ thập phân
QInt fromDec(string s) {
	Int dec(s);
	int r;
	int i = 0;

	string bin;
	bool sign = dec.isNegative();

	QInt res;
	int pos = 0;
	while (pos < QBit::TYPESZ * QBit::BYTESZ) {
		dec = dec.halved(r);
		res.setBit(pos, r);
		pos++;
	}

	/*QInt res;
	for (int i = 0; i < QBit::TYPESZ*QBit::BYTESZ; i++) {
		dec = dec.halved(r);
		int dataId = i / QBit::TYPESZ;
		int bitId = i % QBit::TYPESZ;
		res.data[dataId] |= (r << (QBit::TYPESZ - 1 - bitId));
	}*/

	// Nếu là số âm, chuyển sang dạng bù 2
	if (sign) res = QInt(~res) + QInt(1);
	return res;
}

// Nhập vào từ chuỗi n, hệ cơ số b
QInt fromString(string n, string b) {
	if (b == "2") return fromBin(n);
	else if (b == "10") return fromDec(n);
	else if (b == "16") return fromHex(n);
}

//  ------------------
// | Nhóm các toán tử |
//  ------------------

// Toán tử gán =
QInt& QInt::operator =(const QInt& n) {
	QBit::operator=(n);
	return (*this);
}

// Toán tử lấy giá trị tuyệt đối
QInt QInt::operator !() const {
	QInt res = *this;
	if (res.data[BYTESZ - 1] & 1)
		res = QInt(~res) + QInt(1);
	return res;
}

// Toán tử nhân (thuật toán Booth)
// Trả về một cặp high/low
pair<QInt, QInt> QInt::operator *(const QInt& n) const {
	QInt A = QInt();
	QInt Q = *this;
	int q = 0;
	QInt M = n;

	for (int i = 0; i < TYPESZ*BYTESZ; i++) {
		// Nếu Q[0] và q khác nhau
		if (((Q.data[0] >> (TYPESZ - 1)) & 1) ^ q) {
			// Trường hợp 01
			if (q) A = A + M;
			// Trường hợp 10
			else A = A - M;
		}
		
		// Dịch phải số học [A, M]

		// Lưu bit cuối của A
		int carry = (A.data[0] >> (TYPESZ - 1)) & 1;

		// Dịch phải số học A
		int arith = A.data[BYTESZ - 1] & 1;
		A = (A >> 1);
		A.data[BYTESZ - 1] |= arith;

		// Dịch phải Q với bit cuối của A
		q = (Q.data[0] >> (TYPESZ - 1)) & 1;
		Q = (Q >> 1);
		Q.data[BYTESZ - 1] |= carry;
	}

	return { A, Q };
}

// Toán tử chia
// Trả về một cặp {thương, số dư}
pair<QInt, QInt> QInt::operator /(const QInt& n) const {
	if (n.isZero()) return { QInt(), QInt() };

	QInt A = QInt();
	// Chia phần không dấu
	QInt Q = !(*this);
	QInt M = !n;

	// Lưu dấu
	bool sign = n.isNegative() ^ isNegative();

	for (int i = 0; i < TYPESZ*BYTESZ; i++) {
		// Dịch trái [A, Q]
		int carry = Q.data[BYTESZ - 1] & 1;	// Lưu lại bit đầu của Q
		A = A << 1;	// Dịch trái A
		A.data[0] |= carry << (TYPESZ - 1);	// Đặt bit cuối của A
		Q = Q << 1;	// Dịch trái Q

		A = A - M;

		if (A.data[BYTESZ - 1] & 1) {	// Nếu A âm
			Q.data[0] &= ~(1 << (TYPESZ - 1));
			A = A + M;
		}
		else {
			Q.data[0] |= (1 << (TYPESZ - 1));
		}
	}

	// Nếu trái dấu, đổi dấu thương số
	if (sign) Q = QInt(~Q) + QInt(1);
	return { Q, A };
}

// Toán tử cộng
QInt QInt::operator +(const QInt& b) const {
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

// Toán tử trừ
QInt QInt::operator -(const QInt& b) const {
	QInt c = b;
	// a - b = a + (-b)
	return (*this) + (QInt(~c) + fromDec("1"));
}

//  -----------------------
// | Nhóm hàm phụ trợ khác |
//  -----------------------

// Kiểm tra âm
bool QInt::isNegative() const {
	return data[BYTESZ - 1] & 1;
}

// Kiểm tra bằng 0
bool QInt::isZero() const {
	for (int i = 0; i < BYTESZ; i++)
		if (data[i] != 0)
			return false;
	return true;
}