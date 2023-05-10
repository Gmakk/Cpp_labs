#include "Header.h"

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

int D_Show(strophoid* object) {
	std::cout << "Current value of A is: " << object->show_A() << std::endl;
	return 1;
}

int D_Change(strophoid* object) {
	double new_val;
	std::cout << "Enter new value of A: ";
	getValue(new_val);
	object->set_A(new_val);
	return 1;
}

int D_Coord(strophoid* object) {
	double x;
	std::cout << "Enter X coordinate: ";
	getValue(x);
	if (object->show_A() < fabs(x)) {
		std::cout << "The value is not included in the scope of the definition" << std::endl;
		return -1;
	}
	if(object->show_A()!=0)
		std::cout << "The Y coordinate of the Cartesian coordinate system: +-" << fabs(object->find_y(x)) << std::endl;
	else
		std::cout << "The Y coordinate of the Cartesian coordinate system: " << 0 << std::endl;
	return 1;
}

int D_Dist(strophoid* object) {
	double angle;
	std::cout << "Enter angle: ";
	getValue(angle);
	if(cos(angle)!=0)
	std::cout << "Distance to the center in the polar coordinate system: " << object->find_distance(angle) << std::endl;
	else {
		std::cout << "Division by 0 occurs!"<<std::endl;
		return -1;
	}
	return 1;
}

int D_Rad(strophoid* object) {
	std::cout << "Radius of curvature at the nodal point: " << object->find_curve_rad() << std::endl;
	return 1;
}

int D_Square(strophoid* object) {
	std::cout << "Loop area: " << object->find_loop_square() << std::endl;
	return 1;
}

int D_Volume(strophoid* object) {
	std::cout << "Volume of body of revolution: " << object->find_volume() << std::endl;
	return 1;
}

int D_Asympt(strophoid* object) {
	std::cout << "Area between the branches and the asymptote: " << object->find_square_asymptote() << std::endl;
	return 1;
}