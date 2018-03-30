﻿#include "QFloat.h"
#include "Float.h"
#include "QInt.h"

//  --------------------------
// | Các hàm hỗ trợ bên ngoài |
//  --------------------------

// Cộng hai dãy Bit
vector <bool> addBit(vector <bool> s1, vector <bool> s2, bool &carry) {
	vector <bool> s;
	for (int i = s1.size() - 1; i >= 0; i--) {
		if (s1[i] == s2[i]) {
			s.insert(s.begin(), carry);
			carry = s1[i];
		}
		else {
			s.insert(s.begin(), !carry);
		}
	}
	return s;
}

// Trừ hai dãy bit
vector <bool> subBit(vector <bool> s1, vector <bool> s2, bool &carry) {
	vector <bool> s;
	for (int i = s1.size() - 1; i >= 0; i--) {
		if (s1[i] == s2[i]) {
			s.insert(s.begin(), carry);
		}
		else {
			s.insert(s.begin(), !carry);
			carry = s2[i];
		}
	}
	return s;
}

// Nhân hai dãy bit
vector<bool> mulBit(const vector<bool>& s1, const vector<bool>& s2) {
	vector<bool> A(114, 0);
	vector<bool> Q = s1;
	int q = 0;
	vector<bool> M = s2;

	for (int i = 0; i < 114; i++) {
		if (Q.back() ^ q) {
			bool carry = 0;
			if (q) A = addBit(A, M, carry);
			else A = subBit(A, M, carry);
		}

		bool carry = A.back();
		A.pop_back();
		A.insert(A.begin(), A[0]);

		q = Q.back();
		Q.pop_back();
		Q.insert(Q.begin(), carry);
	}

	A.insert(A.end(), Q.begin(), Q.end());
	return A;
}

// Chia hai dãy bit
pair<vector<bool>, vector<bool>> divBit(vector<bool> s1, vector<bool> s2) {
	int n = max(s1.size(), s2.size()) + 1;

	vector<bool> A(n, 0);
	vector<bool> Q = s1;
	vector<bool> M = s2;

	while (Q.size() < n) Q.insert(Q.begin(), 0);
	while (M.size() < n) M.insert(M.begin(), 0);

	for (int i = 0; i < n; i++) {
		int carry = Q[0];
		A.erase(A.begin());
		A.push_back(carry);
		Q.erase(Q.begin());
		Q.push_back(0);

		bool c = 0;
		A = subBit(A, M, c);

		if (A[0] == 1) {
			Q[Q.size() - 1] = 0;
			bool c = 0;
			A = addBit(A, M, c);
		}
		else {
			Q[Q.size() - 1] = 1;
		}
	}

	if (Q[0] == 1) {
		for (int i = 0; i < Q.size(); i++)
			Q[i] = !Q[i];
		for (int i = Q.size() - 1; i >= 0; i--)
			if (!Q[i]) {
				Q[i] = 1;
				for (int j = i + 1; j < Q.size(); j++) Q[j] = 0;
				break;
			}
	}

	while (Q[0] == 0 && Q.size() > 1) Q.erase(Q.begin());
	while (A[0] == 0 && A.size() > 1) A.erase(A.begin());

	return { Q, A };
}

// Lấy bit thứ i từ trái sang của số nguyên x
int getBitInt(int x, int i) {
	return ((x >> (31 - i % 32)) & 1);
}

// Nhân đôi số thực
string mulFractionByTwo(string number) {
	int len = number.length();
	string result;
	int k = number.find('.');
	int carry = 0, tmp;

	if (k != string::npos) {
		// Nhân 2 với phần thập phân
		for (int i = len - 1; i > k; --i) {
			tmp = (number[i] - '0') * 2 + carry;
			if (tmp >= 10) {
				result.insert(result.begin(), char(tmp - 10 + '0'));
				carry = 1;
			}
			else {
				result.insert(result.begin(), char(tmp + '0'));
				carry = 0;
			}
		}
		result.insert(result.begin(), '.');

		// Nhân 2 với phần nguyên trước dấu '.'
		for (int i = k - 1; i >= 0; --i) {
			tmp = (number[i] - '0') * 2 + carry;
			if (tmp >= 10) {
				result.insert(result.begin(), char(tmp - 10 + '0'));
				carry = 1;
			}
			else {
				result.insert(result.begin(), char(tmp + '0'));
				carry = 0;
			}
		}
	}
	else {
		for (int i = len - 1; i >= 0; --i) {
			tmp = (number[i] - 48) * 2 + carry;
			if (tmp >= 10) {
				result.insert(result.begin(), char(tmp - 10 + '0'));
				carry = 1;
			}
			else {
				result.insert(result.begin(), char(tmp + '0'));
				carry = 0;
			}
		}
	}
	if (carry == 1) result.insert(result.begin(), '1');
	return result;
}

