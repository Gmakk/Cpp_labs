#pragma once
#include "Polygon.h"
#include "cmath"
#include <string>
#include <ctime>
#include <windows.h>
# define M_PI 3.14159265358979323846

int dialog(const char* msgs[], int N);
int D_Circle(laba3::Polygon& polygon);
int D_Square(laba3::Polygon& polygon);
int D_Triangle(laba3::Polygon& polygon);
int D_Show(laba3::Polygon& polygon);
int D_Bear(laba3::Polygon& polygon);
int D_Rabbit(laba3::Polygon& polygon);
int D_Tic_Tac(laba3::Polygon& polygon);

void setLine(laba3::Polygon& polygon, laba3::Item& point1, laba3::Item& point2, const int N1);
void set�ircle(laba3::Polygon& circle, const float radius, const int N, const float x_centre, const float y_centre);//������������� N ����� �� ���������� ����� ������ ����������
void setSquare(laba3::Polygon& square, const float side, const int N, const float x_centre, const float y_centre);//������������� �� N ����� �� ������ ������� ��������
void setTriangle(laba3::Polygon& triangle, laba3::Item& point1, const int N1, laba3::Item& point2, const int N2, laba3::Item& point3, const int N3);//������������� �� N_i ����� �� ������ ������� ������������
void outputPoints(laba3::Polygon& polygon);//������� ����� ������������ ����������
void outputPoints_console(laba3::Polygon& polygon);//������� ��� ����� ����

template <class T>
int getValue(T& value) {
	while (true) {
		std::cin >> value;
		if (std::cin.fail())
		{
			std::cin.clear();//������� �����
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
int getPositive(T& value) {//���� ������ ������������� ��������
	T buf;
	bool check = 0;
	do {//�������� ����������� �����
		getValue(buf);
		if (check == 1 || buf < 0)
			std::cout << "Enter positive number" << std::endl;
		check = 1;
	} while (buf < 0);
	value = buf;
	return 1;
}