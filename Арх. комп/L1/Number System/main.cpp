#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

#include "Num.h"

using namespace std;
typedef unsigned short int usi;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

template <typename T>
T prompt(const string label = "Введите значение: ");

void runCommad(const string command);
usi askRadix(const string label = "Введите основание СЧ: ");
void assert(string val, string rightVal, string description);

void help(), cls(), add(), sub(), mul(), div();
void leftShift(), compare(), convert(), runTests();

enum Color {Black = 0, Green = 2, Red = 4, White = 15};
void setColor(Color text, Color bg = White);
void printInColor(string str, Color text, Color bg = White);
void resetColor();

int main() {
	setlocale(LC_ALL, "Russian");
	system("color F0");

	string prevCommand = "help";
	help();

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
	else if (command == "cls") cls();

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
		<< "> cls: очистить консоль" << endl
		<< "> 1: повторить последнюю команду" << endl
		<< "> 0: Выход" << endl << endl;
}

void add() {
	usi radix = askRadix();
	Num num1(prompt<string>("Введите первое число: "), radix);
	Num num2(prompt<string>("Введите второе число: "), radix);
	
	cout << endl << num1 << " + " << num2 << ": " << endl;
	printInColor(num1 + num2, Green); cout << endl << endl;
}

void sub() {
	usi radix = askRadix();
	Num num1(prompt<string>("Из числа: "), radix);
	Num num2(prompt<string>("Вычесть: "), radix);

	cout << endl << num1 << " - " << num2 << ": " << endl;
	printInColor(num1 - num2, Green); cout << endl << endl;
}

void mul() {
	usi radix = askRadix();
	Num num1(prompt<string>("Первое число: "), radix);
	Num num2(prompt<string>("Второе число: "), radix);

	cout << endl << num1 << " * " << num2 << ": " << endl;
	printInColor(num1 * num2, Green); cout << endl << endl;
}

void div() {
	usi radix = askRadix();
	Num num1(prompt<string>("Число: "), radix);
	Num num2(prompt<string>("Разделить на: "), radix);

	cout << endl << num1 << " / " << num2 << ": " << endl;
	printInColor(num1 / num2, Green); cout <<  endl << endl;
}

void leftShift() {
	usi radix = askRadix();
	Num num(prompt<string>("Введите число: "), radix);
	unsigned shift = prompt<unsigned>("Сместить на: ");
	shift = min(shift, 1000);

	cout << endl << num << " << " << shift << ": " << endl;
	printInColor(num << shift, Green); cout << endl << endl;
}

void compare() {
	usi radix1 = askRadix("Введите основание СЧ первого числа: ");
	Num num1(prompt<string>("Первое число: "), radix1);
	usi radix2 = askRadix("Введите основание СЧ второго числа: ");
	Num num2(prompt<string>("Второе число: "), radix2);

	string res = "Такое же как число";
	if (num1.compare(num2) == 1) res = "Больше чем число";
	else if (num1.compare(num2) == -1) res = "Меньше чем число";
	
	cout << endl << "Число " << num1 << "(" << num1.getRadix() << ")" << endl;
	printInColor(res, Green); 
	cout << ":" << endl << num2 << "(" << num2.getRadix() << ")" << endl << endl;
}

void convert() {
	usi radix1 = askRadix("Введите текущее основание СЧ: ");
	Num num(prompt<string>("Введите число: "), radix1);
	usi radix2 = askRadix("Введите новое основание СЧ: ");

	cout << endl << num << "(" << radix1 << ")" << " -> " << endl;
	num.setSystem(radix2);

	string res = num.toString() + "(" + to_string(num.getRadix()) + ")";
	printInColor(res, Green); cout << endl << endl;
}

void cls() { 
	system("cls"); 
}

usi askRadix(const string label) {
	usi radix = 0;

	while (radix < 2 || radix > 36) {
		radix = prompt<usi>(label);
	}

	return radix;
} 

