#include "Header.h"

int findRow(matrix* matr, int i) {// i-индекс искомого элемента
	int min_row = 1;
	while (1) {
		if (matr->rows[min_row] >= i + 1)
			break;
		min_row++;
	}
	return min_row - 1;
}

matrix* input() {
	matrix* matr = new matrix; //память под матрицу
	const char* error = "";
	int count = 0, m, n;// кол-во строк,столбцов
	double buf;
	do {
		std::cout << error << std::endl;
		std::cout << "Enter number of lines: ";
		error = "You are wrong; repeat please!";
		if (getNum(m) < 0) // ошибка ввода
			return nullptr;
	} while (m < 1);
	matr->rows = new int[m + 1];
	matr->rows[0] = 0;
	error = "";
	do {
		std::cout << error << std::endl;
		std::cout << "Enter number of items in line: ";
		error = "You are wrong; repeat please!";
		if (getNum(n) < 0) { // ошибка ввода
			return nullptr;
		}
	} while (n < 1);
	for (int i = 0; i < m; i++) {
		//ввод количества столбцов
		try {
			if (count == 0) {
				matr->values = new double[n];
				matr->cals = new int[n];
			}
			else {
				matr->values = new_size(matr->values, count, n + count);
				matr->cals = new_size(matr->cals, count, n + count);
			}
		}
		catch (std::bad_alloc& ba) {
			std::cout << "Error when allocating memory for matrix elements:" << ba.what() << std::endl;
			return nullptr;
		}
		// ввод элементов строки
		std::cout << "Enter items for matrix line #" << (i + 1) << ":" << std::endl;
		for (int j = 0; j < n; j++) {
			getNum(buf);
			if (buf < 0) { // ошибка ввода
				return nullptr;
			}
			if (buf > 0) {
				matr->values[count] = buf;
				matr->cals[count] = j;
				count++;//всего элементов
			}
		}
		matr->rows[i + 1] = count;//элементов в предыдущих строках
	}
	// формируем результат
	matr->values = new_size(matr->values, count, count);
	matr->cals = new_size(matr->cals, count, count);
	matr->numb_cals = n;
	matr->numb_rows = m;
	matr->total = count;
	return matr;
}

matrix* rand_input(int n, int m) {			//n-столбцы m-строки
	srand(time(0));
	matrix* matr = new matrix; //память под матрицу
	int count = 0;
	double buf;

	matr->rows = new int[m + 1];
	matr->rows[0] = 0;
	for (int i = 0; i < m; i++) {
		try {
			if (count == 0) {
				matr->values = new double[n];
				matr->cals = new int[n];
			}
			else {
				matr->values = new_size(matr->values, count, n + count);
				matr->cals = new_size(matr->cals, count, n + count);
			}
		}
		catch (std::bad_alloc& ba) {
			std::cout << "Error when allocating memory for matrix elements:" << ba.what() << std::endl;
			return nullptr;
		}
		// заполнение рандомными числами
		for (int j = 0; j < n; j++) {
			switch (rand() % 2)
			{
			case 0:
				buf = 0;
				break;
			case 1:
				buf = rand() % 9;
				buf++;
				break;
			default:
				break;
			}
			if (buf > 0) {
				matr->values[count] = buf;
				matr->cals[count] = j;
				count++;//всего элементов
			}
		}
		matr->rows[i + 1] = count;//элементов в предыдущих строках
	}
	// формируем результат
	matr->values = new_size(matr->values, count, count);
	matr->cals = new_size(matr->cals, count, count);
	matr->numb_cals = n;
	matr->numb_rows = m;
	matr->total = count;
	return matr;
}

