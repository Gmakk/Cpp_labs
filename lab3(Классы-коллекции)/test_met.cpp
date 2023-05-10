#include "pch.h"
#include "Plate.h"
TEST(Constructor, Copy) {
	Contact array[3] = {
		{0,5,6,INT_MAX},
		{0,-5,-5,2},
		{1,50,50,1}
	};
	Plate plate_origin(3, array);
	Plate plate(plate_origin);
	EXPECT_EQ(plate.getArr()[0].x, 5);
	EXPECT_EQ(plate.getArr()[0].y, 6);
	EXPECT_EQ(plate.getArr()[0].type, 0);
	EXPECT_EQ(plate.getArr()[0].number, INT_MAX);
}
TEST(Constructor, Move) {
	Contact array[3] = {
		{0,5,6,INT_MAX},
		{0,-5,-5,2},
		{1,50,50,1}
	};
	Plate plate_origin(3, array);
	Plate plate = std::move(plate_origin);
	EXPECT_EQ(plate.getArr()[0].x, 5);
	EXPECT_EQ(plate.getArr()[0].y, 6);
	EXPECT_EQ(plate.getArr()[0].type, 0);
	EXPECT_EQ(plate.getArr()[0].number, INT_MAX);
}
TEST(Constructor, OneElement) {
	Plate plate(5, 10, 0);
	EXPECT_EQ(plate.getArr()[0].x, 5);
	EXPECT_EQ(plate.getArr()[0].y, 10);
	EXPECT_EQ(plate.getArr()[0].type, 0);
	EXPECT_EQ(plate.getArr()[0].number, INT_MAX);
}
TEST(Constructor, Array) {
	Contact array[3] = {
		{0,5,6,INT_MAX},
		{0,-5,-5,2},
		{1,50,50,1}
	};
	Plate plate(3, array);
	EXPECT_EQ(plate.correctness(0), 2);
	EXPECT_EQ(plate.correctness(1), 1);
	EXPECT_DOUBLE_EQ(plate.pathLength(1, 2), 77.781745930520231);
	EXPECT_EQ(plate.getArr()[0].type, 0);
	EXPECT_EQ(plate.getArr()[0].x, 5);
	EXPECT_EQ(plate.getArr()[0].y, 6);
	EXPECT_EQ(plate.getArr()[0].number, INT_MAX);
}
TEST(AddConact, CorrectValues) {
	Plate plate;
	plate.addContact(6, -10, 0);
	plate.addContact(-100, 56, 1);
	EXPECT_EQ(plate.getArr()[0].type, 0);
	EXPECT_EQ(plate.getArr()[0].x, 6);
	EXPECT_EQ(plate.getArr()[0].y, -10);
	EXPECT_EQ(plate.getArr()[0].number, INT_MAX);
	EXPECT_EQ(plate.getArr()[1].type, 1);
	EXPECT_EQ(plate.getArr()[1].x, -100);
	EXPECT_EQ(plate.getArr()[1].y, 56);
	EXPECT_EQ(plate.getArr()[1].number, INT_MAX);
}

TEST(AddConact, IncorrectValues) {
	Plate plate;
	EXPECT_EQ(plate.addContact(6, -10, 6), -1);
}

TEST(Correctness, BothValues) {
	Plate plate;
	plate.addContact(1, 1, 0);
	plate.addContact(2, 2, 1);
	plate.addLink(0, 1);
	EXPECT_EQ(plate.correctness(0), 1);
	EXPECT_EQ(plate.correctness(1), 1);
}

TEST(Correctness, WithoutConnection) {
	Plate plate;
	plate.addContact(1, 1, 0);
	plate.addContact(2, 2, 1);
	EXPECT_EQ(plate.correctness(0), 2);
	EXPECT_EQ(plate.correctness(1), 2);
}

TEST(AddLink, IncorrectTypes1) {
	Plate plate;
	plate.addContact(1, 1, 1);
	plate.addContact(2, 2, 1);
	plate.addLink(1, 0);
	EXPECT_EQ(plate.correctness(0), 2);
	EXPECT_EQ(plate.correctness(1), 2);
}

TEST(AddLink, IncorrectTypes2) {
	Plate plate;
	plate.addContact(1, 1, 0);
	plate.addContact(2, 2, 1);
	plate.addLink(1, 0);
	EXPECT_EQ(plate.correctness(0), 2);
	EXPECT_EQ(plate.correctness(1), 2);
}

TEST(FindLength, PositiveValues) {
	Plate plate;
	plate.addContact(1, 1, 0);
	plate.addContact(2, 2, 1);
	plate.addLink(0, 1);
	EXPECT_DOUBLE_EQ(plate.pathLength(0, 1), 1.4142135623730951);
}

TEST(FindLength, NegativeValues) {
	Plate plate;
	plate.addContact(-1, -1, 0);
	plate.addContact(2, 2, 1);
	plate.addLink(0, 1);
	EXPECT_DOUBLE_EQ(plate.pathLength(0, 1), 4.2426406871192848);
}