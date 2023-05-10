#include "Dialog.h"
#include <iostream>

int dialog(const char* msgs[], int N) {
	int rc;
	int i, n;
	do {
		for (i = 0; i < N; ++i)
			puts(msgs[i]);
		puts("Make your choice:");
		n = getValue(rc);
		if (n == 0)
			rc = 0;
	} while (rc < 0 || rc >= N);
	return rc;
}

int D_Circle(laba3::Polygon& polygon) {
	float x, y, size;
	int number;
	std::cout << "Enter the coordinates of the center" << std::endl;
	getValue(x);
	getValue(y);
	std::cout << "Enter the radius and the number of points on the circle" << std::endl;
	getPositive(size);
	getPositive(number);
	try {
		setСircle(polygon, size, number, x, y);
		outputPoints_console(polygon);
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
	return 1;
}

int D_Square(laba3::Polygon& polygon) {
	float x, y, size;
	int number;
	std::cout << "Enter the coordinates of the center" << std::endl;
	getValue(x);
	getValue(y);
	std::cout << "Enter the size of the side and the number of points on it." << std::endl;
	getPositive(size);
	getPositive(number);
	try {
		setSquare(polygon, size, number, x, y);
		outputPoints_console(polygon);
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
	return 1;
}

int D_Triangle(laba3::Polygon& polygon) {
	int N1, N2, N3;
	laba3::Item point1, point2, point3;
	std::cout << "Enter the coordinates of each point" << std::endl;
	std::cout << "First point:" << std::endl;
	getValue(point1.x);
	getValue(point1.y);
	std::cout << "Second point:" << std::endl;
	getValue(point2.x);
	getValue(point2.y);
	std::cout << "Third point:" << std::endl;
	getValue(point3.x);
	getValue(point3.y);
	std::cout << "Enter the number of points between 1 and 2, 2 and 3, 3 and 1 points" << std::endl;
	getPositive(N1);
	getPositive(N2);
	getPositive(N3);
	try {
		setTriangle(polygon, point1, N1, point2, N2, point3, N3);
		outputPoints_console(polygon);
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
	return 1;
}

int D_Show(laba3::Polygon& polygon) {
	int choice;
	std::cout << "1 - show in console    2 - output dots   other number to exit" << std::endl;
	getPositive(choice);
	if (choice == 1)
		outputPoints_console(polygon);
	if (choice == 2)
		outputPoints(polygon);
	return 1;
}

int D_Bear(laba3::Polygon& polygon) {
	//тело
	setСircle(polygon, 1, 10, 0, 4);
	setСircle(polygon, 6, 40, 0, 5);
	setСircle(polygon, 7, 40, 0, 6);
	//руки/ноги
	setСircle(polygon, 1.5, 10, 5, -1);
	setСircle(polygon, 1.5, 10, -5, -1);
	setСircle(polygon, 1.5, 10, 8, 10);
	setСircle(polygon, 1.5, 10, -8, 10);
	//глова/уши
	setСircle(polygon, 2.5, 20, 0, 16);
	setСircle(polygon, 1, 10, 3, 18);
	setСircle(polygon, 1, 10, -3, 18);
	//глаза
	setСircle(polygon, 0.5, 10, 1, 16.75);
	setСircle(polygon, 0.5, 10, -1, 16.75);
	//нос
	setСircle(polygon, 0.25, 5, 0, 15.5);
	//рот
	setСircle(polygon, 1, 10, 0, 15.25);
	outputPoints_console(polygon);
	return 1;
}

int D_Rabbit(laba3::Polygon& polygon) {
	laba3::Item point1 = { 5,2.5 }, point2 = { -5,2.5 }, point3 = { 0,8 };
	//ноги
	setSquare(polygon, 2.5, 5, -1.75, 1.25);
	setSquare(polygon, 2.5, 5, 1.75, 1.25);
	//тело
	setTriangle(polygon, point1, 8, point2, 8, point3, 8);
	//руки
	setСircle(polygon, 1, 10, 3.25, 6.25);
	setСircle(polygon, 1, 10, -3.25, 6.25);
	//голова
	setСircle(polygon, 2, 20, 0, 10);
	//уши
	point1.x = 1.15;
	point1.y = 11.65;
	point2.x = 1.15;
	point2.y = 13.65;
	point3.x = 2.15;
	point3.y = 12.65;
	setTriangle(polygon, point1, 5, point2, 5, point3, 5);
	point1.x = -1.15;
	point1.y = 11.65;
	point2.x = -1.15;
	point2.y = 13.65;
	point3.x = -2.15;
	point3.y = 12.65;
	setTriangle(polygon, point1, 5, point2, 5, point3, 5);
	//глаза
	setСircle(polygon, 0.25, 5, 1, 10.65);
	setСircle(polygon, 0.25, 5, -1, 10.65);
	//рот
	point1.x = -0.6;
	point1.y = 9;
	point2.x = 0.6;
	point2.y = 9;
	setLine(polygon, point1, point2, 5);
	point3.x = -0.9;
	point3.y = 9.3;
	setLine(polygon, point1, point3, 4);
	point3.x = 0.9;
	point3.y = 9.3;
	setLine(polygon, point2, point3, 4);
	outputPoints_console(polygon);
	return 1;
}

int D_Tic_Tac(laba3::Polygon& polygon) {
	srand(time(0));
	float size;
	int x, y, random;
	int check[9] = { 0 };//-1 - нолик  1 - крестик
	laba3::Item point1, point2;
	std::cout << "Enter the size of the field" << std::endl;
	getValue(size);
	if (size < 1)
		throw std::exception("Size is too small");
	//поле
	setSquare(polygon, size, size * 4, size / 2, size / 2);
	//разграничения
	point1.x = size / 3;
	point1.y = 0;
	point2.x = size / 3;
	point2.y = size;
	setLine(polygon, point1, point2, size * 4);
	point1.x = size / 3 * 2;
	point1.y = 0;
	point2.x = size / 3 * 2;
	point2.y = size;
	setLine(polygon, point1, point2, size * 4);
	point1.x = 0;
	point1.y = size / 3;
	point2.x = size;
	point2.y = size / 3;
	setLine(polygon, point1, point2, size * 4);
	point1.x = 0;
	point1.y = size / 3 * 2;
	point2.x = size;
	point2.y = size / 3 * 2;
	setLine(polygon, point1, point2, size * 4);
	outputPoints_console(polygon);
	for (int i = 0; i < 9; i++) {
		if (i % 2 == 0) {
			std::cout << "Enter a column and a row" << std::endl;
			do {
				getPositive(x);
				getPositive(y);
			} while (x > 3 || y > 3 || check[(y - 1) * 3 + x - 1] != 0);
			check[(y - 1) * 3 + x - 1] = 1;
			point1.x = (x - 1) * size / 3;
			point1.y = (y - 1) * size / 3;
			point2.x = (x - 1) * size / 3 + size / 3;
			point2.y = (y - 1) * size / 3 + size / 3;
			setLine(polygon, point1, point2, size * 8 / 3);
			point1.x = (x - 1) * size / 3 + size / 3;
			point1.y = (y - 1) * size / 3;
			point2.x = (x - 1) * size / 3;
			point2.y = (y - 1) * size / 3 + size / 3;
			setLine(polygon, point1, point2, size * 8 / 3);
			outputPoints_console(polygon);
			//проверка выйгрыша
			//по вертикали
			x = (y - 1) * 3 + x - 1;
			if (x < 3 && check[x + 3] == 1 && check[x + 6] == 1) {//поставили в первую строку
				std::cout << "You have won" << std::endl;
				break;
			}
			if (x >= 3 && x < 6 && check[x - 3] == 1 && check[x + 3] == 1) {//поставили во вторую строку
				std::cout << "You have won" << std::endl;
				break;
			}
			if (x >= 6 && check[x - 3] == 1 && check[x - 6] == 1) {//поставили в 3 строку
				std::cout << "You have won" << std::endl;
				break;
			}
			//по горизонтали
			if (x % 3 == 0 && check[x + 1] == 1 && check[x + 2] == 1) {//поставили в 1 столбец
				std::cout << "You have won" << std::endl;
				break;
			}
			if (x % 3 == 1 && check[x - 1] == 1 && check[x + 1] == 1) {//поставили в 2 столбец
				std::cout << "You have won" << std::endl;
				break;
			}
			if (x % 3 == 2 && check[x - 1] == 1 && check[x - 2] == 1) {//поставили в 3 столбец
				std::cout << "You have won" << std::endl;
				break;
			}
		}
		else {
			do {
				random = rand() % 9;
			} while (check[random] != 0);
			check[random] = -1;
			y = random / 3 + 1;
			x = random % 3 + 1;
			std::cout << "The opponent chose: x=" << x << " y=" << y << std::endl;
			setСircle(polygon, size / 8, size * 4, (x - 1) * size / 3 + size / 6, (y - 1) * size / 3 + size / 6);
			outputPoints_console(polygon);
			//проверка выйгрыша
			//по вертикали
			if (random < 3 && check[random + 3] == -1 && check[random + 6] == -1) {//поставили в первую строку
				std::cout << "You've lost" << std::endl;
				break;
			}
			if (random >= 3 && random < 6 && check[random - 3] == -1 && check[random + 3] == -1) {//поставили во вторую строку
				std::cout << "You've lost" << std::endl;
				break;
			}
			if (random >= 6 && check[random - 3] == -1 && check[random - 6] == -1) {//поставили в 3 строку
				std::cout << "You've lost" << std::endl;
				break;
			}
			//по горизонтали
			if (random % 3 == 0 && check[random + 1] == -1 && check[random + 2] == -1) {//поставили в 1 столбец
				std::cout << "You've lost" << std::endl;
				break;
			}
			if (random % 3 == 1 && check[random - 1] == -1 && check[random + 2] == -1) {//поставили в 2 столбец
				std::cout << "You've lost" << std::endl;
				break;
			}
			if (random % 3 == 2 && check[random - 1] == -1 && check[random - 2] == -1) {//поставили в 3 столбец
				std::cout << "You've lost" << std::endl;
				break;
			}
		}
		if (i == 8)
			std::cout << "Draw!" << std::endl;
	}
}

void setLine(laba3::Polygon& polygon, laba3::Item& point1, laba3::Item& point2, const int N) {
	float t, shift_t;
	laba3::Item point;
	//прямая между 1 и 2 точками
	if (point2.x - point1.x != 0) {
		t = (point2.x - point1.x) / (point2.x - point1.x);
		shift_t = ((point1.x - point1.x) / (point2.x - point1.x) - (point2.x - point1.x) / (point2.x - point1.x)) / N;
	}
	else {
		t = (point2.y - point1.y) / (point2.y - point1.y);
		shift_t = ((point1.y - point1.y) / (point2.y - point1.y) - (point2.y - point1.y) / (point2.y - point1.y)) / N;
	}
	for (int i = 0; i < N; i++) {
		point.x = point2.x - (point2.x - point1.x) * t;
		point.y = point2.y - (point2.y - point1.y) * t;
		polygon += point;
		t += shift_t;
	}
}

void setСircle(laba3::Polygon& circle, const float radius, const int N, const float x_centre, const float y_centre) {
	if (N < 2)
		throw std::exception("Not enough points to set circle");
	laba3::Item point;
	float current_angle = 0, angle = 2 * M_PI / N;
	for (int i = 0; i < N; i++) {
		point.x = radius * cos(current_angle) + x_centre;
		point.y = radius * sin(current_angle) + y_centre;
		circle += point;
		current_angle += angle;
	}
}

void setSquare(laba3::Polygon& square, const float side, const int N, const float x_centre, const float y_centre) {
	if (N < 4)
		throw std::exception("Not enough points to set square");
	float shift = 0, distance = side / N;
	laba3::Item point;
	for (int i = 0; i < N; i++) {//верхняя строна
		point.x = x_centre + side / 2 - shift;
		point.y = y_centre + side / 2;
		square += point;
		shift += distance;
	}
	shift = 0;
	for (int i = 0; i < N; i++) {//левая строна
		point.x = x_centre - side / 2;
		point.y = y_centre + side / 2 - shift;
		square += point;
		shift += distance;
	}
	shift = 0;
	for (int i = 0; i < N; i++) {//нижняя строна
		point.x = x_centre - side / 2 + shift;
		point.y = y_centre - side / 2;
		square += point;
		shift += distance;
	}
	shift = 0;
	for (int i = 0; i < N; i++) {//правая строна
		point.x = x_centre + side / 2;
		point.y = y_centre - side / 2 + shift;
		square += point;
		shift += distance;
	}
}

void setTriangle(laba3::Polygon& triangle, laba3::Item& point1, const int N1, laba3::Item& point2, const int N2, laba3::Item& point3, const int N3) {
	if (N1 < 1 || N2 < 1 || N3 < 1)
		throw std::exception("Not enough points to set triangle");
	float t, shift_t;
	laba3::Item point;
	//прямая между 1 и 2 точками
	setLine(triangle, point1, point2, N1);
	//прямая между 2 и 3 точками
	setLine(triangle, point2, point3, N2);
	//прямая между 3 и 1 точками
	setLine(triangle, point3, point1, N3);
}

void outputPoints(laba3::Polygon& polygon) {
	for (int i = 0; i < polygon.getSIZE(); i++) {
		std::cout << std::fixed << '(' << polygon.getNum(i).x << ',' << polygon.getNum(i).y << ")" << std::endl;
	}
}

void outputPoints_console(laba3::Polygon& polygon) {//првоерить вывод экспоненциального вида
	POINT op;
	HWND hWnd = GetConsoleWindow(); //Получаем дескриптор окна консоли
	HDC hDC = GetDC(hWnd); //Получаем контекст устройства по полученному дескриптору
	SelectObject(hDC, GetStockObject(DC_BRUSH));
	SetDCBrushColor(hDC, RGB(255, 255, 255));
	Rectangle(hDC, 400, 400, 800, 800);

	SelectObject(hDC, GetStockObject(DC_BRUSH));
	for (int i = 0; i < polygon.getSIZE(); ++i)
	{
		SetDCBrushColor(hDC, RGB(255, 0, 0));
		Ellipse(hDC, 600 + polygon.getNum(i).x * 8 - 3, 600 - polygon.getNum(i).y * 8 - 3, 600 + polygon.getNum(i).x * 8 + 3, 600 - polygon.getNum(i).y * 8 + 3);
	}
	ReleaseDC(hWnd, hDC); //"Освобождаем" контекст
}