void output(matrix* matr) {
	int current, size, count;
	for (int i = 1; i < matr->numb_rows + 1; i++) {
		size = matr->rows[i] - matr->rows[i - 1];
		if (size > 0) {
			current = 0;
			count = 0;
			std::cout << "| ";
			do {
				while (current < matr->cals[matr->rows[i-1] + count]) {
					std::cout << 0 << ' ';
					current++;
				}
				std::cout << matr->values[matr->rows[i - 1] + count] << ' ';
				count++;
				current++;
				//берем следующее число
			} while (count < size);
			while (current < matr->numb_cals) {
				std::cout << 0 << ' ';
				current++;
			}
			std::cout << "| ";
		}
		else {
			std::cout << "| ";
			for(int j=0;j<matr->numb_cals;j++)
				std::cout << 0 << ' ';
			std::cout << "| ";
		}
		std::cout << std::endl;
	}









	/*int min_row;
	//заполнение 0
	regular_matrix buf_matr;
	buf_matr.numbers = new double* [matr->numb_rows];
	for (int i = 0; i < matr->numb_rows; i++)
		buf_matr.numbers[i] = new double[matr->numb_cals];
	for (int i = 0; i < matr->numb_rows; i++)
		for (int j = 0; j < matr->numb_cals; j++) {
			buf_matr.numbers[i][j] = 0;
		}

	//подстановка ненулевых значений
	for (int i = 0; i < matr->total; i++) {
		min_row = 1;
		while (1) {
			if (matr->rows[min_row] >= i + 1)
				break;
			min_row++;
		}
		buf_matr.numbers[min_row - 1][matr->cals[i]] = matr->values[i];
	}

	//вывод матрицы
	for (int i = 0; i < matr->numb_rows; i++) {
		std::cout << "| ";
		for (int j = 0; j < matr->numb_cals; j++) {
			std::cout << buf_matr.numbers[i][j] << ' ';
		}
		std::cout << " |";
		std::cout << std::endl;
	}
	*/
}

void clean(matrix* matr) {
	delete[] matr->cals;
	delete[] matr->rows;
	delete[] matr->values;
	delete matr;
}