// Chia đôi số nguyên
string strDiv2(string number) {
	string result = number;
	int len = number.length();
	int k = 0, tmp;
	for (int i = 0; i < len; ++i) {
		tmp = k * 10 + (number[i] - '0');
		result[i] = tmp / 2 + '0';
		k = tmp % 2;
	}
	// Xóa 0 ở đầu
	while (result[0] == '0')
		result.erase(0, 1);
	// Nếu kết quả bằng 0
	if (result == "")
		result = "0";
	return result;
}

// Đổi từ số nguyên thành số nhị phân
string toBinary(string number) {
	string result = "";
	string x = number;
	while (x != "0") {
		int bit = x.back() % 2;
		if (bit == 1) result = "1" + result;
		else result = "0" + result;
		x = strDiv2(x);
	}
	return result;
}

// Kiểm tra số thực là số 0
bool isZeroStr(string number) {
	int pos = number.find('.');
	int len = number.length();
	if (pos != string::npos) {
		for (int i = 0; i < pos; ++i)
			if (number[i] != '0') return false;
		for (int i = pos + 1; i < len; ++i)
			if (number[i] != '0') return false;
	}
	else {
		for (int i = 0; i < len; ++i)
			if (number[i] != '0') return false;
	}
	return true;
}

// Đổi số thực ra nhị phân
string toStrBit(string number, int &exp) {
	int pos = number.find('.');
	string intPart, fractionPart;
	if (pos == string::npos) {
		intPart = number;
		fractionPart = "0";
	}
	else {
		intPart = number.substr(0, pos);
		fractionPart = number.substr(pos);
		fractionPart.insert(fractionPart.begin(), '0');
	}
	// Chuyển string của phần nguyên sang binary
	intPart = toBinary(intPart);

	int k = (1 << 14) - 1;
	string fractionBit;

	if (intPart != "") {
		exp = intPart.size() - 1 + k;
		for (int i = 0; i < 112 - int(intPart.size() - 1); ++i) {
			fractionPart = mulFractionByTwo(fractionPart);
			fractionBit += fractionPart[0];
			fractionPart[0] = '0';
		}
	}
	else {
		int cnt = 0;
		while (cnt < k) {
			fractionPart = mulFractionByTwo(fractionPart);
			fractionBit += fractionPart[0];
			fractionPart[0] = '0';
			if (fractionBit.back() == '1') break;
			cnt++;
		}

		exp = -(cnt + 1) + k;
		if (cnt + 1 < k) {
			for (int i = 0; i < 112; ++i) {
				fractionPart = mulFractionByTwo(fractionPart);
				fractionBit += fractionPart[0];
				fractionPart[0] = '0';
			}
		}
		else {
			fractionBit = "";
			while (exp < 1) {
				fractionPart = mulFractionByTwo(fractionPart);
				fractionBit += fractionPart[0];
				fractionPart[0] = '0';
				exp++;
			}
			string res = intPart + fractionBit;
			while (res.size() < 113) res += '0';
			return res;
		}
	}

	string res = intPart + fractionBit;
	while (res[0] == '0') res.erase(0, 1);
	while (res.size() < 113) res += '0';
	return res;
}

//  -------------------
// | Nhóm hàm khởi tạo |
//  -------------------

QFloat::QFloat(string dec) : QBit() {
	if (dec == "Inf" || dec == "-Inf") {
		data[0] = data[1] = (1 << 8) - 1;
		if (dec[0] != '-')
			data[0] = data[0] & ((1 << 7) - 1);
	}
	else if (dec == "NaN") {
		data[0] = data[1] = (1 << 8) - 1;
		if (dec[0] != '-')
			data[0] = data[0] & ((1 << 7) - 1);
		data[15] |= 1;
	}
	else
		operator =(strDecToQFloat(dec));
}

