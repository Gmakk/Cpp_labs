#pragma once
#include <cmath>
#include <iostream>

#define M_PI 3.14159265358979323846

class strophoid {
	double A_coordinate;
public:
	strophoid(double offset);
	strophoid();
	~strophoid() = default;
	inline double show_A() const {
		return A_coordinate;
	}

	void set_A(double value);
	double find_y(double x_value) const;
	double find_distance(double angle) const;//угол в радианах
	double find_curve_rad() const;
	double find_loop_square() const;
	double find_volume() const;
	double find_square_asymptote() const;
};