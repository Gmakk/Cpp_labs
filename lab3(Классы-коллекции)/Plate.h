#pragma once
#include <iostream>
#include <cmath>

typedef struct Contact {
	bool type;//1-entrance / 0-output
	int x, y, number;//number-number of the associated contact / ==INT_MAX - no connection
}Contact;

Contact* new_size(int size_old, int size_new, Contact* arr);//изменяет количесво выделенной под массив памяти

class Plate
{
private:
	int size;//текущее количество элементов
	Contact* arr;//элементы добавляются в конец
public:
	Plate();
	Plate(const Plate& origin);//создает дубликат переданного элемента
	Plate(Plate&& origin);//перемещающий конструктор
	Plate(int x, int y, int type);//конструктор, создающий только 1 контакт на плате
	Plate(int size, Contact* arr);//переденный массив помещается в поле класса
	~Plate();
	//методы
	inline Contact* getArr() { return arr; };//возвращает массив
	inline int getSize() const { return size; };//возвращает текущий размер
	inline void setSize(int new_s) { size = new_s; };//задает новый размер
	int addContact(int x, int y, int type);//добавление контакта
	int deleteContact();//удаляет последний контакт, если такой есть
	void showInfo(std::ostream& out) const;//вывод всех элементов
	int correctness(int number) const;//проверка корректности связи
	int addLink(int number1, int number2);//добавление связи с проверкой корректности
	void showGroup(bool type, std::ostream& out) const;//вывод определенного типа контактов
	double pathLength(int number1, int number2) const;//нахождение длины пути с проверкой корректности

	//унарные
	friend Plate& operator++(Plate& plate);//префиксный инкремент возвращает объект с добавленным контакатом(0,0,0)
	friend Plate operator++(Plate& plate, int i);//постфиксный инкремент аналогичен префиксному, но вовращает старую версию
	friend Plate& operator--(Plate& plate);//префиксный декремент удаляет элемент
	friend Plate operator--(Plate& plate, int i);//постфиксный декремент аналогичен префиксному, но вовращает старую версию
	//бинарные
	Plate& operator+=(const int right);//добавляет N контактов (0,0,0)
	Plate& operator-=(const int right);//удаляет N  последних контактов, если такие есть
	Plate* operator+(const Plate& right);//создает новый элемент с контактами слагаемых
	//ввод вывод
	friend std::ostream& operator<<(std::ostream& out, const Plate& plate);//вывод всех контактов класса
	friend std::istream& operator>>(std::istream& in, Plate& plate);//происходит ввод и добавление нового контакта
	//сравнения
	bool operator!=(const Plate& right);//
	bool operator==(const Plate& right);//
	bool operator<(const Plate& right);//
	bool operator<=(const Plate& right);//	сравнивают количество контактов на платах
	bool operator>(const Plate& right);//
	bool operator>=(const Plate& right);//

	Plate& operator=(const Plate& right);//левой плате присваивается размер и массив контактов правой
	Plate& operator=(Plate&& right);//левой плате присваивается размер и массив контактов правой
	Contact& operator[] (int index);//возвращает элемент массива
	const Contact& operator[] (int index) const;
};

bool operator==(const Contact& left, const Contact& right);//проверяет корректность связи между контактами