#include "pch.h"
#include "Strophoid.h"
TEST(Constr, positive) {
	strophoid str(5.5);
	ASSERT_DOUBLE_EQ(str.show_A(), 5.5);
}

TEST(Constr, zero) {
	strophoid str;
	ASSERT_DOUBLE_EQ(str.show_A(), 0);
}

TEST(Constr, negative) {
	strophoid str(-5.5);
	ASSERT_DOUBLE_EQ(str.show_A(), 5.5);
}

TEST(Set, positive) {
	strophoid str(5.5);
	str.set_A(6.6);
	ASSERT_DOUBLE_EQ(str.show_A(), 6.6);
}

TEST(Set, negative) {
	strophoid str(5.5);
	str.set_A(-6.6);
	ASSERT_DOUBLE_EQ(str.show_A(), 5.5);
}

TEST(Find_Y, positive_x) {
	strophoid str(5.5);
	ASSERT_DOUBLE_EQ(str.find_y(2), 2.9277002188455996);
}

TEST(Find_Y, negative_X) {
	strophoid str(5.5);
	ASSERT_DOUBLE_EQ(str.find_y(-2), -1.3662601021279464);
}

TEST(Distance, positive) {
	strophoid str(5);
	ASSERT_DOUBLE_EQ(str.find_distance(1), 3.8510555297232307);
}

TEST(Radius, positive) {
	strophoid str(sqrt(2));
	ASSERT_DOUBLE_EQ(str.find_curve_rad(), 2);
}

TEST(Radius, negative) {
	strophoid str(-sqrt(2));
	ASSERT_DOUBLE_EQ(str.find_curve_rad(), 2);
}

TEST(Square_1, positive) {
	strophoid str(2);
	ASSERT_DOUBLE_EQ(str.find_loop_square(), 8-2*M_PI);
}

TEST(Square_1, negative) {
	strophoid str(-2);
	ASSERT_DOUBLE_EQ(str.find_loop_square(), 8 - 2 * M_PI);
}

TEST(Volume, positive) {
	strophoid str(5.5);
	ASSERT_DOUBLE_EQ(str.find_volume(), 27.681801227187748);
}

TEST(Volume, negative) {
	strophoid str(-5.5);
	ASSERT_DOUBLE_EQ(str.find_volume(), 27.681801227187748);
}

TEST(Square_2, positive) {
	strophoid str(5.5);
	ASSERT_DOUBLE_EQ(str.find_square_asymptote(), 108.01658888554562);
}

TEST(Square_2, negative) {
	strophoid str(-5.5);
	ASSERT_DOUBLE_EQ(str.find_square_asymptote(), 108.01658888554562);
}