//  ------------------
// | Nhóm hàm phụ trợ |
//  ------------------

// Kiểm tra số âm
bool QFloat::isNegative() const {
	return getBit(0);
}

// Kiểm tra = 0
bool QFloat::isZero() const {
	for (int i = 0; i < 16; i++)
		if (data[i] != 0)
			return false;
	return true;
}

// Kiểm tra số là số vô cực
bool QFloat::isInf() const {
	for (int i = 1; i <= 15; i++)
		if (getBit(i) != 1)
			return false;
	for (int i = 2; i < 16; i++)
		if (data[i] != 0)
			return false;
	return true;
}

// Kiểm tra là số báo lỗi
bool QFloat::isNaN() const {
	for (int i = 1; i <= 15; i++)
		if (getBit(i) != 1)
			return false;
	for (int i = 2; i < 16; i++)
		if (data[i] != 0)
			return true;
	return false;
}

//  ------------------
// | Nhóm các toán tử |
//  ------------------

// Toán tử gán =
QFloat& QFloat::operator = (const QFloat& f) {
	QBit::operator=(f);
	return (*this);
}

// Phép tính cộng trên QFloat
QFloat QFloat::operator + (const QFloat &T) {
	// Nếu 1 trong 2 là số lỗi thì trả về số lỗi
	if (isNaN() || T.isNaN()) return QFloat("NaN");
	// Nếu cả hai là số vô cực
	if (isInf() && T.isInf()) {
		if (isNegative() && T.isNegative()) return QFloat("-Inf");
		if (!isNegative() && !T.isNegative()) return QFloat("Inf");
		return QFloat("NaN");
	}
	// Nếu một trong hai là số vô cực
	if ((isInf() && isNegative()) || (T.isInf() && T.isNegative())) return QFloat("-Inf");
	if ((isInf() && !isNegative()) || (T.isInf() && !T.isNegative())) return QFloat("Inf");
	// Nếu 1 trong 2 số là 0, trả về số còn lại
	if (T.isZero()) return *this;
	if (this->isZero()) return T;

	QFloat ans;

	// Lấy phần dấu
	bool sign1 = this->getBit(0);
	bool sign2 = T.getBit(0);
	bool sign;

	// Lấy phần mũ
	int e1 = 0, e2 = 0, e = 0;
	for (int i = 15; i >= 1; i--) {
		e1 += this->getBit(i) * (1 << (15 - i));
		e2 += T.getBit(i) * (1 << (15 - i));
	}
	// Nếu mũ = 0 -> số = 0 -> trả về số còn lại
	if (e1 == 0) return T;
	if (e2 == 0) return *this;

	// Lấy phần trị của hai số
	vector <bool> s1, s2, s;
	s1.clear(); s2.clear(); s.clear();
	for (int i = 16; i <= 127; i++) {
		s1.push_back(this->getBit(i));
		s2.push_back(T.getBit(i));
	}

	// Đưa số có phần mũ lớn hơn lên trước
	bool change = 0;
	if (e1 < e2) {
		bool tsign = sign1; sign1 = sign2; sign2 = tsign;
		int te = e1; e1 = e2; e2 = te;
		vector <bool> ts = s1; s1 = s2; s2 = ts;
		change = 1;
	}

	// Phần mũ kết quả bằng phần mũ lớn hơn
	e = e1;

	// Trường hợp 1: hai số cùng số mũ
	if (e1 == e2) {
		// Trường hợp 1.1: hai số khác dấu
		if (sign1 != sign2) {
			bool carry = 0;
			// Thực hiện phép trừ hai số
			s = subBit(s1, s2, carry);
			// Nếu còn phần nhớ -> s1 < s2 -> đổi dấu kết quả
			if (carry) {
				int i;
				// Đảo tất cả các bit
				for (i = 0; i < s.size(); i++) s[i] = !s[i];
				// Thêm 1
				for (i = s.size() - 1; i >= 0; i--)
					if (!s[i]) {
						s[i] = 1;
						for (int j = i + 1; j < s.size(); j++) s[j] = 0;
						break;
					}

				// Dịch trái kết quả và giảm số mũ để chuẩn hóa
				// Xóa các số 0 và số 1 đầu tiên
				for (i = 0; i < s.size(); i++) {
					if (!s[0]) {
						s.erase(s.begin());
						s.push_back(0);
						e--;
					}
					else
					{
						s.erase(s.begin());
						s.push_back(0);
						e--;
						break;
					}
				}

				// Dấu theo số lớn hơn
				sign = !sign1;
			}
			// Nếu không còn nhớ, s1 > s2
			else {
				int i;

				// Xóa các số 0 ở đầu, tìm đến bit 1 đầu tiên
				for (i = 0; i < s.size(); i++) {
					if (!s[0]) {
						s.erase(s.begin());
						s.push_back(0);
						e--;
					}
					else break;
				}

				// Trường hợp số không chuẩn
				if (i >= s.size()) e = 0;
				else {
					s.erase(s.begin());
					s.push_back(0);
					e--;
				}

				// Dấu theo số lớn hơn
				sign = sign1;
			}
		}
		// Trường hợp 1.2: Hai số cùng dấu
		else {
			bool carry = 0;
			// Cộng hai dãy bit
			s = addBit(s1, s2, carry);
			// Thêm phần nhớ ở đầu
			s.insert(s.begin(), carry);
			// Trả về đúng số lượng bit
			s.pop_back();
			e++;
			sign = sign1;
		}
	}
	// Trường hợp 2: hai số khác số mũ (e1 > e2)
	else {
		int d = e1 - e2;
		// Thêm bit vào e2 để cân bằng số mũ
		while (e1 > e2) {
			s2.insert(s2.begin(), 0);
			s2.pop_back();
			e2++;
		}
		// Thêm bit 1 ở đầu
		if (d > 0 && d <= s2.size()) s2[d - 1] = 1;
		// Trường hợp 2.1: hai số khác dấu (s1 > s2)
		if (sign1 != sign2) {
			bool carry = 0;
			s = subBit(s1, s2, carry);
			if (carry) {
				while (s[0] == 0) {
					s.erase(s.begin());
					s.push_back(0);
					e--;
				}
				s.erase(s.begin());
				s.push_back(0);
				e--;
			}
			sign = sign1;
		}
		// Trường hợp 2.2: hai số cùng dấu
		else {
			bool carry = 0;
			s = addBit(s1, s2, carry);
			if (carry) {
				s.insert(s.begin(), 0);
				s.pop_back();
				e++;
			}
			sign = sign1;
		}
	}

	// Đặt phần dấu cho kết quả
	ans.setBit(0, sign);

	// Đặt phần mũ cho kết quả
	for (int i = 15; i >= 1; i--) {
		ans.setBit(i, e % 2);
		e /= 2;
	}

	// Đặt phần trị cho kết quả
	for (int i = 16; i <= 127; i++)
		ans.setBit(i, s[i - 16]);

	return ans;
}

