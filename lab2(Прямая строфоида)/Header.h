#pragma once
#include <iostream>
#include <vld.h>
#include <Strophoid.h>


int dialog(const char* msgs[], int N);

template <class T>
int getValue(T& value) {
	while (true) {
		std::cin >> value;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			std::cout << "Invalid input\n";
		}
		else {
			std::cin.ignore(32767, '\n');
			return 1;
		}
	}
}

int D_Show(strophoid* object);
int D_Change(strophoid* object);
int D_Coord(strophoid* object);
int D_Dist(strophoid* object);
int D_Rad(strophoid* object);
int D_Square(strophoid* object);
int D_Volume(strophoid* object);
int D_Asympt(strophoid* object);