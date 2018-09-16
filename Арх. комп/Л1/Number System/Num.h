#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;
typedef unsigned short int usi;

class Num {
private:
	usi radix = 2; //Основание системы счисления
	vector<usi> bits; //Биты числа (bits[0] - младший бит)

	void setRadix(usi radix);
	usi getCorrectReadix(usi radix);

	usi charToDigit(char c);
	char digitToChar(usi d);

	Num mulOnDigit(usi digit);

public:
	Num(string num, usi radix = 10);
	Num(unsigned long long num, usi radix = 10);
	Num(Num *num);

	void parse(string num, usi radix = 10);
	void parse(Num &num);

	Num plus(Num &_num);
	Num minus(Num &_num);
	Num mul(Num &_num);
	Num div(Num &_num);
	Num leftShift(unsigned int n);
	short int compare(Num &_num);
	void setSystem(usi _radix);
	
	usi getBit(usi pos);
	void setBit(usi pos, usi val);
	void addToBit(usi pos, usi val);

	usi getRadix();
	unsigned int size();

	Num getCorrectNum(Num &num);
	Num copy();
	void clean();

	string toString();
	unsigned long long toReal();

	friend Num operator + (Num num1, Num num2) { return num1.plus(num2); }
	friend Num operator - (Num num1, Num num2) { return num1.minus(num2); }
	friend Num operator * (Num num1, Num num2) { return num1.mul(num2); }
	friend Num operator / (Num num1, Num num2) { return num1.div(num2); }
	friend Num operator << (Num num, int shift) { return num.leftShift(shift); }
	friend ostream& operator << (ostream &out, Num &num) { return out << num.toString();}
	operator string() { return toString(); }

};