// Phép tính trừ trên QFloat
QFloat QFloat::operator - (const QFloat &T) {
	QFloat X = T;
	// Đổi dấu số trừ
	X.setBit(0, !X.getBit(0));
	// a - b = a + (-b)
	return *this + X;
}

// Phép tính nhân trên QFloat
QFloat QFloat::operator * (const QFloat &T) {
	// Nếu 1 trong 2 là số báo lỗi
	if (isNaN() || T.isNaN()) return QFloat("NaN");
	// Nếu là vô cực nhân 0
	if ((T.isZero() && isInf()) || (isZero() && isInf())) return QFloat("NaN");
	// Nếu là vô cực nhân một số
	if (isInf() || T.isInf()) {
		if (isNegative() ^ T.isNegative()) return QFloat("-Inf");
		return QFloat("Inf");
	}
	// Nếu 1 trong 2 số là 0, trả về 0
	if (T.isZero() || this->isZero()) return QFloat();

	QFloat ans;

	// Lấy phần dấu
	bool sign1 = this->getBit(0);
	bool sign2 = T.getBit(0);
	bool sign;

	// Lấy phần mũ
	int e1 = 0, e2 = 0, e = 0;
	for (int i = 15; i >= 1; i--) {
		e1 += this->getBit(i) * (1 << (15 - i));
		e2 += T.getBit(i) * (1 << (15 - i));
	}

	// Lấy phần trị của hai số
	vector <bool> s1, s2, s;
	s1.clear(); s2.clear(); s.clear();

	// Thêm bit 0 ở đầu để thuật toán Booth chạy đúng
	s1.push_back(0);
	s2.push_back(0);

	// Thêm bit ẩn ở đầu, xét trường hợp số không chuẩn
	s1.push_back(e1 != 0);
	s2.push_back(e2 != 0);

	for (int i = 16; i <= 127; i++) {
		s1.push_back(this->getBit(i));
		s2.push_back(T.getBit(i));
	}

	// Nhân hai phần trị bằng Booth
	s = mulBit(s1, s2);
	// Phần mũ bằng tổng mũ thêm 2 bit khi nhân
	e = e1 + e2 + 4;
	// Phần dấu bằng 0 nếu cùng dấu, 1 nếu khác
	sign = sign1 ^ sign2;

	int i;
	// Xóa các số 0 và số 1 đầu tiên
	for (i = 0; i < 2 * s.size(); i++) {
		if (!s[0]) {
			s.erase(s.begin());
			s.push_back(0);
			e--;
		}
		else {
			s.erase(s.begin());
			s.push_back(0);
			e--;
			break;
		}

		// Trường hợp số không chuẩn
		if (e <= (1 << 14) - 1) {
			e = (1 << 14) - 1;
			break;
		}
	}

	e -= ((1 << 14) - 1);

	// Đặt phần dấu cho kết quả
	ans.setBit(0, sign);

	// Đặt phần mũ cho kết quả
	for (int i = 15; i >= 1; i--) {
		ans.setBit(i, e % 2);
		e /= 2;
	}

	// Đặt phần trị cho kết quả
	for (int i = 16; i <= 127; i++)
		ans.setBit(i, s[i - 16]);

	return ans;
}

