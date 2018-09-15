#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef unsigned short int usi;

class Number {
private:
	usi radix = 2; //Основание системы счисления
	vector<usi> bits; //Биты числа (bits[0] - младший бит)

	void setRadix(usi radix) {
		this->radix = getCorrectReadix(radix);
	}

	usi getCorrectReadix(usi radix) {
		if (radix < 2) radix = 2;
		else if (radix > 36) radix = 36;

		return radix;
	}

	usi charToDigit(char c) {
		c = toupper(c);

		if (c >= '0' && c <= '9') return c - '0';
		if (c >= 'A' && c <= 'Z') return 10 + (c - 'A');
		return 0;
	}

	char digitToChar(usi d) {
		if (d >= 0 && d <= 9) return d + '0';
		if (d >= 10 && d <= 35) return (d + 'A') - 10;
		return '*';
	}

	//Возвращает число num в виде строки в нужной СЧ
	string getStrNumInSystem(unsigned long long num, usi radix) {
		string res = "";

		while (num >= radix) {
			res  = digitToChar(num % radix) + res;
			num /= radix;
		}

		res = digitToChar(usi(num)) + res;
		return res;
	}

public:
	Number(string strNum, usi radix = 10) {
		parse(strNum, radix);
	}

	Number(unsigned long long num) {
		parse(to_string(num), radix);
	}

	Number(Number *num) {
		parse(*num);
	}

	void parse(string strNum, usi radix = 10) {
		setRadix(radix);
		if (strNum == "") strNum = "0";

		int len = strNum.length();
		bits.reserve(len);

		for (int i = len - 1; i >= 0; i--) {
			usi bit = charToDigit(strNum[i]);

			//Биты не могут быть больше основания СЧ
			if (bit >= getRadix()) {
				bit = getRadix() - 1;
			}

			bits.push_back(bit);
		}

		clean();
	}

	void parse(Number &num) {
		this->radix = num.radix;
		this->bits = num.bits;
	}

	//Возвращает бит находящийся на позиции pos
	//Либо 0, если такого разряда нет
	usi getBit(usi pos) {
		return (pos < bits.size()) ? bits[pos] : 0;
	}

	//Устанавливает значение val в бит на позиции pos
	void setBit(usi pos, usi val) {
		if (pos >= bits.size()) bits.push_back(val);
		else bits[pos] = val;
	} 

	//Добавляет к биту на позиции pos значение val
	void addToBit(usi pos, usi val) {
		if (val == 0) return; 
		setBit(pos, getBit(pos) + val);
	}

	usi getRadix() {
		return radix;
	}

	void setSystem(usi radix) {
		if (this->radix == radix) return;
		radix = getCorrectReadix(radix); 

		unsigned long long all = 0;
		for (int i = bits.size() - 1; i >= 0; i--) {
			all = (all * this->radix) + getBit(i);
		}
		
		Number res(getStrNumInSystem(all, radix), radix);
		parse(res);
	}

	//Cумирует даное число с переданным числом
	//Числа могут быть в разных СЧ (результат в СЧ даного числа)
	Number plus(const Number &_num) {
		Number num1 = copy();
		Number num2 = getCorrectNum(_num);

		int len1 = num1.bits.size();
		int len2 = num2.bits.size();

		usi radix = num1.getRadix();
		
		for (int i = 0; i < len1 || i < len2; i++) {
			usi sum = num1.getBit(i) + num2.getBit(i);

			num1.setBit(i, sum % radix);
			num1.addToBit(i + 1, sum / radix);
		}

		num1.clean();
		return num1;
	}

