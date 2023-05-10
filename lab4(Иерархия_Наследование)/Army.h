#pragma once
#include <iostream>
#include <string>
#include <deque>
#include <list>
#include <map>
#include <vector>

std::string findCondition(int number);

std::string findSpecialization(int number);

/**
* \brief Инструкция
*
* Содержит инструкцию, с соответствующим ей номером
*/
typedef struct Instructions {
	std::string instruction;
	int number;
}Instructions;

/**
* \brief Место дислокации
*
* Определяет координаты дивизии или штаба на плоскости
*/
typedef struct Location {
	int x;
	int y;
}location;

/**
* \brief Абстрактный солдат
*
* Клас, содержащий общие для всех слодат поля и методы и от которого наследуются все остальные солдаты.
* Методы: возвращение типа солдата и вывод информации о нем в поток
*/
class Abstract {
protected:
	std::string FIO;//ФИО
	std::string rank;//звание
	int shape_size;
public:
	std::string get_FIO() const { return FIO; };
	void setFIO(std::string fio) { FIO = fio; };

	std::string get_Rank() const { return rank; };
	void setRank(std::string rank1) { rank = rank1; };

	int get_Size() const { return shape_size; };
	void setSize(int size) { shape_size = size; };

	virtual int getType() const { return -1; };

	virtual void showInfo(std::ostream& out) const {};
};

/**
* \brief Информация о солдате
*
* Содержит состояние солдата, его номер и описатель
*/
typedef struct Info {
	int condition;//состояние
	int number;
	Abstract* soldier;
}Info;

/**
* \brief Солдат
*
* Солдат, наследуемый от абстрактного класса, у которого есть специализация и который может хранить и выполнять приказы
*/
class Soldier : public Abstract {
protected:
	int spec;//специализация
	std::deque<std::string> orders;//приказы
public:
	Soldier() = default;
	Soldier(std::string fio, std::string rank1, int size, int specialization);
	Soldier(Soldier& original);

	std::string executeOrder();
	void addOrder(std::string order) { orders.push_back(order); };

	int get_Spec_int() const { return spec; };
	void setSpec_int(int sp) { spec = sp; };
	std::string get_Spec_str() const;
	void set_Spec_str(std::string str);

	virtual void showInfo(std::ostream& out) const;

	virtual int getType() const { return 0; };
};

/**
* \brief Штабист
*
* Класс, наследуемый от абстрактного солдата и содержащий список инструкций с возможностью их выполнения и свою должность при штабе
*/
class Staff : public Abstract {
protected:
	std::string post;//должность при штабе
	std::list<Instructions> instructions;
public:
	Staff() = default;
	Staff(std::string fio, std::string rank1, int size, std::string post1);
	Staff(Staff& original);

	std::string get_Post() const { return post; };
	void setPost(std::string post1) { post = post1; };

	Instructions executeInstruction();
	void addInstruction(Instructions instruction) { instructions.push_back(instruction); };
	void addInstruction(std::string instruction, int number);
	int getInstructionNumber() { return instructions.size(); };

	virtual void showInfo(std::ostream& out);

	virtual int getType() const { return 1; };
};

template <class M>
class Iterator {
private:
	M* info;
public:
	Iterator() = default;
	Iterator(Info* info1) :info(info1) {};
	Iterator(const Iterator<M>& original) :info(original.info) {};

	bool operator!=(Iterator const& other) const {
		return info != other.info;
	};
	bool operator==(Iterator const& other) const {
		return info == other.info;
	};
	Info* operator*() const{
		return info;
	}
	Iterator<M>& operator++() {//префиксный
		++info;
		return *this;
	};
	Iterator<M>& operator++(int i) {//постфиксный
		Iterator<M> current(info);
		++info;
		return current;
	};
	Iterator<M>& operator--() {//префиксный
		--info;
		return *this;
	};
	Iterator<M>& operator--(int i) {//постфиксный
		Iterator<M> current(info);
		--info;
		return current;
	};
	Iterator& operator=(const Iterator& right) {
		if (this == &right) {//проверка на самоприсваивание
			return *this;
		}
		this->info = right.info;
	}
};

