#include "Num.h"

void Num::setRadix(usi radix) {
	this->radix = getCorrectReadix(radix);
}

// Возвращает корректное значение основания СЧ radix (от 2 до 36)
usi Num::getCorrectReadix(usi radix) {
	if (radix < 2) radix = 2;
	else if (radix > 36) radix = 36;

	return radix;
}

usi Num::charToDigit(char c) {
	c = toupper(c);

	if (c >= '0' && c <= '9') return c - '0';
	if (c >= 'A' && c <= 'Z') return 10 + (c - 'A');
	return 0;
}

char Num::digitToChar(usi d) {
	if (d >= 0 && d <= 9) return d + '0';
	if (d >= 10 && d <= 35) return (d + 'A') - 10;
	return '*';
}

//Умножение на одну цифру
Num Num::mulOnDigit(usi digit) {
	Num num = copy();
	usi radix = num.getRadix();
	if (digit >= radix) digit = radix - 1;

	int len = num.size();
	int rest = 0;

	for (int i = 0; i < len; i++) {
		int mul = num.getBit(i) * digit + rest;
		num.setBit(i, mul % radix);

		rest = mul / radix;
	}

	if (rest) num.setBit(len, rest);

	return num;
}

Num::Num(string num, usi radix) {
	parse(num, radix);
}

Num::Num(unsigned long long num, usi radix) {
	parse(to_string(num), 10);
	setSystem(radix);
}

Num::Num(Num *num) {
	parse(*num);
}

void Num::parse(string num, usi radix) {
	if (num == "") num = "0";
	bits.clear();
	setRadix(radix);

	for (int i = num.length() - 1; i >= 0; i--) {
		usi bit = min(charToDigit(num[i]), getRadix() - 1);
		bits.push_back(bit);
	}

	clean();
}

void Num::parse(Num &num) {
	this->radix = num.radix;
	this->bits = vector<usi>(num.bits.begin(), num.bits.end());
}

Num Num::plus(Num &_num) {
	Num num1 = copy(), num2 = getCorrectNum(_num);
	int len1 = num1.size(), len2 = num2.size();
	usi radix = num1.getRadix();

	for (int i = 0; i < len1 || i < len2; i++) {
		usi sum = num1.getBit(i) + num2.getBit(i);

		num1.setBit(i, sum % radix);
		num1.addToBit(i + 1, sum / radix);
	}

	num1.clean();
	return num1;
}

Num Num::minus(Num &_num) {
	Num num1 = copy(), num2 = getCorrectNum(_num);
	int len1 = num1.size(), len2 = num2.size();
	usi radix = num1.getRadix();

	if (len1 < len2) return Num(0, radix);

	for (int i = 0; i < len1; i++) {
		short sub = num1.getBit(i) - num2.getBit(i); //sub может быть отрицательным

		if (sub < 0) {
			sub += radix; //Окончательное значение текущего бита
			int notZiro = -1;

			//Ищем бит, у которого можно взять 1
			for (int j = i + 1; j < len1; j++) {
				if (num1.getBit(j) != 0) {
					num1.addToBit(j, -1);
					notZiro = j;
					break;
				}
			}

			if (notZiro == -1) return Num(0, radix);

			//Добавляем по 1 всем промежуточным битам
			for (int j = notZiro - 1; j > i; j--) {
				num1.setBit(j, radix - 1);
			}
		}
		num1.setBit(i, sub);
	}

	num1.clean();
	return num1;
}

Num Num::mul(Num &_num) {
	Num num1 = copy(), num2 = getCorrectNum(_num);
	int len1 = num1.bits.size(), len2 = num2.bits.size();
	usi radix = num1.getRadix();

	Num res(0, radix);
	for (int i = 0; i < len2; i++) {
		res = res + (num1.mulOnDigit(num2.getBit(i)) << i);
	}

	res.clean();
	return res;
}

