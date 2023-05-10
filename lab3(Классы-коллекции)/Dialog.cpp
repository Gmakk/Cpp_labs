#include "Dialog.h"

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

int D_AddContact(Plate& plate) {
	std::cout << "Enter x,y and type(0/1)" << std::endl;
	try {
		std::cin >> plate;
	}
	catch (std::exception ex) {
		std::cout << ex.what() << std::endl;
	}
	return 1;
}
int D_Info(Plate& plate) {
	plate.showInfo(std::cout);
	/*try {//вывод без пояcнения
		std::cout << plate;
	}
	catch (std::exception ex) {
		std::cout << ex.what() << std::endl;
	}*/
	return 1;
}
int D_Correct(Plate& plate) {
	int number;
	std::cout << "Enter number of the contact: " << std::endl;
	getPositive(number);
	switch (plate.correctness(number))
	{
	case -1:
		std::cout << "The connection between the contacts is incorrect " << std::endl;
		break;
	case 1:
		std::cout << "The connection between the contacts is correct " << std::endl;
		break;
	case 2:
		std::cout << "The contact is not connected " << std::endl;
		break;
	case 3:
		std::cout << "The is no such contact " << std::endl;
		break;
	}
	return 1;
}
int D_AddLink(Plate& plate) {
	int number1, number2;
	std::cout << "Enter number of the first contact: " << std::endl;
	getPositive(number1);
	std::cout << "Enter number of the second contact: " << std::endl;
	getPositive(number2);
	return plate.addLink(number1, number2);
}
int D_Group(Plate& plate) {
	short number;
	std::cout << "Enter 0 for output, 1 for entrance, another number to exit: " << std::endl;
	getValue(number);
	if (number == 1 || number == 0)
		plate.showGroup(number, std::cout);
	return 1;
}
int D_Length(Plate& plate) {
	int number1, number2;
	double result;
	std::cout << "Enter number of the first contact: " << std::endl;
	getPositive(number1);
	std::cout << "Enter number of the second contact: " << std::endl;
	getPositive(number2);
	result = plate.pathLength(number1, number2);
	if (result != -1)
		std::cout << "Distance between contacts is: " << result << std::endl;
	return 1;
}