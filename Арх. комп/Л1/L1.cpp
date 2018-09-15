#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

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

public:
	Number(string strNum, usi radix = 10) {
		parse(strNum, radix);
	}

	Number(unsigned long long num, usi radix = 10) {
		parse(to_string(num), radix);
	}

	Number(Number *num) {
		parse(*num);
	}

	void parse(string strNum, usi radix = 10) {
		setRadix(radix);
		if (strNum == "") strNum = "0";

		int len = strNum.length();

		bits.clear();
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
		Number numRadix(radix, 10);

		//Calc RealNumber
		Number curRadix = Number(getRadix(), 10);
		Number all("0", 10);

		if (getRadix() == 10) {
			all.parse(*this);
		} 
		else {
			for (int i = bits.size() - 1; i >= 0; i--) {
				Number bit(getBit(i));
				all = (all * curRadix).plus(bit);
			}
		}

		//To result
		string res = "";

		while (all.compare(numRadix) >= 0) {
			Number div = all / numRadix;
			Number a = div * numRadix;
			usi remainder = usi((all - a).toReal());

			res = digitToChar(remainder) + res;
			all = Number(div);
		}

		res = digitToChar(all.toReal()) + res;
		parse(*new Number(res, radix));
	}

	//Cумирует даное число с переданным числом
	//Числа могут быть в разных СЧ (результат в СЧ даного числа)
	Number plus(Number &_num) {
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

	Number minus(Number &_num) {
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
			//тип sub должен допускать отрицательные значения
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

	Number mul(Number &_num) {
		Number num1 = copy();
		Number num2 = getCorrectNum(_num);

		int len1 = num1.bits.size();
		int len2 = num2.bits.size();

		usi radix = num1.getRadix();
		Number res("0", radix);

		for (int i = 0; i < len2; i++) {
			Number next = num1.mulOnDigit(num2.getBit(i)).leftShift(i);
			res = res + next;
		}

		res.clean();
		return res;
	}

	Number div(Number &_num) {
		Number num1 = copy();
		Number num2 = getCorrectNum(_num);

		//Div on 0

		int len2 = num2.bits.size();

		usi radix = num1.getRadix();
		Number res("0", radix);
		Number tmp("0", radix);
		Number one("1", radix);

		int n = 1;

		while (num1.compare(num2) >= 0) {
			auto b = num1.bits.begin() + num1.bits.size();
			vector<usi> tmpBits(b - n, b);
			tmp.bits = tmpBits;

			if (tmp.compare(num2) == -1) {
				n++;
				continue;
			}

			Number next("0", radix);
			Number k("0", radix);

			while (true) {
				next = next + num2;

				if (next.compare(tmp) > 0) {
					next = next - num2;
					break;
				};

				k = k + one;
			}

			int shift = num1.bits.size() - tmp.bits.size();
			next = next << shift;
			k = k << shift;

			num1 = num1 - next;
			res = res + k;

			n = 1;
			k = Number("0", radix);
		}

		res.clean();
		return res;
	}

	//Сравнивает данное число в переданным
	//Если оно больше то возв.: 1, меньше: -1, одинаковые: 0
	short int compare(Number &_num) {
		Number num = getCorrectNum(_num);
		num.clean();
		clean();

		int len1 = bits.size();
		int len2 = num.bits.size();

		if (len1 > len2) return 1;
		else if (len1 < len2) return -1;

		for (int i = len1 - 1; i >= 0; i--) {
			if (getBit(i) > num.getBit(i)) return 1;
			else if (getBit(i) < num.getBit(i)) return -1;
		}

		return 0;
	}

	Number leftShift(unsigned int n) {
		Number num = copy();
		vector<usi> shift(n, 0);

		num.bits.insert(num.bits.begin(), shift.begin(), shift.end());

		return num;
	}

	Number getCorrectNum(Number &num) {
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

	//Возвращает реальное число 
	//Число не должно быть слишком большим
	unsigned long long toReal() {
		unsigned long long all = 0;

		for (int i = bits.size() - 1; i >= 0; i--) {
			all = all * getRadix() + getBit(i);
		}

		return all;
	}

	friend Number operator + (Number &num1, Number &num2) {
		return num1.plus(num2);
	}

	friend Number operator - (Number &num1, Number &num2) {
		return num1.minus(num2);
	}

	friend Number operator * (Number &num1, Number &num2) {
		return num1.mul(num2);
	}

	friend Number operator / (Number &num1, Number &num2) {
		return num1.div(num2);
	}

	friend Number operator << (Number &num, int shift) {
		return num.leftShift(shift);
	}

	friend ostream& operator << (ostream &out, Number &num) {
		out << num.toString();
		return out;
	}

	operator string() {
		return toString();
	}
	
};

void help();		void clean();	void add();
void sub();			void mul();		void div();
void leftShift();	void compare();	void convert();
void runTests();

void runCommad(const string command);
usi askRadix(const string label = "Введите основание СЧ: ");

void assert(string val, string rightVal, string description);
Number &get(string num, usi radix);

template <typename T>
T prompt(const string label = "Введите значение: ");

enum ConsoleColor {	Black = 0, Green = 2, Red = 4, White = 15, LightGray = 7};

void resetColor() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((White << 4) | Black));
};

