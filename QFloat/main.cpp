#include <iostream>
#include <string>
#include <bitset>
#include <vector>
using namespace std;
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

vector <bool> subBit(vector <bool> s1, vector <bool> s2, bool &carry)
{
	vector <bool> s;
	for (int i = s1.size() - 1; i >= 0; i--)
	{
		if (s1[i] == s2[i])
		{
			s.insert(s.begin(), carry);
		}
		else
		{
			s.insert(s.begin(), !carry);
			carry = s2[i];
		}
	}
	return s;
}

// Lấy bit thứ i từ trái sang của số nguyên x
int getBitInt(int x, int i) {
	return ((x >> (31 - i % 32)) & 1);
}

class QFloat {
private:
	char DATA[16];	// Sử dụng 16 char cho 128 bit
	bool isNegative;
public:
	// Khởi tạo mặc định toàn bit 0
	QFloat() {
		for (int i = 0; i < 16; ++i) {
			this->DATA[i] = 0;
		}
		this->isNegative = false;
	}

	// Toán tử gán = toàn bộ với ký tự x
	QFloat& operator =(char x) {
		for (int i = 0; i < 16; ++i) {
			this->DATA[i] = x;
		}
		this->isNegative = false;
		return *this;
	}

	// Đặt bit thứ i là bit (vị trí i tính từ trái sang, từ 0)
	void setBit(int bit, int i) {
		int temp = i / 8;
		this->DATA[temp] ^= (-bit ^ this->DATA[temp]) & (1 << (7 - i % 8));
	}

	// Lấy bit thứ i từ trái sang
	int getBit(int i) const {
		return ((this->DATA[i / 8] >> (7 - i % 8)) & 1);
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
	bool isZero(string number) {
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

	// Kiểm tra = 0
	bool isZero() const {
		for (int i = 0; i < 16; i++) {
			for (int j = 7; j >= 0; --j) {
				if (((this->DATA[i] >> j) & 1) != 0) {
					return false;
				}
			}
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
			for (int i = 0; i < 112 - (intPart.size() - 1); ++i) {
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

			for (int i = 0; i < 112; ++i) {
				fractionPart = mulFractionByTwo(fractionPart);
				fractionBit += fractionPart[0];
				fractionPart[0] = '0';
			}

			if (cnt + 1 < k)
				exp = -(cnt + 1) + k;
			else
				exp = 0;
		}

		string res = intPart + fractionBit;
		while (res[0] == '0') res.erase(0, 1);
		while (res.size() < 113) res += '0';
		return res;
	}

	void strDecToQFloat() {
		string number;
		cin >> number;
		if (number[0] == '-') {
			this->isNegative = true;
			number.erase(0, 1);
		}
		if (isZero(number)) {
			*this = (char)0;
			return;
		}

		int exp;
		string sign = toStrBit(number, exp);

		if (isNegative) {
			setBit(1, 0);
		}
		else setBit(0, 0);

		for (int i = 1; i <= 15; i++)
			setBit(getBitInt(exp, 31 - 15 + i), i);

		for (int i = 15 + 1; i < 15 + 112 + 1; i++)
			setBit(sign[i - 15] - '0', i);
	}

	void DecToBinary() {
		for (int i = 0; i < 16; i++) {
			for (int j = 7; j >= 0; --j)
				cout << ((this->DATA[i] >> j) & 1);
		}
	}

	QFloat operator + (const QFloat&);
	QFloat operator - (const QFloat&);
};

QFloat QFloat::operator + (const QFloat &T) {
	QFloat ans;

	// Nếu 1 trong 2 số là 0, trả số còn lại
	if (T.isZero()) return *this;
	if (this->isZero()) return T;

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

	// Tráo 2 số để phần mũ số 1 luôn > số 2
	bool change = 0;
	if (e1 < e2)
	{
		bool tsign = sign1; sign1 = sign2; sign2 = tsign;
		int te = e1; e1 = e2; e2 = te;
		vector <bool> ts = s1; s1 = s2; s2 = ts;
		change = 1;
	}

	e = e1;
	if (e1 == e2) {
		if (sign1 != sign2)
		{
			bool carry = 0;
			s = subBit(s1, s2, carry);
			if (carry)
			{
				int i;
				for (i = 0; i < s.size(); i++) s[i] = !s[i];
				for (i = s.size() - 1; i >= 0; i--)
					if (!s[i])
					{
						s[i] = 1;
						for (int j = i + 1; j < s.size(); j++) s[j] = 0;
						break;
					}
				for (i = 0; i < s.size(); i++)
				{
					if (!s[0])
					{
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
				sign = !sign1;
			}
			else
			{
				int i;
				for (i = 0; i < s.size(); i++)
				{
					if (!s[0])
					{
						s.erase(s.begin());
						s.push_back(0);
						e--;
					}
					else break;
				}
				if (i >= s.size()) e = 0;
				else
				{
					s.erase(s.begin());
					s.push_back(0);
					e--;
				}
				sign = sign1;
			}
		}
		else
		{
			bool carry = 0;
			s = addBit(s1, s2, carry);
			s.insert(s.begin(), carry);
			s.pop_back();
			e++;
			sign = sign1;
		}
	}
	else
	{
		int d = e1 - e2;
		while (e1 > e2)
		{
			s2.insert(s2.begin(), 0);
			s2.pop_back();
			e2++;
		}
		if (d > 0 && d <= s2.size()) s2[d - 1] = 1;
		if (sign1 != sign2)
		{
			bool carry = 0;
			s = subBit(s1, s2, carry);
			if (carry)
			{
				s.erase(s.begin());
				s.push_back(0);
				e--;
			}
			sign = sign1;
		}
		else
		{
			bool carry = 0;
			s = addBit(s1, s2, carry);
			if (carry)
			{
				s.insert(s.begin(), 0);
				s.pop_back();
				e++;
			}
			sign = sign1;
		}
	}
	
	// Đặt phần dấu cho kết quả
	ans.setBit(sign, 0);

	// Đặt phần mũ cho kết quả
	for (int i = 15; i >= 1; i--) {
		ans.setBit(e % 2, i);
		e /= 2;
	}

	// Đặt phần trị cho kết quả
	for (int i = 16; i <= 127; i++)
		ans.setBit(s[i - 16], i);

	return ans;
}

QFloat QFloat::operator - (const QFloat &T) {
	QFloat X = T;
	X.setBit(!X.getBit(0), 0);
	return *this + X;
}

int main() {
	QFloat a;
	a.strDecToQFloat();
	a.DecToBinary();
	cout << endl;
	QFloat b;
	b.strDecToQFloat();
	b.DecToBinary();
	cout << endl;
	QFloat c = a - b;
	c.DecToBinary();
	cout << endl;
	QFloat d;
	d.strDecToQFloat();
	d.DecToBinary();
	cout << endl;
	system("pause");
	return 0;
}