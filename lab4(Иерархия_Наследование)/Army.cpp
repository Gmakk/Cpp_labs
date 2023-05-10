#include "pch.h"
#include "framework.h"
#include "Army.h"

/**
* \brief Набор определений
*
* Определяет все возможные для использования состояния и специализации солдат
*/
namespace Definition {
	extern std::string condition[4] = { "healthy", "conditionally_wounded",
			"conditionally_killed", "conditionally_missing" };

	extern std::string specialization[8] = {
		"infantry", "special_forces", "scout",
		"sniper", "sapper", "RHBZ", "medic", "radio_operator" };
}

std::string findCondition(int number) {
	return Definition::condition[number];
}

std::string findSpecialization(int number) {
	return Definition::specialization[number];
}

Info* binarySearch(Info* information, int size, int number) {
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
	if (flag)
		return &information[mid];
	else
		return nullptr;
}

Soldier::Soldier(std::string fio, std::string rank1, int size, int specialization) :spec(specialization) {
	FIO = fio;
	rank = rank1;
	shape_size = size;
}

Soldier::Soldier(Soldier& original) {
	FIO = original.FIO;
	rank = original.rank;
	shape_size = original.shape_size;
	spec = original.spec;
	orders = original.orders;
}

Staff::Staff(std::string fio, std::string rank1, int size, std::string post1) : post(post1) {
	FIO = fio;
	rank = rank1;
	shape_size = size;
}

Staff::Staff(Staff& original) {
	FIO = original.FIO;
	rank = original.rank;
	shape_size = original.shape_size;
	post = original.post;
	instructions = original.instructions;
}

std::string Soldier::executeOrder() {
	std::string buf = orders.front();
	orders.pop_front();
	return buf;
}

std::string Soldier::get_Spec_str() const{
	return Definition::specialization[spec]; 
};

void Soldier::set_Spec_str(std::string str) {
	for (int i = 0; i < 8; i++) {
		if (Definition::specialization[i] == str) {
			spec = i;
			return;
		}
	}
	throw std::exception("Incorrect specialization");
}

void Soldier::showInfo(std::ostream& out) const {
	out << ' ' << FIO << ' ' << rank << ' ' << shape_size << ' ' << findSpecialization(spec);
	//out << ' ' << FIO << ' ' << rank << ' '  << ' ' << findSpecialization(spec);
	for (int i = 0; i < orders.size(); i++)
		out << ' ' << orders[i];
	out << std::endl;
}

Instructions Staff::executeInstruction() {
	Instructions buf = instructions.front();
	instructions.pop_front();
	return buf;
}

void Staff::addInstruction(std::string instruction, int number) {
	Instructions buf = { instruction,number };
	instructions.push_back(buf);
}

void Staff::showInfo(std::ostream& out) {
	std::list<Instructions>::iterator iter;
	iter = instructions.begin();
	out << ' ' << FIO << ' ' << rank << ' ' << shape_size << ' ' << post;
	for (int i = 0; i < instructions.size(); i++) {
		out << ' ' << (*iter).number << ' ' << (*iter).instruction;
		iter++;
	}
	out << std::endl;
}

FieldCommander::FieldCommander(FieldCommander& original) {
	FIO = original.FIO;
	rank = original.rank;
	shape_size = original.shape_size;
	spec = original.spec;
	orders = original.orders;
	division = original.division;
	post = original.post;
	instructions = original.instructions;
}

FieldCommander::FieldCommander(std::string fio, std::string rank1, int size, int specialization, Division* div, std::string post1) :division(div), post(post1) {
	spec = specialization;
	FIO = fio;
	rank = rank1;
	shape_size = size;
}

Instructions FieldCommander::executeInstruction() {
	Instructions buf = instructions.front();
	instructions.pop_front();
	return buf;
}

void FieldCommander::addInstruction(std::string instruction, int number) {
	Instructions buf = { instruction,number };
	instructions.push_back(buf);
}