// Phép tính chia trên QFloat
QFloat QFloat::operator / (const QFloat &T) {
	// Nếu 1 trong 2 là NaN, báo lỗi
	if (isNaN() || T.isNaN()) return QFloat("NaN");
	// a / 0 = Undefined
	if (T.isZero()) return QFloat("NaN");
	// 0 / a = 0 (a khác 0)
	if (isZero()) return QFloat();
	// oo / oo = Undefined
	if (isInf() && T.isInf()) return QFloat("NaN");
	// oo / a = oo (xét dấu)
	if (isInf()) {
		if (T.isNegative() ^ isNegative()) return QFloat("-Inf");
		return QFloat("Inf");
	}
	// a / oo = 0 (a khác vô cực)
	if (T.isInf()) return QFloat();

	QFloat ans;

	// Xét dấu
	bool sign = getBit(0) ^ T.getBit(0);

	// Lấy phần mũ
	int e1 = 0, e2 = 0, e = 0;
	for (int i = 15; i >= 1; i--) {
		e1 += this->getBit(i) * (1 << (15 - i));
		e2 += T.getBit(i) * (1 << (15 - i));
	}

	// Lấy phần trị của hai số
	vector<bool> s1, s2, s;

	s1.clear(); s2.clear(); s.clear();
	// Thêm số ở đầu, xét dạng chuẩn và không chuẩn
	s1.push_back((e1 != 0));
	s2.push_back((e2 != 0));
	for (int i = 16; i <= 127; i++) {
		s1.push_back(this->getBit(i));
		s2.push_back(T.getBit(i));
	}

	e = e1 - e2 + (1 << 14) - 1;
	
	if (e1 > e2) 
		for (int i = 0; i < e1 - e2; i++)
			s1.push_back(0);
	else 
		for (int i = 0; i < e2 - e1 + 1; i++)
			s1.push_back(0);

	pair<vector<bool>, vector<bool>> t = divBit(s1, s2);
	if (e1 - e2 == t.first.size() || e2 - e1 == t.first.size() - 1) e--;

	int i = 16;
	int j = 1;
	while (i <= 127 && j < t.first.size()) {
		ans.setBit(i, t.first[j]);
		i++; j++;
	}
	s1 = t.second;
	s1.push_back(0);

	while (i < 128) {
		pair<vector<bool>, vector<bool>> res = divBit(s1, s2);

		int j = 0;
		while (i <= 127 && j < res.first.size()) {
			ans.setBit(i, res.first[j]);
			i++; j++;
		}

		s1 = res.second;

		s1.push_back(0);
	}

	// Đặt phần dấu cho kết quả
	ans.setBit(0, sign);

	// Đặt phần mũ cho kết quả
	for (int i = 15; i >= 1; i--) {
		ans.setBit(i, e % 2);
		e /= 2;
	}

	return ans;
}

