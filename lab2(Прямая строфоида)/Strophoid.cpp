#include "Strophoid.h"

strophoid::strophoid(double offset) {
	if (offset >= 0)
		A_coordinate = offset;
	else
		A_coordinate = -offset;
}

strophoid::strophoid() {
	A_coordinate = 0;
}

void strophoid::set_A(double value) {
	if (value < 0)
		//A_coordinate = -value;
		std::cout << "Incorrect input" << std::endl;
	else
		A_coordinate = value;
}

double strophoid::find_y(double x_value) const {
	return x_value * sqrt((A_coordinate + x_value) / (A_coordinate - x_value));
}

double strophoid::find_distance(double angle) const {
	return fabs((A_coordinate * cos(2 * angle)) / (cos(angle)));
}

double strophoid::find_curve_rad() const {
	return sqrt(2.0) * A_coordinate;
}

double strophoid::find_loop_square() const {
	return pow(A_coordinate, 2) * (2 - M_PI / 2);
}

double strophoid::find_volume() const {
	return pow(A_coordinate, 3) * M_PI * 2 / 3 + 2 * pow(A_coordinate, 3) * M_PI * (log(2) - 1);
}

double strophoid::find_square_asymptote() const {
	return pow(A_coordinate, 2) * (2 + M_PI / 2);
}