/**
* \brief Таблица
*
* Таблица хранит онформацию о бойцах в формате Info и позволяет изменять, просматривать и дополнять эту информацию
*/
template <class T>
class Table {
private:
	T* information;
	int size, allocated;
public:
	Table() :size(0), allocated(0) {};
	Table(int size, int allocated, Info* info);
	Table(Table<T>& origin);
	Table(Table<T>&& origin);
	~Table() { delete[] information; }

	void addInfo(const Info inf);
	void addInfo(const int condition,const int number, Abstract* soldier);

	void deleteInfo(const int number);

	Info* getInformation() const { return information; };
	void setInformation(Info* inf) { information = inf; };

	int getAllocated() const { return allocated; };
	void setAllocated(const int allo) { allocated = allo; };

	int getSize() const { return size; }
	void setSize(const int size1) { size = size1; };

	Info* getInfo (const int number) const;

	Abstract* getDescriptor (const int number) const;

	void showInfo(std::ostream& out) const;

	std::string getCondition_str(const int number) const;
	void setCondition(const int number, const std::string condition);
	int getCondition_int(const int number) const;
	void setCondition(const int number, const int cond);

	int getSpecialSize(const int condition) const;//количество бойцов с определенным состоянием
	int getSpecialSize(const std::string condition) const;

	Iterator<T> begin() const { return Iterator<T>(information); };
	Iterator<T> end() const { return Iterator<T>(information + size - 1); };

	void new_size(const int new_size);

	Table<T>& operator=(Table<T>& right);
	Table<T>& operator=(Table<T>&& right);
};

/**
* \brief Штаб
*
* \warning отстутствует возможность изменять расположение
* Содержит таблицу солдат и свое расположение. Определены операции взаимодействия с таблицей и просмотра расположения штаба
*/
class Headquarters {
protected:
	Table<Info>* table;
	Location* location;
public:
	Headquarters();
	Headquarters(int x, int  y, Table<Info>& table1);
	Headquarters(Location loc, Table<Info>& table1);
	Headquarters(Headquarters& original);
	~Headquarters();

	Location* getLocation() { return location; };

	Table<Info>* getTable() { return table; };

	void setCondition(int number, int condition);

	std::vector<Headquarters*> devide(std::string maxRank, std::string newPost);
};

/**
* \brief Дивизия
*
* Класс, наследуемый от штаба. Отличается наличием возможности изменить свое расположение
*/
class Division : public Headquarters {
public:
	Division();
	Division(int x, int  y, Table<Info>& table1);
	Division(Location loc, Table<Info>& table1);
	Division(Division& original);

	void setLocation(int x, int y);
	void setLocation(Location loc);
};

/**
* \brief Полевой командир
*
* Класс, наследуемый от солдата и содержащий должность при штабе, список инструкций и указатель на дивизию. Определены операции изменения/просмотра должности,
* исполнения/добавления инструкций и изменения/просмотра дивизии
*/
class FieldCommander : public Soldier {
protected:
	Division* division;
	std::string post;//должность при штабе
	std::list<Instructions> instructions;
public:
	FieldCommander() { division = new Division; };
	FieldCommander(std::string fio, std::string rank1, int size, int specialization, Division* div, std::string post1);
	FieldCommander(FieldCommander& original);

	std::string get_Post() const { return post; };
	void setPost(std::string post1) { post = post1; };

	Instructions executeInstruction();
	void addInstruction(Instructions instruction) { instructions.push_back(instruction); };
	void addInstruction(std::string instruction, int number);
	int getInstructionNumber() { return instructions.size(); };

	Division* getDivision() const { return division; };
	void setDivision(Division* div) { division = div; };

	virtual void showInfo(std::ostream& out);

	virtual int getType() const { return 2; };
};

/**
* \brief Командир
*
* Класс, наследуемый от штабиста. Отличается наличием дивизии и возможностью ее изменять/просматривать
*/
class Commander : public Staff {
private:
	Division* division;
public:
	Commander() { division = new Division; };
	Commander(std::string fio, std::string rank1, int size, Division* div, std::string post1);
	Commander(Commander& original);

	Division* getDivision() const { return division; };
	void setDivision(Division* div) { division = div; };

	virtual int getType() const { return 3; };
};

