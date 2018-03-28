#include "Int.h"

//  -------------------
// | Nhóm hàm khởi tạo |
//  -------------------

// Khởi tạo mặc định
Int::Int() {
	sign = false;
}

// Khởi tạo từ chuỗi
Int::Int(string s) {
	sign = (s[0] == '-');
	Digit.resize(s.size() - (sign ? 1 : 0));
	for (int i = s.size() - (sign ? 1 : 0) - 1; i > -1; i--)
		Digit[i] = s[s.size() - 1 - i] - '0';
	while (Digit.size() && Digit.back() == 0) Digit.pop_back();
	if (Digit.size() == 0) Digit.push_back(0);
}

// Khởi tạo từ số nguyên
Int::Int(int n) {
	sign = false;
	if (n == 0)
		Digit.push_back(0);
	else {
		if (n < 0) {
			sign = true;
			n = -n;
		}

		while (n > 0) {
			Digit.push_back(n % 10);
			n = n / 10;
		}
	}
}

//  ------------------
// | Nhóm các toán tử |
//  ------------------

// Toán tử cộng
Int Int::operator + (const Int& n) const {
	Int a = (*this);
	Int b = n;
	Int c;

	// Nếu a và b khác dấu
	if (a.sign ^ b.sign) {
		// Trả về hiệu số lớn - số bé
		// Dấu theo số lớn
		if (!a > !b) {
			c = !a - !b;
			c.sign = a.sign;
		}
		else {
			c = !b - !a;
			c.sign = b.sign;
		}
	}
	// Ngược lại, thực hiện phép cộng bình thường
	// Dấu là dấu chung
	else {
		if (a.Digit.size() > b.Digit.size()) {
			b.Digit.resize(a.Digit.size());
			c.Digit.resize(a.Digit.size());
		}
		else {
			a.Digit.resize(b.Digit.size());
			c.Digit.resize(b.Digit.size());
		}

		int leftover = 0;
		for (int i = 0; i < c.Digit.size(); i++) {
			leftover = leftover + a.Digit[i] + b.Digit[i];
			c.Digit[i] = (leftover % 10);
			leftover = leftover / 10;
		}

		if (leftover > 0)
			c.Digit.push_back(leftover);
		c.sign = a.sign;
	}
	return c;
}

// Toán tử trừ
Int Int::operator - (const Int& n) const {
	Int a = !(*this); bool s1 = this->isNegative();
	Int b = !n; bool s2 = n.isNegative();
	Int c;

	// Nếu a >= b, trả về a - b
	if (a >= b) {
		b.Digit.resize(a.Digit.size());
		c.Digit.resize(a.Digit.size());
		int leftover = 0;
		for (int i = 0; i < c.Digit.size(); i++) {
			leftover = a.Digit[i] - b.Digit[i] - leftover;
			if (leftover < 0) {
				c.Digit[i] = leftover + 10;
				leftover = 1;
			}
			else {
				c.Digit[i] = leftover;
				leftover = 0;
			}
		}
		while (c.Digit.size() >= 2 && c.Digit.back() == 0)
			c.Digit.pop_back();
	}
	// Ngược lại, trả về -(b - a)
	else {
		c = b - a;
		c.sign = ~c.sign;
	}
	return c;
}

// Gấp đôi số lên
Int Int::doubled() const {
	return (*this) + (*this);
}

// Phép dịch phải
Int Int::operator <<(int k) const {
	Int res = (*this);
	while (k--)
		res = res.doubled();
	return res;
}

// Giảm nửa số
Int Int::halved(int& rem) const {
	Int c;
	int leftover = 0;
	for (int i = Digit.size() - 1; i > -1; i--) {
		c.Digit.push_back((10 * leftover + Digit[i]) >> 1);
		leftover = (10 * leftover + Digit[i]) % 2;
	}
	rem = leftover;
	int l = 0, r = c.Digit.size() - 1;
	while (l < r) {
		swap(c.Digit[l], c.Digit[r]);
		l++; r--;
	}
	if (c.Digit.back() == 0 && c.Digit.size() > 1) c.Digit.pop_back();
	c.sign = sign;
	return c;
}

// Gấp 10 lần
Int Int::tenfold(int k) const {
	if (k <= 0) return *this;
	Int res = *this;
	res.Digit.resize(res.Digit.size() + k);
	int r = res.Digit.size() - 1;
	while (r > k - 1) {
		res.Digit[r] = res.Digit[r - k];
		r--;
	}
	while (r >= 0) {
		res.Digit[r] = 0;
		r--;
	}
	return res;
}

// Giảm 10 lần
Int Int::tenth(int k) const {
	if (k <= 0) return *this;
	Int res = *this;
	res.Digit.erase(res.Digit.begin(), res.Digit.begin() + k);
	if (res.Digit.size() == 0) res.Digit.push_back(0);
	return res;
}

// Toán tử lấy giá trị tuyệt đối
Int Int::operator !() const {
	Int res = *this;
	res.sign = false;
	return res;
}

// Toán tử đổi dấu
Int Int::operator ~() const {
	Int res = *this;
	res.sign = ~res.sign;
	return res;
}

//  --------------------------
// | Nhóm các toán tử so sánh |
//  --------------------------

bool Int::operator == (const Int& n) const {
	if (n.sign != sign && Digit[0] != 0) return false;
	if (n.Digit.size() != Digit.size()) return false;
	for (int i = 0; i < Digit.size(); i++)
		if (Digit[i] != n.Digit[i]) return false;
	return true;
}

bool Int::operator != (const Int& n) const {
	return !(*this == n);
}

bool Int::operator > (const Int& n) const {
	if (!sign && n.sign) return true;
	if (sign && !n.sign) return false;

	if (Digit.size() > n.Digit.size()) return !sign;
	if (Digit.size() < n.Digit.size()) return sign;

	for (int i = Digit.size() - 1; i > -1; i--) {
		if (Digit[i] > n.Digit[i]) return !sign;
		if (Digit[i] < n.Digit[i]) return sign;
	}
	return false;
}

bool Int::operator < (const Int& n) const {
	return !(*this > n) && !(*this == n);
}

bool Int::operator >= (const Int& n) const {
	return (*this > n) || (*this == n);
}

bool Int::operator <= (const Int& n) const {
	return !(*this > n);
}

//  ------------------
// | Nhóm các phụ trợ |
//  ------------------

// Kiểm tra số âm
bool Int::isNegative() const {
	return sign; 
}

// Kiểm tra số lẻ
bool Int::isOdd() const {
	return Digit[0] % 2 != 0;
}

// Độ dài
int Int::length() const {
	return Digit.size();
}

// Nhập số
void Int::input() {
	string s;
	cin >> s;
	sign = s[0] == '-';
	Digit.resize(s.size() - sign);
	for (int i = s.size() - sign - 1; i > -1; i--)
		Digit[i] = s[s.size() - 1 - i] - '0';
	while (Digit.size() && Digit.back() == 0) Digit.pop_back();
	if (Digit.size() == 0) Digit.push_back(0);
}

// In số
void Int::print() const {
	if (sign) cout << '-';
	for (int i = Digit.size() - 1; i > -1; i--)
		cout << Digit[i];
}

// Lấy ký số thứ i
int Int::operator[](int i) const {
	return Digit[i];
}

// Ép về kiểu string <=> biểu diễn hệ thập phân
Int::operator string() const {
	string s;
	if (sign) s += "-";
	for (int i = Digit.size() - 1; i > -1; i--)
		s += (Digit[i] + '0');
	return s;
}