#pragma once

#include "Int.h"
#include <algorithm>
#include <cmath>

class Float {
private:
	Int data;
	int exp;
public:
	Float() {
		data = Int();
		exp = 0;
	}

	Float(string s) {
		int pos = s.find('.');
		if (pos != string::npos) {
			exp = s.size() - pos - 1;
			s = s.erase(pos, 1);
		}
		else {
			exp = 0;
		}
		data = Int(s);
	}

	Float(int n) {
		data = Int(n);
		exp = 0;
	}

	Float& operator = (const Float& f) {
		data = f.data;
		exp = f.exp;
		return (*this);
	}

	void input() {
		string s;
		cin >> s;
		int pos = s.find('.');
		exp = s.size() - pos - 1;
		s = s.erase(pos, 1);
		data = Int(s);
	}

	void print() {
		cout << string(data) + "E-" + to_string(exp) << endl;
	}

	operator string() {
		string res = string(data);

		bool sign = (res[0] == '-');

		if (sign) 
			res.erase(0, 1);
		
		int n = res.size();
		while (exp > res.size())
			res = '0' + res;
		
		if (exp >= n)
			res = "0." + res;
		else if (exp > 0) {
			res.insert(res.begin() + n - exp, '.');
		}

		if (sign) 
			res.insert(res.begin(), '-');

		return res;
	}

	Float operator + (const Float& f) {
		Float a, b, res;
		res.exp = max(exp, f.exp);

		a.data = data.tenfold(res.exp - exp);
		b.data = f.data.tenfold(res.exp - f.exp);

		res.data = a.data + b.data;
		return res.normalize();
	}

	Float operator - (const Float& f) {
		Float a, b, res;
		res.exp = max(exp, f.exp);

		a.data = data.tenfold(res.exp - exp);
		b.data = f.data.tenfold(res.exp - f.exp);

		res.data = a.data - b.data;
		return res.normalize();
	}

	Float doubled() {
		Float res = *this;
		res.data = res.data.doubled();
		return res.normalize();
	}

	Float halved() {
		Float res = *this;
		if (res.data.isOdd()) {
			res.data = res.data.tenfold(1);
			res.exp++;
		}
		int r;
		res.data = res.data.halved(r);
		return res.normalize();
	}

	Float& normalize() {
		int len = 0;
		while (data[len] == 0 && len < exp) len++;

		int k = min(exp, len);
		data = data.tenth(k);
		exp -= k;

		return *this;
	}

	Float operator << (int k) {
		Float res = *this;
		while (k--) res = res.doubled();
		return res;
	}

	Float operator >> (int k) {
		Float res = *this;
		while (k--) res = res.halved();
		return res;
	}

	Float operator ~() const {
		Float res = *this;
		res.data = ~res.data;
		return res;
	}
};