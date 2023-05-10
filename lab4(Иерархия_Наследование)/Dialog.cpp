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

int D_Show(Exercises& ex) {
	std::cout << "Duration:" << std::endl;
	std::cout << ex.getDuration() << std::endl;
	std::cout << "Location:" << std::endl;
	std::cout << "X: " << ex.getLocation().x << " Y: " << ex.getLocation().y << std::endl;
	std::cout << "Commander 1:" << std::endl;
	ex.getCommander1()->showInfo(std::cout);
	std::cout << "Division 1:" << std::endl;
	ex.getCommander1()->getDivision()->getTable()->showInfo(std::cout);
	std::cout << "Commander 2:" << std::endl;
	ex.getCommander2()->showInfo(std::cout);
	std::cout << "Division 2:" << std::endl;
	ex.getCommander2()->getDivision()->getTable()->showInfo(std::cout);
	return 1;
}

int D_Commander(Exercises& ex) {
	int result, shape_size, count = 0;
	std::string post, FIO, rank;
	Instructions inst;
	Division* div;
	Commander* com;
	std::cout << "1-change the first commander   2-change the second commander" << std::endl;
	getPositive(result);
	switch (result)
	{
	case 1:
		delete ex.getCommander1();
		std::cout << "Enter FIO, rank, shape size, post" << std::endl;
		std::cin >> FIO >> rank >> shape_size >> post;
		std::cout << "How many instructions to add?" << std::endl;
		div = new Division;
		com = new Commander(FIO, rank, shape_size, div, post);
		getPositive(count);
		for (int i = 0; i < count; i++) {
			std::cin >> inst.instruction;
			inst.number = i;
			com->addInstruction(inst);
		}
		ex.setCommander1(com);
		break;
	case 2:
		delete ex.getCommander2();
		std::cout << "Enter FIO, rank, shape size, post" << std::endl;
		std::cin >> FIO >> rank >> shape_size >> post;
		std::cout << "How many instructions to add?" << std::endl;
		div = new Division;
		com = new Commander(FIO, rank, shape_size, div, post);
		getPositive(count);
		for (int i = 0; i < count; i++) {
			std::cin >> inst.instruction;
			inst.number = i;
			com->addInstruction(inst);
		}
		ex.setCommander2(com);
		break;
	default:
		std::cout << "There is no such option" << std::endl;
		break;
	}
	return 1;
}

int D_Map(Exercises& ex) {
	int result, x, y;
	std::cout << "1-show location   2-change location" << std::endl;
	getPositive(result);
	switch (result)
	{
	case 1:
		std::cout << "X: " <<ex.getLocation().x << " Y: " << ex.getLocation().y << std::endl;
		break;
	case 2:
		std::cout << "Enter the x and y coordinates" << std::endl;
		getValue(x);
		getValue(y);
		ex.setLocation(x, y);
		break;
	default:
		std::cout << "There is no such option" << std::endl;
		break;
	}
	return 1;
}

int D_Duration(Exercises& ex) {
	int result, duration;
	std::cout << "1-show duration   2-change duration" << std::endl;
	getPositive(result);
	switch (result)
	{
	case 1:
		std::cout << "Duration: " << ex.getDuration() << std::endl;
		break;
	case 2:
		std::cout << "Enter new duration" << std::endl;
		getPositive(duration);
		ex.setDuration(duration);
		break;
	default:
		std::cout << "There is no such option" << std::endl;
		break;
	}
	return 1;
}

