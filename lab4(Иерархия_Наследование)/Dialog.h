#pragma once
#include "Army.h"

template <class T>
int getValue(T& value) {
	while (true) {
		std::cin >> value;
		if (std::cin.fail())
		{
			std::cin.clear();//очистка ввода
			std::cin.ignore(32767, '\n');
			std::cout << "Invalid input" << std::endl;
		}
		else {
			std::cin.ignore(32767, '\n');
			return 1;
		}
	}
}

template <class T>
int getPositive(T& value) {//ввод только положительных значений
	T buf;
	bool check = 0;
	do {//ожидание корректного ввода
		getValue(buf);
		if (check == 1 || buf < 0)
			std::cout << "Enter positive number" << std::endl;
		check = 1;
	} while (buf < 0);
	value = buf;
	return 1;
}

int dialog(const char* msgs[], int N);
int D_Show(Exercises& ex);
int D_Commander(Exercises& ex);
int D_Map(Exercises& ex);
int D_Duration(Exercises& ex);
int D_Soldiers(Exercises& ex);