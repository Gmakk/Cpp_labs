#pragma once
#include <iostream>
#include "Plate.h"
#include <vld.h>

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
int D_AddContact(Plate& plate);
int D_Info(Plate& plate);
int D_Correct(Plate& plate);
int D_AddLink(Plate& plate);
int D_Group(Plate& plate);
int D_Length(Plate& plate);