void FieldCommander::showInfo(std::ostream& out) {
	std::list<Instructions>::iterator iter;
	iter = instructions.begin();
	out << ' ' << FIO << ' ' << rank << ' ' << shape_size << ' ' << Definition::specialization[spec] << post;
	for (int i = 0; i < orders.size(); i++)
		out << ' ' << orders[i];
	for (int i = 0; i < instructions.size(); i++) {
		out << ' ' << (*iter).number << ' ' << (*iter).instruction;
		iter++;
	}
	out << std::endl;
}

Commander::Commander(std::string fio, std::string rank1, int size, Division* div, std::string post1) :division(div) {
	post = post1;
	FIO = fio;
	rank = rank1;
	shape_size = size;
}

Commander::Commander(Commander& original) {
	FIO = original.FIO;
	rank = original.rank;
	shape_size = original.shape_size;
	division = original.division;
	post = original.post;
	instructions = original.instructions;
}

Headquarters::Headquarters() {
	table = new Table<Info>;
	location = new Location;
}

Headquarters::Headquarters(int x, int  y, Table<Info>& table1) {
	Iterator<Info> it = table1.begin();
	table = new Table<Info>;
	location = new Location;
	location->x = x;
	location->y = y;
	for (int i = 0; i < table1.getSize(); i++) {
		table->addInfo(*it.operator*());
		it.operator++();
	}
}

Headquarters::Headquarters(Location loc, Table<Info>& table1) {
	Iterator<Info> it = table1.begin();
	table = new Table<Info>;
	location = new Location;
	location->x = loc.x;
	location->y = loc.y;
	for (int i = 0; i < table1.getSize(); i++) {
		table->addInfo(*it.operator*());
		it.operator++();
	}
}

Headquarters::Headquarters(Headquarters& original) {
	Iterator<Info> it = original.getTable()->begin();
	location = new Location;
	location->x = original.getLocation()->x;
	location->y = original.getLocation()->y;
	table = new Table<Info>;
	for (int i = 0; i < original.getTable()->getSize(); i++) {
		table->addInfo(*it.operator*());
		it.operator++();
	}
}

Headquarters::~Headquarters() {
	delete location;
	delete table;
}

void Headquarters::setCondition(int number, int condition) {
	Iterator<Info> it = table->begin();
	Soldier* soldier;
	Info info = *table->getInfo(number);
	int medic_check = 0;
	if (condition == 0) {
		if (info.condition == 2)
			throw std::exception("There is no way to change the type like that");
		if (info.condition == 1) {
			for (int i = 0; i < table->getSize(); i++) {
				if (it.operator*()->soldier->getType() == 0 || it.operator*()->soldier->getType() == 2) {
					soldier = (Soldier*)it.operator*()->soldier;
					if (soldier->get_Spec_int() == 6 && it.operator*()->number != number) {
						medic_check = 1;
						break;
					}
				}
				it.operator++();
			}
			if (medic_check == 0)
				throw std::exception("There is no medic in the division");
			else
				table->setCondition(number, 0);
		}
		if (info.condition == 3)
			table->setCondition(number, 0);
		return;
	}
	if (condition == 1) {
		if (info.condition == 0)
			table->setCondition(number, 1);
		else
			throw std::exception("There is no way to change the type like that");
		return;
	}
	if (condition == 2) {
		if (info.condition == 3)
			throw std::exception("There is no way to change the type like that");
		else
			table->setCondition(number, 2);
		return;
	}
	if (condition == 3) {
		if (info.condition == 2)
			throw std::exception("There is no way to change the type like that");
		else
			table->setCondition(number, 3);
		return;
	}
}