	Number minus(const Number &_num) {
		Number num1 = copy();
		Number num2 = getCorrectNum(_num);

		int len1 = num1.bits.size();
		int len2 = num2.bits.size();

		usi radix = num1.getRadix();

		if (len1 < len2) {
			num1.parse("0", radix);
			return num1;
		}

		for (int i = 0; i < len1; i++) {
			//тип sub должен допускать отрецательные значения
			short sub = num1.getBit(i) - num2.getBit(i); 

			if (sub < 0) {
				sub += radix; //Окончательное значение текущего бита

				bool noBits = true;
				int j;

				//Ищем бит, у которого можно взять 1
				for (j = i + 1; j < len1; j++) {
					if (num1.getBit(j) != 0) {
						num1.addToBit(j, -1);
						noBits = false;
						break;
					}
				}

				if (noBits) {
					num1.parse("0", radix);
					return num1;
				}

				//Добавляем по 1 всем промежуточным битам
				for (j = j - 1; j > i; j--) {
					num1.setBit(j, radix - 1);
				}
			}

			num1.setBit(i, sub);
		}

		num1.clean();
		return num1;
	}

	Number mul(const Number &_num) {
		Number num1 = copy();
		Number num2 = getCorrectNum(_num);

		int len1 = num1.bits.size();
		int len2 = num2.bits.size();

		usi radix = num1.getRadix();
		Number res("0", radix);

		for (int i = 0; i < len2; i++) {
			res = res + num1.mulOnDigit(num2.getBit(i)).leftShift(i);
		}

		num1.clean();
		return num1;
	}

	Number leftShift(unsigned int n) {
		Number num = copy();
		vector<usi> shift(n, 0);
		
		num.bits.insert(num.bits.begin(), shift.begin(), shift.end());

		return num;
	}

	Number mulOnDigit(usi digit) {
		Number num = copy();
		usi radix = num.getRadix();
		if (digit >= radix) digit = radix - 1;

		int len = num.bits.size();
		int rest = 0;

		for (int i = 0; i < len; i++) {
			int mul = num.getBit(i) * digit + rest;
			num.setBit(i, mul % radix);

			rest = mul / radix;
		}

		if (rest) num.setBit(len, rest);

		return num;
	}

	Number getCorrectNum(Number num) {
		Number res = num.copy();
		
		if (res.getRadix() != getRadix()) {
			res.setSystem(getRadix());
		}

		return res;
	}

	Number copy() {
		return Number(this);
	}

	//Удаляет мусор из числа
	void clean() {
		cleanHighZiros();
	}

	void cleanHighZiros() {
		int len = bits.size();
		if (len <= 1 || getBit(len - 1) != 0) return;

		int noZiroIndex = -1;

		for (int i = len - 1; i >= 0; i--) {
			if (getBit(i) != 0) {
				noZiroIndex = i;
				break;
			}
		}

		if (noZiroIndex == -1) {
			bits = {0};
			return;
		}

		vector<usi> newBits(bits.begin(), bits.begin() + noZiroIndex + 1);
		bits = newBits;
	}

	string toString() {
		string strNum = "";
		int len = bits.size();

		for (int i = len - 1; i >= 0; i--) {
			strNum += digitToChar(bits[i]);
		}

		return strNum;
	}

	friend Number operator + (Number &num1, const Number &num2) {
		return num1.plus(num2);
	}

	friend Number operator - (Number &num1, const Number &num2) {
		return num1.minus(num2);
	}

	friend Number operator << (Number &num, int shift) {
		return num.leftShift(shift);
	}

	friend ostream& operator << (ostream &out, Number &num) {
		out << num.toString();
		return out;
	}
	
};
 
void run();
void runTests(); 
void assert(string val, string rightVal, string description);
  
int main() {
	//run();
	//runTests();

	string n;
	usi d, radix;

	Number a("132", 10);
	a = a << 3;
	cout << a << endl;

	while (0) {
		cin >> radix >> n >> d;

		Number num(n, radix);
		cout << "in:  " << num << endl;

		num = num.mulOnDigit(d);
		cout << "out: " << num << endl;

		cout << "-----------" << endl;
	}

	system("pause");
	return 0;
}

void run() {
	cout << "Working" << endl;
}

void runTests() {
	cout << "Converting:" << endl;
}

void assert(string val, string rightVal, string description) {
	cout << (val == rightVal ? "OK" : "FAIL") << ":\t" << description << endl;
}