void setColor(ConsoleColor text, ConsoleColor bg = White) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((bg << 4) | text));
};

void printInColor(string str, ConsoleColor text, ConsoleColor bg = White) {
	setColor(bg, text);
	cout << str;
	resetColor();
}

int main() {
	setlocale(LC_ALL, "Russian");
	system("color F0");

	help();
	string prevCommand = "help";

	while (true) {
		string command = prompt<string>("> ");
		if (command == "0") return 0;

		if (command == "1") {
			cout << "> " << prevCommand << endl;
			runCommad(prevCommand);
		}
		else {
			prevCommand = command;
			runCommad(command);
		}
	}

	return 0;
}

void runCommad(const string command) {
	if (command == "add") add();
	else if (command == "sub") sub();
	else if (command == "mul") mul();
	else if (command == "div") div();
	else if (command == "leftShift") leftShift();
	else if (command == "compare") compare();
	else if (command == "convert") convert();
	else if (command == "runTests") runTests();

	else if (command == "help") help();
	else if (command == "clean") clean();

	else cout << "Команда не найдена" << endl;
}

void help() {
	cout << "- - - Number System 0.0.1 - - -" << endl << endl
		<< "> add: Cуммирование (+)" << endl
		<< "> sub: Вичитание (-)" << endl
		<< "> mul: Умножение (*)" << endl
		<< "> div: Деление (/)" << endl
		<< "> leftShift: Сдвиг влево (<<)" << endl
		<< "> compare: Сравнить числа" << endl
		<< "> convert: Изменить систему счисления" << endl
		<< "> runTests: Запустить тесты" << endl << endl
		
		<< "> help: помощь" << endl
		<< "> clean: очистить консоль" << endl
		<< "> 1: повторить последнюю команду" << endl
		<< "> 0: Выход" << endl << endl;
}

void clean() {
	system("cls");
}

void add() {
	usi radix = askRadix();
	Number num1(prompt<string>("Введите первое число: "), radix);
	Number num2(prompt<string>("Введите второе число: "), radix);
	
	cout << endl << num1 << " + " << num2 << ": " << endl;
	cout << (num1 + num2).toString() << endl << endl;
}

void sub() {
	usi radix = askRadix();
	Number num1(prompt<string>("Из числа: "), radix);
	Number num2(prompt<string>("Вычесть: "), radix);

	cout << endl << num1 << " - " << num2 << ": " << endl;
	cout << (num1 - num2).toString() << endl << endl;
}

void mul() {
	usi radix = askRadix();
	Number num1(prompt<string>("Первое число: "), radix);
	Number num2(prompt<string>("Второе число: "), radix);

	cout << endl << num1 << " * " << num2 << ": " << endl;
	cout << (num1 * num2).toString() << endl << endl;
}

void div() {
	usi radix = askRadix();
	Number num1(prompt<string>("Число: "), radix);
	Number num2(prompt<string>("Разделить на: "), radix);

	cout << endl << num1 << " / " << num2 << ": " << endl;
	cout << (num1 / num2).toString() << endl << endl;
}

void leftShift() {
	usi radix = askRadix();
	Number num(prompt<string>("Введите число: "), radix);
	unsigned short shift = prompt<unsigned short>("Сместить на: ");
	if (shift > 1000) shift = 1000;

	cout << endl << num << " << " << shift << ": " << endl;
	cout << (num << shift).toString() << endl << endl;
}

void compare() {
	usi radix1 = askRadix("Введите основание СЧ первого числа: ");
	Number num1(prompt<string>("Первое число: "), radix1);

	usi radix2 = askRadix("Введите основание СЧ второго числа: ");
	Number num2(prompt<string>("Второе число: "), radix2);

	string res = "Такое же как число";
	if (num1.compare(num2) == 1) res = "Больше чем число";
	else if (num1.compare(num2) == -1) res = "Меньше чем число";
	
	cout << endl << "Число " << num1 << "(" << num1.getRadix() << ")" << endl;
	printInColor(res, Green); 
	cout << ":" << endl << num2 << "(" << num2.getRadix() << ")" << endl << endl;
}