Num Num::div(Num &_num) {
	Num num1 = copy(), num2 = getCorrectNum(_num);
	usi radix = num1.getRadix();

	if (Num(0, radix).compare(_num) == 0) {
		return Num(0, radix);
	}

	Num res("0", radix), tmp("0", radix);
	int n = 1;

	while (num1.compare(num2) >= 0) {
		auto b = num1.bits.begin() + num1.size();
		tmp.bits = vector<usi>(b - n, b);

		if (tmp.compare(num2) == -1) {
			n++;
			continue;
		}

		Num next(0, radix), k(0, radix);
		while (true) {
			next = next + num2;

			if (next.compare(tmp) > 0) {
				next = next - num2;
				break;
			};

			k = k + Num(1);
		}

		int shift = num1.size() - tmp.size();
		num1 = num1 - (next << shift);
		res = res + (k << shift);

		n = 1;
	}

	res.clean();
	return res;
}

Num Num::leftShift(unsigned int n) {
	Num num = copy();
	vector<usi> shift(n, 0);

	num.bits.insert(num.bits.begin(), shift.begin(), shift.end());
	return num;
}

//Сравнивает данное число c переданным
//Если оно больше то возв.: 1, меньше: -1, одинаковые: 0
short int Num::compare(Num &_num) {
	Num num = getCorrectNum(_num);
	num.clean(); clean();
	int len1 = size(), len2 = num.size();

	if (len1 > len2) return 1;
	else if (len1 < len2) return -1;

	for (int i = len1 - 1; i >= 0; i--) {
		if (getBit(i) > num.getBit(i)) return 1;
		else if (getBit(i) < num.getBit(i)) return -1;
	}

	return 0;
}

void Num::setSystem(usi _radix) {
	if (getRadix() == _radix) return;
	_radix = getCorrectReadix(_radix);

	Num radix(_radix), curRadix(getRadix()), all("0", 10);

	//Собираем все биты в одно число
	if (getRadix() == 10) {
		all.parse(*this);
	}
	else {
		for (int i = size() - 1; i >= 0; i--) {
			all = (all * curRadix) + Num(getBit(i));
		}
	}

	//Разбиваем на нужную СЧ
	string res = "";
	while (all.compare(radix) >= 0) {
		Num div = all / radix;
		usi rem = usi((all - (div * radix)).toReal());

		res = digitToChar(rem) + res;
		all = div;
	}

	res = digitToChar(usi(all.toReal())) + res;
	parse(*new Num(res, _radix));
}

//Возвращает бит находящийся на позиции pos
//Либо 0, если такого разряда нет
usi Num::getBit(usi pos) {
	return (pos < bits.size()) ? bits[pos] : 0;
}

//Устанавливает значение val в бит на позиции pos
void Num::setBit(usi pos, usi val) {
	if (pos >= bits.size()) bits.push_back(val);
	else bits[pos] = val;
}

//Добавляет к биту на позиции pos значение val
void Num::addToBit(usi pos, usi val) {
	if (val == 0) return;
	setBit(pos, getBit(pos) + val);
}

usi Num::getRadix() {
	return radix;
}

//Возвращает количество битов
unsigned int Num::size() {
	return bits.size();
}

Num Num::getCorrectNum(Num &num) {
	Num res = num.copy();
	if (res.getRadix() != getRadix()) res.setSystem(getRadix());

	return res;
}

Num Num::copy() { 
	return Num(this); 
}

//Удаляет мусор из числа
void Num::clean() {
	int len = size();
	if (len <= 1 || getBit(len - 1) != 0) return;

	int noZiroIndex = -1;
	for (int i = len - 1; i >= 0; i--) {
		if (getBit(i) != 0) {
			noZiroIndex = i;
			break;
		}
	}

	if (noZiroIndex == -1) {
		bits = { 0 };
		return;
	}

	bits = vector<usi>(bits.begin(), bits.begin() + noZiroIndex + 1);
}

string Num::toString() {
	string strNum = "";

	for (int i = size() - 1; i >= 0; i--) {
		strNum += digitToChar(bits[i]);
	}

	return strNum;
}

//Возвращает реальное число 
//Число не должно быть слишком большим
unsigned long long Num::toReal() {
	unsigned long long all = 0;

	for (int i = size() - 1; i >= 0; i--) {
		all = all * getRadix() + getBit(i);
	}

	return all;
}
