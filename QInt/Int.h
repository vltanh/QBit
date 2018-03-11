#pragma once

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Int {
private:
	vector<int> Digit;
	bool sign;
public:
	Int() { 
		sign = false; 
	}

	Int(string s) {
		sign = (s[0] == '-');
		Digit.resize(s.size() - (sign ? 1 : 0));
		for (int i = s.size() - (sign ? 1 : 0) - 1; i > -1; i--)
			Digit[i] = s[s.size() - 1 - i] - '0';
		while (Digit.size() && Digit.back() == 0) Digit.pop_back();
		if (Digit.size() == 0) Digit.push_back(0);
	}

	Int(int n) {
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

	void input() {
		string s;
		cin >> s;
		sign = s[0] == '-';
		Digit.resize(s.size() - sign);
		for (int i = s.size() - sign - 1; i > -1; i--)
			Digit[i] = s[s.size() - 1 - i] - '0';
		while (Digit.size() && Digit.back() == 0) Digit.pop_back();
		if (Digit.size() == 0) Digit.push_back(0);
	}

	void print() {
		if (sign) cout << '-';
		for (int i = Digit.size() - 1; i > -1; i--)
			cout << Digit[i];
	}

	Int operator +(const Int&);
	Int operator -(const Int&);
	Int doubled();
	Int halved(int&);
	Int tenfold(int k) const {
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

	Int tenth(int k) {
		if (k <= 0) return *this;
		Int res = *this;
		res.Digit.erase(res.Digit.begin(), res.Digit.begin() + k);
		return res;
	}

	Int operator <<(int k);

	Int operator !() {
		Int res = *this;
		res.sign = false;
		return res;
	}

	operator string() {
		string s;
		if (sign) s += "-";
		for (int i = Digit.size() - 1; i > -1; i--)
			s += (Digit[i] + '0');
		return s;
	}

	bool operator == (const Int& n) {
		if (n.sign != sign && Digit[0] != 0) return false;
		if (n.Digit.size() != Digit.size()) return false;
		for (int i = 0; i < Digit.size(); i++)
			if (Digit[i] != n.Digit[i]) return false;
		return true;
	}

	bool operator != (const Int& n) {
		return !(*this == n);
	}

	bool operator > (const Int& n) {
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

	bool operator < (const Int& n) {
		return !(*this > n) && !(*this == n);
	}

	bool operator >= (const Int& n) {
		return (*this > n) || (*this == n);
	}

	bool operator <= (const Int& n) {
		return !(*this > n);
	}

	bool neg() { return sign; }

	int operator[](int i) const {
		return Digit[i];
	}
};

Int Int::operator + (const Int& n) {
	Int a = (*this);
	Int b = n;
	Int c;

	if (a.sign ^ b.sign) {
		if (!a > !b) {
			c = !a - !b;
			c.sign = a.sign;
		}
		else {
			c = !b - !a;
			c.sign = b.sign;
		}
	}
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

Int Int::operator - (const Int& n) {
	Int a = *this;
	Int b = n;
	Int c;

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
	else {
		c = b - a;
		c.sign = ~c.sign;
	}
	return c;
}

Int Int::doubled() {
	return (*this) + (*this);
}

Int Int::operator <<(int k) {
	Int res = (*this);
	while (k--)
		res = res.doubled();
	return res;
}

Int Int::halved(int& rem) {
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