void convert() {
	usi radix1 = askRadix("Введите текущее основание СЧ: ");
	Number num(prompt<string>("Введите число: "), radix1);
	usi radix2 = askRadix("Введите новое основание СЧ: ");

	cout << endl << num << "(" << radix1 << ")" << " -> " << endl;
	num.setSystem(radix2);

	string res = num.toString() + "(" + to_string(num.getRadix()) + ")";
	printInColor(res, Green);
	cout << endl << endl;
}

usi askRadix(const string label) {
	usi radix = 0;

	while (radix < 2 || radix > 36) {
		radix = prompt<usi>(label);
	}

	return radix;
} 

void runTests() {
	Number num1("0", 10), num2("0", 10);

	//Add
	cout << "Add (+):" << endl;
	assert(get("0", 10) + get("0", 10), "0", "0 + 0 = 0 (10)");
	assert(get("10", 10) + get("20", 10), "30", "10 + 20 = 30 (10)");
	assert(get("999", 10) + get("1", 10), "1000", "999 + 1 = 1000 (10)");
	assert(get("111111", 2) + get("1", 2), "1000000", "111111 + 1 = 1000000 (2)");
	assert(get("FFFFFF", 16) + get("1", 16), "1000000", "FFFFFF + 1 = 1000000 (16)");
	//Пример ошибки
	assert("99", "100", "10 + 15 = 100 (fail)");
	assert("86", "100", "99 + 15 = 85 (fail)");
	cout << "--------------------------------------------------" << endl;
	//Sub
	cout << "Sub (-):" << endl;
	assert(get("123", 8) - get("123", 8), "0", "123 - 123 = 0 (8)");
	assert(get("1500", 10) - get("600", 10), "900", "1500 - 600 = 900 (10)");
	cout << "--------------------------------------------------" << endl;
	//Mul
	cout << "Mul (*):" << endl;
	assert(get("99", 10) * get("500", 10), "49500", "99 * 500 = 49500 (10)");
	assert(get("FF", 16) * get("FF", 16), "FE01", "FF * FF = FE01 (36)");
	cout << "--------------------------------------------------" << endl;
	//Div
	cout << "Div (/):" << endl;
	assert(get("1500", 10) / get("7", 10), "214", "1500 / 7 = 214 (10)");
	assert(get("ZZZ", 36) / get("10", 36), "ZZ", "ZZZ / 10 = ZZ (36)");
	cout << "--------------------------------------------------" << endl;
	//LeftShift
	cout << "LeftShift (<<):" << endl;
	assert(get("111", 2) << 3, "111000", "111 << 3 = 111000 (2)");
	assert(get("ZXCQW", 36) << 2, "ZXCQW00", "ZXCQW << 2 = ZXCQW00 (36)");
	cout << "--------------------------------------------------" << endl;
	//Compare
	cout << "Compare Numbers:" << endl;
	assert(to_string(get("150", 10).compare(get("120", 10))), "1", "150(10) compare 120(10) -> 1");
	assert(to_string(get("120", 10).compare(get("150", 10))), "-1", "120(10) compare 150(10) -> -1");
	assert(to_string(get("FF", 16).compare(get("255", 10))), "0", "FF(16) compare 255(10) -> 0");
	cout << "--------------------------------------------------" << endl;
	//Nunber System
	Number num("0", 10);
	cout << "Convert Number System:" << endl;

	num.parse("15", 10); num.setSystem(2);
	assert(num, "1111", "15(10) -> 1111(2)");

	num.parse("255", 10); num.setSystem(16);
	assert(num, "FF", "255(10) -> FF(16)");

	num.parse("FFFFFF", 16); num.setSystem(8);
	assert(num, "77777777", "FFFFFF(16) -> 77777777(8)");

	num.parse("10000000000000", 2); num.setSystem(10);
	assert(num, "8192", "10000000000000(2) -> 8192(10)");

	num.parse("10000000000000", 2); num.setSystem(16);
	assert(num, "2000", "10000000000000(2) -> 2000(16)");

	cout << endl;
}

Number &get(string num, usi radix) {
	return *(new Number(num, radix));
}

void assert(string val, string rightVal, string description) {
	bool pass = (val == rightVal);

	cout << "- ";
	printInColor((pass ? "OK" : "FAIL"), (pass ? Green : Red));
	cout << ":\t" << description;

	if (val != rightVal) {
		printInColor(string("\t got: ") + val + " ", Red);
	}

	cout << endl;
}

/**
* Запрашивает от пользователя значение нужного типа
* @param{char[]} label - текст, предложенный пользователю
*
* Привет работы:
* prompt<int>("Введите целое число: ");
* prompt<char>("Введите символ: ");
* prompt<string>("Введите строку: ");
*/
template <typename T>
T prompt(const string label) {
	cout << label;

	while (true) {
		T val;
		cin >> val;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Произошла ошибка. Введите еще раз: ";
		}
		else {
			cin.ignore(32767, '\n');
			return val;
		}
	}

}