/**
* \brief Учения
*
* Содержат расположение, продолжительность и двух командиров, которые в свою очередь содержат таблицы своих бойцов.
* Определены операции добавления/удаления бойцов у каждого комадира, изменения команды бойца, просмотра командиров,
* подсчета бойцов по команде, званию и специализации.
*/
class Exercises {
private:
	Commander* commander1;
	Commander* commander2;
	Location location;
	int duration;
public:
	Exercises();
	Exercises(Commander* com1, Commander* com2, Location loc) :commander1(com1), commander2(com2), location(loc) {};
	Exercises(Commander* com1, Commander* com2, int x, int y) :commander1(com1), commander2(com2) { location.x = x; location.y = y; };
	Exercises(Exercises& origin);

	Commander* getCommander1() { return commander1; };
	void setCommander1(Commander* commander) { commander1 = commander; };
	Commander* getCommander2() { return commander2; };
	void setCommander2(Commander* commander) { commander2 = commander; };

	Location getLocation() { return location; };
	void setLocation(int x, int y);
	void setLocation(Location loc);

	int getNumberByTeam(int team);
	int getNumberByRank(std::string rank);
	int getNumberBySpecialization(int specialization);
	int getNumberBySpecialization(std::string specialization);

	void swapSoldier(int team, int number);

	void addSoldier(Info info, int team);
	void addSoldier(int number, int condition, Abstract* soldier, int team);

	int getDuration() { return duration; };
	void setDuration(int dur) { duration = dur; };
};

template <typename T>
Table<T>::Table(int size, int allocated, Info* info) : size(size), allocated(allocated) {
	try {
		information = new Info[size];
	}
	catch (std::bad_alloc& ba) {
		std::cerr << ba.what() << std::endl;
	}
	Info* ptr_arr1 = info;
	Info* ptr_arr2 = this->information;
	Info* arr_end = ptr_arr1 + size;
	for (; ptr_arr1 != arr_end; ++ptr_arr1, ++ptr_arr2) {
		ptr_arr2->condition = ptr_arr1->condition;
		ptr_arr2->soldier = ptr_arr1->soldier;
		ptr_arr2->number = ptr_arr1->number;
	}
}

template <typename T>
Table<T>::Table(Table& origin) {
	this->size = origin.size;
	this->allocated = origin.allocated;
	this->information = new T[allocated];
	for (int i = 0; i < size; i++) {
		this->information[i].condition = origin.information[i].condition;
		this->information[i].number = origin.information[i].number;
		this->information[i].soldier = origin.information[i].soldier;
	}
}

template <typename T>
Table<T>::Table(Table&& origin) {
	this->size = origin.size;
	this->allocated = origin.allocated;
	information = origin.information;
	origin.information = nullptr;
}

template <typename T>
void Table<T>::addInfo(Info inf) {
	this->new_size(size + 1);
	int count = 0;
	while (count < size && inf.number > information[count].number)
		count++;
	for (int i = size - 1; i >= count; i--)
		information[i + 1] = information[i];
	information[count].condition = inf.condition;
	information[count].number = inf.number;
	information[count].soldier = inf.soldier;
	size++;
}

template <typename T>
void Table<T>::addInfo(int condition, int number, Abstract* soldier) {
	this->new_size(size + 1);
	int count = 0;
	while (count < size && number > information[count].number)
		count++;
	for (int i = size - 1; i >= count; i--)
		information[i + 1] = information[i];
	information[count].condition = condition;
	information[count].number = number;
	information[count].soldier = soldier;
	size++;
}

template <typename T>
void Table<T>::deleteInfo(const int number) {
	bool flag = false;
	int l = 0, r = size - 1, mid;
	while ((l <= r) && (flag != true)) {
		mid = (l + r) / 2;

		if (information[mid].number == number) {
			flag = true;
			break;
		}
		if (information[mid].number > number)
			r = mid - 1;
		else l = mid + 1;
	}
	if (flag) {
		for (int i = mid + 1; i < size; i++) {
			information[i - 1] = information[i];
		}
		new_size(size - 1);
	}
}

template <typename T>
Info* Table<T>::getInfo(const int number) const  {
	Info* info = binarySearch(information, size, number);
	if (info != nullptr)
		return info;
	else
		throw std::exception("Incorrect number of element");
}

template <typename T>
Abstract* Table<T>::getDescriptor(const int number) const {
	Info* info = binarySearch(information, size, number);
	if (info != nullptr)
		return info->soldier;
	else
		throw std::exception("Incorrect number of element");
}