std::vector<Headquarters*> Headquarters::devide(std::string maxRank, std::string newPost) {
	Staff* staff;
	FieldCommander* fcommander;
	Commander* commander_new;
	Location* location_new;
	Table<Info>* table_new;
	Headquarters* headquarters;
	Iterator<Info> it = table->begin();
	std::vector<Headquarters*> result;
	for (int i = 0; i < table->getSize(); i++) {
		if (it.operator*()->soldier->get_Rank() == maxRank) {
			commander_new = new Commander;
			if (it.operator*()->soldier->getType() != 3) {
				commander_new->setFIO(it.operator*()->soldier->get_FIO());
				commander_new->setRank(it.operator*()->soldier->get_Rank());
				commander_new->setSize(it.operator*()->soldier->get_Size());
			}
			switch (it.operator*()->soldier->getType())
			{
			case 0:
				commander_new->setPost(newPost);
				break;
			case 1:
				commander_new->setPost(newPost);
				staff = (Staff*)(it.operator*()->soldier);
				for (int i = 0; i < staff->getInstructionNumber(); i++) {
					commander_new->addInstruction(staff->executeInstruction());
				}
				break;
			case 2:
				commander_new->setPost(newPost);
				fcommander = (FieldCommander*)(it.operator*()->soldier);
				for (int i = 0; i < fcommander->getInstructionNumber(); i++) {
					commander_new->addInstruction(fcommander->executeInstruction());
				}
				commander_new->setDivision(fcommander->getDivision());
				break;
			case 3:
				commander_new = (Commander*)it.operator*()->soldier;
				break;
			default:
				break;
			}
			table_new = new Table<Info>;
			table_new->addInfo(it.operator*()->condition, it.operator*()->number, commander_new);
			table->deleteInfo(it.operator*()->number);
			headquarters = new Headquarters(location->x, location->y, *table_new);
			result.push_back(headquarters);
			delete headquarters;
		}
		it.operator++();
	}
	it = table->begin();
	for (int i = 0; i < result.size(); i++) {
		for (int g = 0; g < (table->getSize() / result.size()); g++) {
			result[i]->getTable()->addInfo(it.operator*()->condition, it.operator*()->number, it.operator*()->soldier);
			table->deleteInfo(it.operator*()->number);
			it.operator++();
		}
	}
	return result;
}

Division::Division() {
	table = new Table<Info>;
	location = new Location;
}

Division::Division(int x, int  y, Table<Info>& table1) {
	Iterator<Info> it = table1.begin();
	table = new Table<Info>;
	location = new Location;
	location->x = x;
	location->y = y;
	for (int i = 0; i < table1.getSize(); i++) {
		table->addInfo(*it.operator*());
		it.operator++();
	}
}

Division::Division(Location loc, Table<Info>& table1) {
	Iterator<Info> it = table1.begin();
	table = new Table<Info>;
	location = new Location;
	location->x = loc.x;
	location->y = loc.y;
	for (int i = 0; i < table1.getSize(); i++) {
		table->addInfo(*it.operator*());
		it.operator++();
	}
}

Division::Division(Division& original) {
	Iterator<Info> it = original.getTable()->begin();
	location = new Location;
	location->x = original.getLocation()->x;
	location->y = original.getLocation()->y;
	table = new Table<Info>;
	for (int i = 0; i < original.getTable()->getSize(); i++) {
		table->addInfo(*it.operator*());
		it.operator++();
	}
}

void Division::setLocation(int x, int y) {
	location->x = x;
	location->y = y;
}

void Division::setLocation(Location loc) {
	location->x = loc.x;
	location->y = loc.y;
}

Exercises::Exercises() {
	commander1 = new Commander;
	commander2 = new Commander;
}

Exercises::Exercises(Exercises& origin) {
	commander1 = origin.commander1;
	commander2 = origin.commander2;
	location = origin.location;
	duration = origin.duration;
}

void Exercises::setLocation(int x, int y) {
	location.x = x;
	location.y = y;
}

void Exercises::setLocation(Location loc) {
	location.x = loc.x;
	location.y = loc.y;
}

int Exercises::getNumberByTeam(int team) {
	int count = 0;
	if (team != 1 && team != 2)
		throw std::exception("There is no such team");
	if (team == 1)
		return commander1->getDivision()->getTable()->getSize();
	else
		return commander2->getDivision()->getTable()->getSize();
}

