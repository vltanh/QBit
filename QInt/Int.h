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
	// Nhóm hàm khởi tạo
	Int();
	Int(string s);
	Int(int n);

	// Nhóm hàm lấy/đặt
	void input();
	void print() const;
	bool isNegative() const;
	int operator[](int i) const;
	
	// Nhóm các toán tử
	Int operator +(const Int&) const;
	Int operator -(const Int&) const;
	Int doubled() const;
	Int halved(int&) const;
	Int tenfold(int k) const;
	Int tenth(int k) const;
	Int operator <<(int k) const;
	Int operator !() const;

	// Nhóm so sánh
	bool operator == (const Int& n) const;
	bool operator != (const Int& n) const;
	bool operator > (const Int& n) const;
	bool operator < (const Int& n) const;
	bool operator >= (const Int& n) const;
	bool operator <= (const Int& n) const;

	// Nhóm ép kiểu
	operator string() const;
};