// Hàm nhập QFloat dưới dạng chuỗi thập phân
QFloat& QFloat::strDecToQFloat(string number) {
	// Kiểm tra trường hợp đặc biệt
	if (number == "Inf" || number == "-Inf") {
		data[0] = data[1] = (1 << 8) - 1;
		if (number[0] != '-')
			data[0] = data[0] & ((1 << 7) - 1);
		return *this;
	}
	else if (number == "NaN") {
		data[0] = data[1] = (1 << 8) - 1;
		if (number[0] != '-')
			data[0] = data[0] & ((1 << 7) - 1);
		data[15] |= 1;
		return *this;
	}
	else if (isZeroStr(number)) {
		*this = QFloat();
		return *this;
	}

	// Xét dấu
	if (number[0] == '-') {
		setBit(0, 1);
		number.erase(0, 1);
	}
	else setBit(0, 0);

	// Tìm phần trị và phần mũ
	int exp;
	string sign = toStrBit(number, exp);

	// Đặt phần mũ
	for (int i = 1; i <= 15; i++)
		setBit(i, getBitInt(exp, 31 - 15 + i));

	// Đặt phần trị
	for (int i = 15 + 1; i < 15 + 112 + 1; i++)
		setBit(i, sign[i - 15] - '0');

	return (*this);
}

// Hàm xuất QFloat dưới dạng chuỗi thập phân
string QFloat::toDec() {
	// Xét trường hợp các số đặc biệt
	if (isInf()) {
		if (isNegative()) return "-Inf";
		return "Inf";
	}
	if (isNaN())
		return "NaN";
	if (isZero())
		return "0";

	Float res(0);

	// Lấy phần dấu
	bool sign = this->getBit(0);

	// Lấy phần mũ
	int e = 0;
	for (int i = 15; i >= 1; i--)
		e += this->getBit(i) * (1 << (15 - i));
	e -= (1 << 14) - 1;

	// Lấy phần trị

	// i lưu vị trí bit 1 đầu tiên
	int i = 0;

	// Trường hợp số không chuẩn
	if (e == -(1 << 14) + 1) {
		e = -(1 << 14) + 2;
		// Tìm vị trí bit 1 đầu tiên
		i = 1;
		while (i + 15 < 128 && getBit(i + 15) == 0)
			i++;
		// Nếu không có, là số 0
		if (i + 15 == 128) return "0";
	}

	// Tìm 2^i đầu tiên
	int d = e - i;
	Float t(1);
	if (d < 0) t = t >> -d;
	else t = t << d;

	// Cộng 2^i đầu tiên
	res = res + t;
	i++;

	// Các 2^i tiếp theo chỉ được cộng khi bit tại đó bật
	while (i < 113) {
		// 2^i = 2^(i + 1) >> 1
		t = t >> 1;
		if (getBit(i + 15)) res = res + t;
		i++;
	}

	// Nếu có dấu, đổi dấu kết quả
	if (sign) res = ~res;

	return string(res);
}

// Hàm xuất QFloat dưới dạng chuỗi nhị phân chuẩn IEEE
string QFloat::DecToBinary() {
	string s;
	for (int i = 0; i < 16; i++) {
		for (int j = 7; j >= 0; --j)
			s += ((this->data[i] >> j) & 1) + '0';
	}
	return s;
}

// Hàm nhập QFloat bằng chuỗi nhị phân chuẩn IEEE
QFloat QFloatfromBin(string bin) {
	QFloat res;
	int pos = 0;
	for (int i = 0; i < bin.size(); i++)
		res.setBit(pos++, bin[i] - '0');
	return res;
}