int D_Soldiers(Exercises& ex) {
	int result, team, condition, number, spec;
	int shape_size, count = 0;
	std::string post, FIO, rank, order;
	Instructions inst;
	Division* div = nullptr;
	Commander* com = nullptr;
	FieldCommander* fcom = nullptr;
	Soldier* sold = nullptr;
	Staff* staff = nullptr;
	Abstract* abstract;
	std::cout << "1-first team   2-second team" << std::endl;
	getPositive(team);
	if (team != 1 && team != 2) {
		std::cout << "There is no such option" << std::endl;
		return 1;
	}
	std::cout << "1-add soldier   2-find soldier   3-delete soldier" << std::endl;
	getPositive(result);
	switch (result)
	{
	case 1:
		std::cout << "1-soldier   2-staff   3-field commander   4-commander" << std::endl;
		getPositive(result);
		switch (result)
		{
		case 1:
			sold = nullptr;
			delete sold;
			std::cout << "Enter FIO, rank, shape size, specialization" << std::endl;
			std::cin >> FIO >> rank >> shape_size >> spec;
			std::cout << "How many orders to add?" << std::endl;
			sold = new Soldier(FIO, rank, shape_size, spec);
			getPositive(count);
			for (int i = 0; i < count; i++) {
				std::cin >> order;
				sold->addOrder(order);
			}
			abstract = sold;
			break;
		case 2:
			staff = nullptr;
			delete staff;
			std::cout << "Enter FIO, rank, shape size, post" << std::endl;
			std::cin >> FIO >> rank >> shape_size >> post;
			std::cout << "How many instructions to add?" << std::endl;
			staff = new Staff(FIO, rank, shape_size, post);
			getPositive(count);
			for (int i = 0; i < count; i++) {
				std::cin >> inst.instruction;
				inst.number = i;
				staff->addInstruction(inst);
			}
			abstract = staff;
			break;
		case 3:
			fcom = nullptr;
			div = nullptr;
			delete fcom;
			delete div;
			std::cout << "Enter FIO, rank, shape size, specialization, post" << std::endl;
			std::cin >> FIO >> rank >> shape_size >> spec >> post;
			std::cout << "How many orders to add?" << std::endl;
			div = new Division;
			fcom = new FieldCommander(FIO, rank, shape_size, spec, div, post);
			getPositive(count);
			for (int i = 0; i < count; i++) {
				std::cin >> order;
				fcom->addOrder(order);
			}
			std::cout << "How many instructions to add?" << std::endl;
			getPositive(count);
			for (int i = 0; i < count; i++) {
				std::cin >> inst.instruction;
				inst.number = i;
				fcom->addInstruction(inst);
			}
			abstract = fcom;
			break;
		case 4:
			com = nullptr;
			div = nullptr;
			delete com;
			delete div;
			std::cout << "Enter FIO, rank, shape size, post" << std::endl;
			std::cin >> FIO >> rank >> shape_size >> post;
			std::cout << "How many instructions to add?" << std::endl;
			div = new Division;
			com = new Commander(FIO, rank, shape_size, div, post);
			getPositive(count);
			for (int i = 0; i < count; i++) {
				std::cin >> inst.instruction;
				inst.number = i;
				com->addInstruction(inst);
			}
			abstract = com;
			break;
		default:
			std::cout << "There is no such option" << std::endl;
			return 1;
			break;
		}
		std::cout << "Enter number:" << std::endl;
		getPositive(number);
		std::cout << "Enter condition:" << std::endl;
		getPositive(condition);
		ex.addSoldier(number, condition, abstract, team);
		break;
	case 2:
		std::cout << "Enter number of soldier:" << std::endl;
		getPositive(number);
		try {
			if (team == 1) {
				ex.getCommander1()->getDivision()->getTable()->getDescriptor(number)->showInfo(std::cout);
			}
			else {
				ex.getCommander2()->getDivision()->getTable()->getDescriptor(number)->showInfo(std::cout);
			}
		}
		catch (std::exception exep) {
			std::cout << exep.what() << std::endl;
		}
		break;
	case 3:
		std::cout << "Enter number of soldier:" << std::endl;
		getPositive(number);
		if (team == 1) {
			ex.getCommander1()->getDivision()->getTable()->deleteInfo(number);
		}
		else {
			ex.getCommander2()->getDivision()->getTable()->deleteInfo(number);
		}
		break;
	default:
		std::cout << "There is no such option" << std::endl;
		return 1;
		break;
	}
	
}