void runTests() {
	//Add
	cout << "Add (+):" << endl;
	assert(Num("0", 10) + Num("0", 10), "0", "0 + 0 = 0 (10)");
	assert(Num("10", 10) + Num("20", 10), "30", "10 + 20 = 30 (10)");
	assert(Num("999", 10) + Num("1", 10), "1000", "999 + 1 = 1000 (10)");
	assert(Num("111111", 2) + Num("1", 2), "1000000", "111111 + 1 = 1000000 (2)");
	assert(Num("FFFFFF", 16) + Num("1", 16), "1000000", "FFFFFF + 1 = 1000000 (16)");
	assert(Num("99"), Num("100"), "10 + 15 = 100 (Пример ошибки)"); //Пример ошибки
	assert(Num("86"), Num("34"), "99 + 15 = 85 (Пример ошибки)"); //Пример ошибки
	cout << "--------------------------------------------------" << endl;
	//Sub
	cout << "Sub (-):" << endl;
	assert(Num("123", 8) - Num("123", 8), "0", "123 - 123 = 0 (8)");
	assert(Num("1500", 10) - Num("600", 10), "900", "1500 - 600 = 900 (10)");
	cout << "--------------------------------------------------" << endl;
	//Mul
	cout << "Mul (*):" << endl;
	assert(Num("99", 10) * Num("500", 10), "49500", "99 * 500 = 49500 (10)");
	assert(Num("FF", 16) * Num("FF", 16), "FE01", "FF * FF = FE01 (36)");
	cout << "--------------------------------------------------" << endl;
	//Div
	cout << "Div (/):" << endl;
	assert(Num("1500", 10) / Num("7", 10), "214", "1500 / 7 = 214 (10)");
	assert(Num("ZZZ", 36) / Num("10", 36), "ZZ", "ZZZ / 10 = ZZ (36)");
	cout << "--------------------------------------------------" << endl;
	//LeftShift
	cout << "LeftShift (<<):" << endl;
	assert(Num("111", 2) << 3, "111000", "111 << 3 = 111000 (2)");
	assert(Num("ZXCQW", 36) << 2, "ZXCQW00", "ZXCQW << 2 = ZXCQW00 (36)");
	cout << "--------------------------------------------------" << endl;
	//Compare
	cout << "Compare Numbers:" << endl;
	assert(to_string(Num("150", 10).compare(*new Num("120", 10))), "1", "150(10) compare 120(10) -> 1");
	assert(to_string(Num("120", 10).compare(*new Num("150", 10))), "-1", "120(10) compare 150(10) -> -1");
	assert(to_string(Num("FF", 16).compare(*new Num("255", 10))), "0", "FF(16) compare 255(10) -> 0");
	cout << "--------------------------------------------------" << endl;
	//Nunber System
	cout << "Convert Number System:" << endl;
	auto conv = [](string s, usi r1, usi r2) { Num n(s, r1); n.setSystem(r2); return n; };

	assert(conv("15", 10, 2), "1111", "15(10) -> 1111(2)");\
	assert(conv("255", 10, 16), "FF", "255(10) -> FF(16)");
	assert(conv("FFFFFF", 16, 8), "77777777", "FFFFFF(16) -> 77777777(8)");
	assert(conv("10000000000000", 2, 10), "8192", "10000000000000(2) -> 8192(10)");
	assert(conv("10000000000000", 2, 16), "2000", "10000000000000(2) -> 2000(16)");

	cout << endl;
}

void assert(string val, string rightVal, string description) {
	bool ok = (val == rightVal);

	cout << "- ";
	printInColor((ok ? "OK" : "FAIL"), (ok ? Green : Red));
	cout << ":\t" << description;

	if (!ok) printInColor(string("\t got: ") + val, Red);
	cout << endl;
}

/**
* Запрашивает от пользователя значение нужного типа
*
* Пример работы:
* prompt<int>("Введите целое число: ");
* prompt<string>("Введите строку: ");
*/
template <typename T>
T prompt(const string label) {
	cout << label;

	while (true) {
		T val; cin >> val;

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

void resetColor() {
	SetConsoleTextAttribute(hConsole, (WORD)((White << 4) | Black));
};

void setColor(Color text, Color bg) {
	SetConsoleTextAttribute(hConsole, (WORD)((bg << 4) | text));
};

void printInColor(string str, Color text, Color bg) {
	setColor(text, bg); 
	cout << str;
	resetColor();
}