// Nhập QFloat từ chuỗi nhị phân có dấu .
QFloat& QFloat::fromBitStr(string bit) {
	// Xét trường hợp đặc biệt
	if (bit == "Inf" || bit == "-Inf" || bit == "NaN") {
		*this = QFloat(bit);
		return *this;
	}
	if (isZeroStr(bit)) {
		operator=(QFloat());
		return *this;
	}

	// Xét dấu
	if (bit[0] == '-') {
		setBit(0, 1);
		bit.erase(0, 1);
	}
	else setBit(0, 0);

	// Tách phần nguyên và phần thập phân
	int pos = bit.find('.');
	string intPart, fractionPart;
	if (pos == string::npos) {
		intPart = bit;
	}
	else {
		intPart = bit.substr(0, pos);
		fractionPart = bit.substr(pos + 1);
	}

	// Chuẩn hóa, loại 0 ở đầu phần nguyên
	while (intPart[0] == '0')
		intPart.erase(intPart.begin());

	// Tìm số mũ
	int k = (1 << 14) - 1;
	int exp = intPart.size() - 1 + k;

	// Nếu không có phần nguyên, chuẩn hóa phần thập phân
	if (intPart == "") {
		while (fractionPart[0] == '0' && fractionPart.size() > 1) {
			if (exp == 1) break;
			fractionPart.erase(fractionPart.begin());
			exp--;
		}

		// Trường hợp số không chuẩn, chỉ lấy 112 bit tiếp
		if (exp == 1) {
			while (fractionPart.size() > 113)
				fractionPart.pop_back();
		}
	}

	// Ghép hai mạnh lại và chuẩn hóa cho đủ 112 bit
	string res = intPart + fractionPart;
	while (res[0] == '0') res.erase(0, 1);
	while (res.size() < 113) res += '0';

	// Nhập phần mũ
	for (int i = 1; i <= 15; i++)
		setBit(i, getBitInt(exp, 31 - 15 + i));

	// Nhập phần trị
	for (int i = 15 + 1; i < 15 + 112 + 1; i++)
		setBit(i, res[i - 15] - '0');

	return *this;
}

// Chuyển QFloat thành chuỗi nhị phân có dấu .
string QFloat::toBitString() {
	if (isInf()) {
		if (isNegative()) return "-Inf";
		return "Inf";
	}
	if (isNaN())
		return "NaN";
	if (isZero())
		return "0";

	// Xét dấu
	bool sign = getBit(0);

	// Lấy phần mũ
	int e = 0;
	for (int i = 15; i >= 1; i--) {
		e += getBit(i) * (1 << (15 - i));
	}
	e -= (1 << 14) - 1;

	// Lấy phần trị
	string s;
	for (int i = 16; i <= 127; i++) {
		s.push_back(getBit(i) + '0');
	}

	// Thêm bit đầu, xét số không chuẩn
	if (e == -(1 << 14) - 1)
		s.insert(s.begin(), '0');
	else
		s.insert(s.begin(), '1');

	while (e < 0) {
		s = '0' + s;
		e++;
	}

	// Thêm 0 ở đầu cho phần trị
	int n = s.size();
	while (e > s.size())
		s = '0' + s;

	// Thêm 0. ở đầu nếu không có phần nguyên
	// Ngược lại, thêm dấu . vào đúng vị trí
	if (e >= n || e == -1)
		s = "0." + s;
	else if (e >= 0) {
		s.insert(s.begin() + e + 1, '.');
	}

	// Chuẩn hóa chuỗi, không có 0 hay . ở cuối
	while (s.back() == '0') s.pop_back();
	if (s.back() == '.') s.pop_back();

	// Thêm dấu âm
	if (sign)
		s.insert(s.begin(), '-');

	return s;
}

// Hàm nhập QFloat từ chuỗi tổng quát
QFloat QFloatfromString(string n, string b) {
	if (b == "2") return QFloat().fromBitStr(n);
	else if (b == "10") return QFloat().strDecToQFloat(n);
}

// Hàm xuất QFloat ra chuỗi tổng quát
string QFloat::toString(string b) {
	if (b == "2") return toBitString();
	else if (b == "10") return toDec();
}