int modification(matrix* matr) {
	int current, length, count, i, j, i_check, j_check;
	int cal_i, check0_i, cal_j, check0_j;
	double buf;
	for (int g = 1; g < matr->numb_rows + 1; g++) {
		if (matr->rows[g] > matr->rows[g - 1]) {
			//считаем количесво ненулевых элементов в строке
			length = matr->rows[g] - matr->rows[g - 1];
			if (length > 1) {//если есть что менять местами
				i = matr->rows[g - 1];
				j = matr->rows[g - 1] + length - 1;
				i_check = 0;
				j_check = 0;
				check0_i = 0;
				check0_j = 0;
				for (int k = 0; k < length; k++) {
					//сравнение с 0
					//если число отрицательное и сосед справа - 0 или это последнее число в строке
					if ((i + k + 1 < matr->total && matr->values[i + k] < 0 && //	<=	????????????
						((matr->cals[i + k + 1] - matr->cals[i + k] > 1 && findRow(matr, i + k) == findRow(matr, i + k + 1)) || findRow(matr, i + k) != findRow(matr, i + k + 1))
						&& matr->cals[i + k] < matr->numb_cals - 1) || (k == length - 1 && matr->cals[i + k] < matr->numb_cals - 1 && matr->values[i + k] < 0)) {
						//запомнить последующий после i+k элемента ноль
						i_check = 1;
						check0_i = 1;
						cal_i = matr->cals[i + k] + 1;
						break;
					}
					//если число положительное и сосед слева - 0 и это не первое число в строке
					if ((i + k - 1 >= 0 && matr->values[i + k] > 0 &&
						((matr->cals[i + k] - matr->cals[i + k - 1] > 1 && findRow(matr, i + k) == findRow(matr, i + k - 1)) || findRow(matr, i + k) != findRow(matr, i + k - 1))
						&& matr->cals[i + k] > 0) || (k == 0 && matr->values[i + k] > 0 && matr->cals[i+k] > 0)) {
						//запомнить i+k элемент
						i += k;
						i_check = 1;
						break;
					}
					//если сосед слева ненулевой элемент
					if (i + k - 1 >= 0 && matr->cals[i + k] > 0 && matr->values[i + k] > matr->values[i + k - 1]
						&& matr->cals[i + k] - matr->cals[i + k - 1] == 1 && findRow(matr, i + k) == findRow(matr, i + k - 1)) {
						//запомнить i+k элемент
						i += k;
						i_check = 1;
						break;
					}
				}
				for (int k = 0; k < length; k++) {
					//если число положительное и сосед справа - 0 или это последнее число в строке
					if ((j - k + 1 < matr->total && matr->values[j - k] > 0 &&
						((matr->cals[j - k + 1] - matr->cals[j - k] > 1 && findRow(matr, j - k) == findRow(matr, j - k + 1)) || findRow(matr, j - k) != findRow(matr, j - k + 1))
						&& matr->cals[j - k] < matr->numb_cals - 1) || (k == 0 && matr->cals[j - k] < matr->numb_cals - 1 && matr->values[j - k] > 0)) {
						//запомнить последующий после j - k элемента ноль
						j_check = 1;
						check0_j = 1;
						cal_j = matr->cals[j - k] + 1;
						break;
					}
					//если число отрицательное и сосед слева - 0 и это не первый элемент в строке
					if ((j - k - 1 >= 0 && matr->values[j - k] < 0 &&
						((matr->cals[j - k] - matr->cals[j - k - 1] > 1 && findRow(matr, j - k) == findRow(matr, j - k - 1)) || findRow(matr, j - k) != findRow(matr, j - k - 1))
						&& matr->cals[j - k] > 0) || (j-k == 0 && matr->values[j - k] < 0 && matr->cals[j-k] > 0)) {
						//запомнить j - k элемент
						j_check = 1;
						j -= k;
						break;
					}
					//если сосед слева ненулевой элемент
					if (j - k - 1 >= 0 && matr->cals[j - k] > 0 && matr->values[j - k] < matr->values[j - k - 1]
						&& matr->cals[j - k] - matr->cals[j - k - 1] == 1 && findRow(matr, j - k) == findRow(matr, j - k - 1)) {
						//запомнить j - k элемент
						j_check = 1;
						j -= k;
						break;
					}
				}
				if (i_check == 1 && j_check == 1) {
					if (check0_i == 0 && check0_j == 0) {
						//меняем местами два ненулевых элемента
						buf = matr->values[i];
						matr->values[i] = matr->values[j];
						matr->values[j] = buf;
					}
					if (check0_i == 1 && check0_j == 0) {
						//переставить j элемент на место 0
						if (cal_i < matr->cals[j]) {
							count = matr->rows[g - 1];
							while (matr->cals[count] < cal_i && count < matr->rows[g - 1] + length - 1) {
								count++;
							}
							buf = matr->values[j];
							for (int g = j; g > count; g--){
								matr->cals[g] = matr->cals[g - 1];
								matr->values[g] = matr->values[g - 1];
							}
							matr->values[count] = buf;
							matr->cals[count] = cal_i;
						}
						else {
							count = matr->rows[g - 1] + length - 1;
							while (matr->cals[count] > cal_i && count > matr->rows[g - 1])
								count--;
							buf = matr->values[j];
							for (int g = j; g < count; g++) {
								matr->cals[g] = matr->cals[g + 1];
								matr->values[g] = matr->values[g + 1];
							}
							matr->values[count] = buf;
							matr->cals[count] = cal_i;
						}
					}
					if (check0_i == 0 && check0_j == 1) {
						//переставить i элемент на место 0
						if (matr->cals[i] > cal_j) {
							count = matr->rows[g - 1];
							while (matr->cals[count ] < cal_j && count < matr->rows[g - 1] + length - 1)
								count++;
							buf = matr->values[i];
							for (int g = i; g > count; g--) {
								matr->cals[g] = matr->cals[g - 1];
								matr->values[g] = matr->values[g - 1];
							}
							matr->values[count] = buf;
							matr->cals[count] = cal_j;
						}
						else {
							count = matr->rows[g - 1] + length - 1;
							while (matr->cals[count] > cal_j)
								count--;
							buf = matr->values[i];
							for (int g = i; g < count; g++) {
								matr->cals[g] = matr->cals[g + 1];
								matr->values[g] = matr->values[g + 1];
							}
							matr->values[count] = buf;
							matr->cals[count] = cal_j;
						}
					}
				}
			}
		}
	}
	return 1;
}