#pragma once
#include <iostream>
#include <time.h>
	// строка матрицы
	struct matrix {
		double* values;//значения
		int numb_cals;//количество столбцов
		int* cals;//столбцы
		int numb_rows;//количество строк
		int* rows;//строки
		int total;//всего элементов
	};


	// щаблон для ввода одного значения
	template <class T>
	int getNum(T& a){
		std::cin >> a;
		if (!std::cin.good())
			return -1;
		return 1;
	}


	template <class T>
	int getPositiveNum(T& a) {
		do {
			std::cin >> a;
			if (!std::cin.good())
				return -1;
			if (a > 0)
				break;
			else
				std::cout << "Enter a positive number" << std::endl;
		} while (a <= 0);
		return 1;
	}


	template <class T>
	T* new_size(T* mass, int old_s, int new_s) {
		T* buf = new T[new_s];
		for (int i = 0; i < old_s; i++)
			buf[i] = mass[i];
		delete[] mass;
		return buf;
	}


	matrix* input(); // ввод матрицы
	matrix* rand_input(int n,int m); // рандомное заполнение матрицы
	void output(matrix* matr); // вывод матрицы
	void clean(matrix* matr); // очистка памяти
	int modification(matrix* matr); //изменение строк
	int findRow(matrix* matr);