template <typename T>
void Table<T>::showInfo(std::ostream& out) const {

	//добавить зависимости от типа
	for (int i = 0; i < size; i++) {
		Soldier* soldier;
		Staff* staff;
		FieldCommander* fieldcommander;
		out << information[i].number << ' ' << information[i].condition << ' ' << information[i].soldier->get_FIO() <<
			' ' << information[i].soldier->get_Rank() << ' ' << information[i].soldier->get_Size() << ' ';

		if (information[i].soldier->getType() == -1)
			throw std::exception("Incorrect type of soldier in the table");
		if (information[i].soldier->getType() == 0) {
			soldier = (Soldier*)(information[i].soldier);
			out << soldier->get_Spec_str();
		}
		if (information[i].soldier->getType() == 2) {
			fieldcommander = (FieldCommander*)(information[i].soldier);
			out << fieldcommander->get_Spec_str() << ' ' << fieldcommander->get_Post();
		}
		if (information[i].soldier->getType() == 1 || information[i].soldier->getType() == 3) {
			staff = (Staff*)(information[i].soldier);
			out << staff->get_Post();
		}
		out << std::endl;
	}
}

template <typename T>
std::string Table<T>::getCondition_str(const int number) const {
	Info* info = binarySearch(information, size, number);
	if (info != nullptr)
		return findCondition(info->condition);
	else
		throw std::exception("Incorrect number of element");
}

template <typename T>
void Table<T>::setCondition(const int number, const std::string condition) {
	int buf = -1;
	for (int i = 0; i < 4; i++) {
		if (findCondition(i) == condition) {
			buf = i;
		}
	}
	if (buf == -1)
		throw std::exception("Incorrect condition");
	Info* info = binarySearch(information, size, number);
	if (info != nullptr)
		info->condition = buf;
	else
		throw std::exception("Incorrect number of element");
}

template <typename T>
int Table<T>::getCondition_int(const int number) const {
	Info* info = binarySearch(information, size, number);
	if (info != nullptr)
		return binarySearch(information, size, number)->condition;
	else
		throw std::exception("Incorrect number of element");
}

template <typename T>
void Table<T>::setCondition(const int number, const int cond) {
	Info* info = binarySearch(information, size, number);
	if (info != nullptr)
		info->condition = cond;
	else
		throw std::exception("Incorrect number of element");
}

template <typename T>
int Table<T>::getSpecialSize(const int condition) const {//количество бойцов с определенным состоянием
	int count = 0;
	for (int i = 0; i < size; i++) {
		if (information[i].condition == condition)
			count++;
	}
	return count;
}

template <typename T>
int Table<T>::getSpecialSize(const std::string condition) const {
	int count = 0, buf;
	for (int i = 0; i < 4; i++) {
		if (findCondition(i) == condition) {
			buf = i;
		}
	}
	if (buf == -1)
		throw std::exception("Incorrect condition");
	for (int i = 0; i < size; i++) {
		if (information[i].condition == buf)
			count++;
	}
	return count;
}

template <typename T>
void Table<T>::new_size(const int new_size) {
	int min;
	Info* result = nullptr;
	if (new_size < size)
		min = new_size;
	else
		min = size;
	try {
		result = new Info[new_size];
	}
	catch (std::bad_alloc& ba) {
		std::cerr << ba.what() << std::endl;
	}
	for (int i = 0; i < min; i++) {
		result[i].condition = information[i].condition;
		result[i].soldier = information[i].soldier;
		result[i].number = information[i].number;
	}
	//delete[] information;
	information = result;
	size = min;
	allocated = new_size;
}

Info* binarySearch(Info* information, int size, int number);

template <typename T>
Table<T>& Table<T>::operator=(Table<T>& right) {
	if (this == &right) {
		return *this;
	}
	delete this->information;
	this->size = right.size;
	this->allocated = right.allocated;
	this->information = new T[allocated];
	for (int i = 0; i < size; i++) {
		this->information[i].condition = right.information[i].condition;
		this->information[i].number = right.information[i].number;
		this->information[i].soldier = right.information[i].soldier;
	}
	return *this;
}

template <typename T>
Table<T>& Table<T>::operator=(Table<T>&& right) {
	if (this == &right) {
		return *this;
	}
	this->size = right.size;
	this->allocated = right.allocated;
	information = right.information;
	right.information = nullptr;
	return *this;
}