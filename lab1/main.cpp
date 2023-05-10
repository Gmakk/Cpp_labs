#include "Header.h"

int main()
{
	int choice, n, m;
	std::cout << "Enter matrix(1) or random(2)" << std::endl;
	getNum(choice);
	matrix* matr;
	switch (choice){
	case 1:
		matr = input();
		std::cout << "Matrix:" << std::endl;
		output(matr);
		modification(matr);
		std::cout << "Result:" << std::endl;
		output(matr);
		clean(matr);
		break;
	case 2:
		std::cout << "Enter number of lines:";
		getPositiveNum(m);
		std::cout << "Enter number of columns:";
		getPositiveNum(n);
		matr = rand_input(n,m);
		std::cout << "Matrix:" << std::endl;
		output(matr);
		modification(matr);
		std::cout << "Result:" << std::endl;
		output(matr);
		clean(matr);
		break;
	default:
		std::cout << "There is no such option" << std::endl;
		break;
	}
	return 0;
}