int Exercises::getNumberByRank(std::string rank) {
	Iterator<Info> it = commander1->getDivision()->getTable()->begin();
	int count = 0;
	for (int i = 0; i < commander1->getDivision()->getTable()->getSize(); i++) {
		if (it.operator*()->soldier->get_Rank() == rank)
			count++;
		it.operator++();
	}
	it = commander2->getDivision()->getTable()->begin();
	for (int i = 0; i < commander2->getDivision()->getTable()->getSize(); i++) {
		if (it.operator*()->soldier->get_Rank() == rank)
			count++;
		it.operator++();
	}
	return count;
}

int Exercises::getNumberBySpecialization(int specialization) {//нет у штабиста и командующего
	Iterator<Info> it = commander1->getDivision()->getTable()->begin();
	Soldier* soldier;
	int count = 0;
	for (int i = 0; i < commander1->getDivision()->getTable()->getSize(); i++) {
		if (it.operator*()->soldier->getType() == 0 || it.operator*()->soldier->getType() == 2) {
			soldier = (Soldier*)it.operator*()->soldier;
			if (soldier->get_Spec_int() == specialization)
				count++;
		}
		it.operator++();
	}
	it = commander2->getDivision()->getTable()->begin();
	for (int i = 0; i < commander2->getDivision()->getTable()->getSize(); i++) {
		if (it.operator*()->soldier->getType() == 0 || it.operator*()->soldier->getType() == 2) {
			soldier = (Soldier*)it.operator*()->soldier;
			if (soldier->get_Spec_int() == specialization)
				count++;
		}
		it.operator++();
	}
	return count;
}

int Exercises::getNumberBySpecialization(std::string specialization) {
	Iterator<Info> it = commander1->getDivision()->getTable()->begin();
	Soldier* soldier;
	int count = 0;
	for (int i = 0; i < commander1->getDivision()->getTable()->getSize(); i++) {
		if (it.operator*()->soldier->getType() == 0 || it.operator*()->soldier->getType() == 2) {
			soldier = (Soldier*)it.operator*()->soldier;
			if (soldier->get_Spec_str() == specialization)
				count++;
		}
		it.operator++();
	}
	it = commander2->getDivision()->getTable()->begin();
	for (int i = 0; i < commander2->getDivision()->getTable()->getSize(); i++) {
		if (it.operator*()->soldier->getType() == 0 || it.operator*()->soldier->getType() == 2) {
			soldier = (Soldier*)it.operator*()->soldier;
			if (soldier->get_Spec_str() == specialization)
				count++;
		}
		it.operator++();
	}
	return count;
}

void Exercises::swapSoldier(int team, int number) {
	Info* buf;
	if (team != 1 && team != 2)
		throw std::exception("There is no such team");
	if (team == 1) {
		try {
			commander2->getDivision()->getTable()->addInfo(*commander1->getDivision()->getTable()->getInfo(number));
			commander1->getDivision()->getTable()->deleteInfo(number);
		}
		catch (std::exception ex) {
			throw std::exception("There is no such team");
		}
	}
	else {
		try {
			commander1->getDivision()->getTable()->addInfo(*commander2->getDivision()->getTable()->getInfo(number));
			commander2->getDivision()->getTable()->deleteInfo(number);
		}
		catch (std::exception ex) {
			throw std::exception("There is no such team");
		}
	}
}

void Exercises::addSoldier(Info info, int team) {
	if (team != 1 && team != 2)
		throw std::exception("There is no such team");
	if (team == 1) {
		commander1->getDivision()->getTable()->addInfo(info);
	}
	else {
		commander2->getDivision()->getTable()->addInfo(info);
	}
}

void Exercises::addSoldier(int number, int condition, Abstract* soldier, int team) {
	if (team != 1 && team != 2)
		throw std::exception("There is no such team");
	if (team == 1) {
		commander1->getDivision()->getTable()->addInfo(condition, number, soldier);
	}
	else {
		commander2->getDivision()->getTable()->addInfo(condition, number, soldier);
	}
}