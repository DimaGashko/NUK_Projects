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
		if (radix < 2) radix = 2;
		else if (radix > 36) radix = 36;

		this->radix = radix;
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

public:
	Number(string strNum, usi radix = 10) {
		parse(strNum, radix);
	}

	Number(unsigned long long num) {
		parse(to_string(num), radix);
	}

	void parse(string strNum, usi radix = 10) {
		setRadix(radix);

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

	void setNumberSystem(usi newRadix) {
		
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

		return num1;
	}

	Number operator + (const Number &num2) {
		return plus(num2);
	}

	void sub(const Number &_num) {
		Number num = getCorrectNum(_num);

	}

	void div(const Number &_num) {
		Number num = getCorrectNum(_num);

	}

	Number getCorrectNum(Number num) {
		Number res = num.copy();
		
		if (res.getRadix() != getRadix()) {
			res.setNumberSystem(getRadix());
		}

		return res;
	}

	Number copy() {
		return Number(toString());
	}

	string toString() {
		string strNum = "";
		int len = bits.size();

		for (int i = len - 1; i >= 0; i--) {
			strNum += digitToChar(bits[i]);
		}

		return strNum;
	}
};
 
void run();
void runTests(); 
void assert(string val, string rightVal, string description);
  
int main() {
	//run();
	//runTests();

	string n1, n2;
	usi radix;

	while (1) {
		cin >> radix >> n1 >> n2;

		Number num1(n1, radix);
		Number num2(n2, radix);

		Number res = num1 + num2;

		cout << res.toString() << endl;
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





/*#include <iostream>

#include <string>
#include <algorithm>

using namespace std;

string correctNum(string num);
string addNumbers(string num1, string num2, short int radix);
string divNumbers(string num1, string num2, short int radix);

int main() {
	run();
	runTests();
	string num1 = "", num2 = "";
	int radix = 2;
	cin >> num1 >> num2 >> radix;

	num1 = correctNum(num1);
	num2 = correctNum(num2);

	cout << addNumbers(num1, num2, radix);
	
	cout << (addNumbers("111", "333", 10) == "444");
	cout << (addNumbers("123", "321", 10) == "444");
	cout << (addNumbers("0123", "00321", 10) == "444");

	cout << (addNumbers("1", "11", 2) == "100");
	cout << (addNumbers("1001", "101", 2) == "1110");

	system("pause");
	return 0;
}

string addNumbers(string num1, string num2, short int radix) {
	return "";
}

string divNumbers(string num1, string num2, short int radix) {
	return "";
}

string correctNum(string num) {
	transform(num.begin(), num.end(), num.begin(), tolower);
	return num;
}

*/