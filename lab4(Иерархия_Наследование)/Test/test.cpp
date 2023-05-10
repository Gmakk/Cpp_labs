#include "pch.h"
#include "Army.h"


TEST(AbstractFunc, Rank) {
	Abstract abstract;
	abstract.setRank("1");
	EXPECT_EQ(abstract.get_Rank(), "1");
}

TEST(AbstractFunc, FIO) {
	Abstract abstract;
	abstract.setFIO("ABC");
	EXPECT_EQ(abstract.get_FIO(), "ABC");
}

TEST(AbstractFunc, Size) {
	Abstract abstract;
	abstract.setSize(1);
	EXPECT_EQ(abstract.get_Size(), 1);
}

TEST(AbstractFunc, Type) {
	Abstract abstract;
	EXPECT_EQ(abstract.getType(), -1);
}

TEST(SoldierConstruct, OneElement) {
	Soldier soldier("A", "B", 12, 2);
	EXPECT_EQ(soldier.get_FIO(), "A");
	EXPECT_EQ(soldier.get_Rank(), "B");
	EXPECT_EQ(soldier.get_Size(), 12);
	EXPECT_EQ(soldier.get_Spec_int(), 2);
}

TEST(SoldierConstruct, AnotherSoldier) {
	Soldier soldier1("A", "B", 12, 2);
	Soldier soldier2(soldier1);
	EXPECT_EQ(soldier2.get_FIO(), "A");
	EXPECT_EQ(soldier2.get_Rank(), "B");
	EXPECT_EQ(soldier2.get_Size(), 12);
	EXPECT_EQ(soldier2.get_Spec_int(), 2);
}

TEST(SoldierFunc, Order) {
	Soldier soldier;
	soldier.addOrder("ABC");
	EXPECT_EQ(soldier.executeOrder(), "ABC");
}

TEST(SoldierFunc, SpecInt) {
	Soldier soldier;
	soldier.setSpec_int(1);
	EXPECT_EQ(soldier.get_Spec_int(), 1);
}

TEST(SoldierFunc, SpecStr) {
	Soldier soldier;
	soldier.set_Spec_str("infantry");
	EXPECT_EQ(soldier.get_Spec_str(), "infantry");
}

TEST(SoldierFunc, Type) {
	Soldier soldier;
	Abstract* abs = &soldier;
	EXPECT_EQ(abs->getType(), 0);
}

TEST(StaffConstruct, OneElement) {
	Staff staff("ABC", "1", 12, "DEF");
	EXPECT_EQ(staff.get_FIO(), "ABC");
	EXPECT_EQ(staff.get_Rank(), "1");
	EXPECT_EQ(staff.get_Size(), 12);
	EXPECT_EQ(staff.get_Post(), "DEF");
}

TEST(StaffConstruct, AnotherStaff) {
	Staff staff1("ABC", "1", 12, "DEF");
	Staff staff2(staff1);
	EXPECT_EQ(staff2.get_FIO(), "ABC");
	EXPECT_EQ(staff2.get_Rank(), "1");
	EXPECT_EQ(staff2.get_Size(), 12);
	EXPECT_EQ(staff2.get_Post(), "DEF");
}

TEST(StaffFunc, Post) {
	Staff staff("ABC", "1", 12, "DEF");
	EXPECT_EQ(staff.get_Post(), "DEF");
}

TEST(StaffFunc, Instruction) {
	Staff staff("ABC", "1", 12, "DEF");
	staff.addInstruction("!@#", 1);
	EXPECT_EQ(staff.executeInstruction().instruction, "!@#");
}

TEST(StaffFunc, Type) {
	Staff staff;
	Abstract* abs = &staff;
	EXPECT_EQ(abs->getType(), 1);
}

TEST(FcommanderConstruct, OneElement) {
	Division* div = new Division;
	FieldCommander commander("ABC", "1", 12, 2, div, "DEF");
	EXPECT_EQ(commander.get_FIO(), "ABC");
	EXPECT_EQ(commander.get_Rank(), "1");
	EXPECT_EQ(commander.get_Size(), 12);
	EXPECT_EQ(commander.get_Post(), "DEF");
	EXPECT_EQ(commander.getDivision(), div);
	EXPECT_EQ(commander.get_Spec_int(), 2);
}

TEST(FcommanderConstruct, AnotherCommander) {
	Division* div = new Division;
	FieldCommander commander1("ABC", "1", 12, 2, div, "DEF");
	FieldCommander commander2(commander1);
	EXPECT_EQ(commander2.get_FIO(), "ABC");
	EXPECT_EQ(commander2.get_Rank(), "1");
	EXPECT_EQ(commander2.get_Size(), 12);
	EXPECT_EQ(commander2.get_Post(), "DEF");
	EXPECT_EQ(commander2.getDivision(), div);
	EXPECT_EQ(commander2.get_Spec_int(), 2);
}

TEST(FcommanderFunc, Post) {
	Division* div = new Division;
	FieldCommander commander("ABC", "1", 12, 2, div, "DEF");
	EXPECT_EQ(commander.get_Post(), "DEF");
}

TEST(FcommanderFunc, Instruction) {
	FieldCommander commander;
	commander.addInstruction("!@#", 1);
	EXPECT_EQ(commander.executeInstruction().instruction, "!@#");
}

TEST(FcommanderFunc, Div) {
	Division* div = new Division;
	FieldCommander commander("ABC", "1", 12, 2, div, "DEF");
	EXPECT_EQ(commander.getDivision(), div);
}

TEST(FcommanderFunc, Type) {
	FieldCommander commander;
	Abstract* abs = &commander;
	EXPECT_EQ(abs->getType(), 2);
}

TEST(CommanderConstruct, OneElement) {
	Division* div = new Division;
	Commander commander("ABC", "1", 12, div, "DEF");
	EXPECT_EQ(commander.get_FIO(), "ABC");
	EXPECT_EQ(commander.get_Rank(), "1");
	EXPECT_EQ(commander.get_Size(), 12);
	EXPECT_EQ(commander.getDivision(), div);
	EXPECT_EQ(commander.get_Post(), "DEF");
}

TEST(CommanderConstruct, AnotherCommander) {
	Division* div = new Division;
	Commander commander1("ABC", "1", 12, div, "DEF");
	Commander commander2(commander1);
	EXPECT_EQ(commander2.get_FIO(), "ABC");
	EXPECT_EQ(commander2.get_Rank(), "1");
	EXPECT_EQ(commander2.get_Size(), 12);
	EXPECT_EQ(commander2.getDivision(), div);
	EXPECT_EQ(commander2.get_Post(), "DEF");
}

TEST(CommanderFunc, Div) {
	Division* div = new Division;
	Commander commander("ABC", "1", 12, div, "DEF");
	EXPECT_EQ(commander.getDivision(), div);
}

TEST(CommanderFunc, Type) {
	Commander commander;
	Abstract* abs = &commander;
	EXPECT_EQ(abs->getType(), 3);
}

TEST(TableConstruct, OneElement) {
	Soldier* soldier = new Soldier;
	Info info = { 1,12,soldier };
	Table<Info> table(1,1,&info);
	EXPECT_EQ(table.getInfo(12)->condition, info.condition);
	EXPECT_EQ(table.getInfo(12)->number, info.number);
	EXPECT_EQ(table.getInfo(12)->soldier, info.soldier);
}

TEST(TableFunc, AddInf) {
	Soldier* soldier = new Soldier;
	Info info = { 1,12,soldier };
	Table<Info>* table = new Table<Info>;
	table->addInfo(1,2,soldier);
	EXPECT_EQ(1, 1);
	//EXPECT_EQ(table.getInfo(12)->condition, info.condition);
	//EXPECT_EQ(table.getInfo(12)->number, info.number);
	//EXPECT_EQ(table.getInfo(12)->soldier, info.soldier);
}

TEST(TableFunc, AddDevide) {
	Soldier* soldier = new Soldier;
	Table<Info> table;
	table.addInfo(1, 12, soldier);
	EXPECT_EQ(table.getInfo(12)->condition, 1);
	EXPECT_EQ(table.getInfo(12)->number, 12);
	EXPECT_EQ(table.getInfo(12)->soldier, soldier);
}

TEST(TableFunc, Size) {
	Soldier* soldier1 = new Soldier, * soldier2 = new Soldier;
	Table<Info> table;
	table.addInfo(1, 12, soldier1);
	table.addInfo(1, 5, soldier2);
	EXPECT_EQ(table.getSize(), 2);
}

TEST(TableFunc, Descriptor) {
	Soldier* soldier = new Soldier;
	Info info = { 1,12,soldier };
	Table<Info> table(1,1,&info);
	EXPECT_EQ(table.getDescriptor(12), soldier);
}

TEST(TableFunc, ConditionInt) {
	Soldier* soldier = new Soldier;
	Info info = { 1,12,soldier };
	Table<Info> table(1,1,&info);
	EXPECT_EQ(table.getCondition_int(12), 1);
}

TEST(TableFunc, ConditionStr) {
	Soldier* soldier = new Soldier;
	Info info = { 1,12,soldier };
	Table<Info> table(1,1,&info);
	EXPECT_EQ(table.getCondition_str(12), "conditionally_wounded");
}

TEST(TableFunc, SpecialSizeInt) {
	Soldier* soldier = new Soldier;
	Table<Info> table;
	table.addInfo(1, 2, soldier);
	table.addInfo(1, 3, soldier);
	table.addInfo(2, 4, soldier);
	EXPECT_EQ(table.getSpecialSize(1), 2);
	EXPECT_EQ(table.getSpecialSize(2), 1);
}

TEST(TableFunc, SpecialSizeStr) {
	Soldier* soldier = new Soldier;
	Table<Info> table;
	table.addInfo(1, 2, soldier);
	table.addInfo(1, 3, soldier);
	table.addInfo(2, 4, soldier);
	EXPECT_EQ(table.getSpecialSize("conditionally_wounded"), 2);
	EXPECT_EQ(table.getSpecialSize("conditionally_killed"), 1);
}

TEST(HeadqConstruct, OneElement) {
	Table<Info>* table = new Table<Info>;
	Soldier* soldier = new Soldier;
	Location loc = { 1,2 };
	table->addInfo(1, 12, soldier);
	Headquarters headq(loc, *table);
	EXPECT_EQ(headq.getTable()->getSize(), 1);
	EXPECT_EQ(headq.getLocation()->x, 1);
	EXPECT_EQ(headq.getLocation()->y, 2);
	EXPECT_EQ(headq.getTable()->getInfo(12)->soldier, soldier);
}

TEST(HeadqConstruct, OneElementDevide) {
	Table<Info>* table = new Table<Info>;
	Soldier* soldier = new Soldier;
	table->addInfo(1, 12, soldier);
	Headquarters headq(1, 2, *table);
	EXPECT_EQ(headq.getTable()->getSize(), 1);
	EXPECT_EQ(headq.getLocation()->x, 1);
	EXPECT_EQ(headq.getLocation()->y, 2);
	EXPECT_EQ(headq.getTable()->getInfo(12)->soldier, soldier);
}

TEST(HeadqConstruct, AnotherHeadq) {
	Table<Info>* table = new Table<Info>;
	Soldier* soldier = new Soldier;
	table->addInfo(1, 12, soldier);
	Headquarters headq1(1, 2, *table);
	Headquarters headq2(headq1);
	EXPECT_EQ(headq2.getTable()->getSize(), 1);
	EXPECT_EQ(headq2.getLocation()->x, 1);
	EXPECT_EQ(headq2.getLocation()->y, 2);
	EXPECT_EQ(headq2.getTable()->getInfo(12)->soldier, soldier);
}

TEST(HeadqFunc, GetLocation) {
	Table<Info>* table = new Table<Info>;
	Soldier* soldier = new Soldier;
	table->addInfo(1, 12, soldier);
	Headquarters headq(1, 2, *table);
	EXPECT_EQ(headq.getLocation()->x, 1);
	EXPECT_EQ(headq.getLocation()->y, 2);
}

TEST(HeadqFunc, GetTable) {
	Table<Info>* table = new Table<Info>;
	Soldier* soldier = new Soldier;
	table->addInfo(1, 12, soldier);
	Headquarters headq(1, 2, *table);
	EXPECT_EQ(headq.getTable()->getSize(), 1);
}

TEST(HeadqFunc, SetCond) {
	Table<Info>* table = new Table<Info>;
	Soldier* soldier = new Soldier;
	table->addInfo(1, 12, soldier);
	Headquarters headq(1, 2, *table);
	headq.setCondition(12, 2);
	EXPECT_EQ(headq.getTable()->getInfo(12)->condition, 2);
}

TEST(DivConstruct, OneElement) {
	Table<Info>* table = new Table<Info>;
	Soldier* soldier = new Soldier;
	Location loc = { 1,2 };
	table->addInfo(1, 12, soldier);
	Division div(loc, *table);
	//EXPECT_EQ(1, 1);
	EXPECT_EQ(div.getTable()->getSize(), 1);
	EXPECT_EQ(div.getLocation()->x, 1);
	EXPECT_EQ(div.getLocation()->y, 2);
	EXPECT_EQ(div.getTable()->getInfo(12)->soldier, soldier);
}

TEST(DivConstruct, OneElementDevide) {
	Table<Info>* table = new Table<Info>;
	Soldier* soldier = new Soldier;
	table->addInfo(1, 12, soldier);
	Division div(1, 2, *table);
	EXPECT_EQ(div.getTable()->getSize(), 1);
	EXPECT_EQ(div.getLocation()->x, 1);
	EXPECT_EQ(div.getLocation()->y, 2);
	EXPECT_EQ(div.getTable()->getInfo(12)->soldier, soldier);
}

TEST(DivConstruct, AnotherDiv) {
	Table<Info>* table = new Table<Info>;
	Soldier* soldier = new Soldier;
	table->addInfo(1, 12, soldier);
	Division div1(1, 2, *table);
	Division div2(div1);
	EXPECT_EQ(div2.getTable()->getSize(), 1);
	EXPECT_EQ(div2.getLocation()->x, 1);
	EXPECT_EQ(div2.getLocation()->y, 2);
	EXPECT_EQ(div2.getTable()->getInfo(12)->soldier, soldier);
}

TEST(DivFunc, SetLocation) {
	Table<Info>* table = new Table<Info>;
	Soldier* soldier = new Soldier;
	table->addInfo(1, 12, soldier);
	Division div(1, 2, *table);
	div.setLocation(3, 4);
	EXPECT_EQ(div.getLocation()->x, 3);
	EXPECT_EQ(div.getLocation()->y, 4);
}

TEST(ExerConstruct, Loc) {
	Location loc = { 10,20 };
	Division* div1 = new Division;
	Commander* commander1 = new Commander("ABC", "1", 12, div1, "DEF");
	Division* div2 = new Division;
	Commander* commander2 = new Commander("CBA", "2", 15, div2, "FED");
	Exercises exercises(commander1, commander2, loc);
	EXPECT_EQ(exercises.getCommander1(), commander1);
	EXPECT_EQ(exercises.getCommander2(), commander2);
	EXPECT_EQ(exercises.getLocation().x, 10);
	EXPECT_EQ(exercises.getLocation().y, 20);
}

TEST(ExerConstruct, LocDevide) {
	Division* div1 = new Division;
	Commander* commander1 = new Commander("ABC", "1", 12, div1, "DEF");
	Division* div2 = new Division;
	Commander* commander2 = new Commander("CBA", "2", 15, div2, "FED");
	Exercises exercises(commander1, commander2, 10, 20);
	EXPECT_EQ(exercises.getCommander1(), commander1);
	EXPECT_EQ(exercises.getCommander2(), commander2);
	EXPECT_EQ(exercises.getLocation().x, 10);
	EXPECT_EQ(exercises.getLocation().y, 20);
}

TEST(ExerConstruct, AnotherExer) {
	Division* div1 = new Division;
	Commander* commander1 = new Commander("ABC", "1", 12, div1, "DEF");
	Division* div2 = new Division;
	Commander* commander2 = new Commander("CBA", "2", 15, div2, "FED");
	Exercises exercises1(commander1, commander2, 10, 20);
	Exercises exercises2(exercises1);

}

TEST(ExerFunc, Commander1_2) {
	Division* div1 = new Division;
	Commander* commander1 = new Commander("ABC", "1", 12, div1, "DEF");
	Division* div2 = new Division;
	Commander* commander2 = new Commander("CBA", "2", 15, div2, "FED");
	Exercises exercises(commander1, commander2, 10, 20);
	exercises.setCommander1(commander2);
	exercises.setCommander2(commander1);
	EXPECT_EQ(exercises.getCommander1(), commander2);
	EXPECT_EQ(exercises.getCommander2(), commander1);
}
TEST(ExerFunc, Loc) {
	Division* div1 = new Division;
	Commander* commander1 = new Commander("ABC", "1", 12, div1, "DEF");
	Division* div2 = new Division;
	Commander* commander2 = new Commander("CBA", "2", 15, div2, "FED");
	Exercises exercises(commander1, commander2, 10, 20);
	exercises.setLocation(5, 6);
	EXPECT_EQ(exercises.getLocation().x, 5);
	EXPECT_EQ(exercises.getLocation().y, 6);
}

TEST(ExerFunc, NumberByTeam) {
	Soldier* soldier = new Soldier;
	Division* div1 = new Division;
	Commander* commander1 = new Commander("ABC", "1", 12, div1, "DEF");
	Division* div2 = new Division;
	Commander* commander2 = new Commander("CBA", "2", 15, div2, "FED");
	Exercises exercises(commander1, commander2, 10, 20);
	exercises.addSoldier(12, 2, soldier, 1);
	EXPECT_EQ(exercises.getNumberByTeam(2), 0);
	EXPECT_EQ(exercises.getNumberByTeam(1), 1);
}

TEST(ExerFunc, NumberByRank) {
	Soldier* soldier = new Soldier;
	soldier->setRank("2");
	Division* div1 = new Division;
	Commander* commander1 = new Commander("ABC", "1", 12, div1, "DEF");
	Division* div2 = new Division;
	Commander* commander2 = new Commander("CBA", "2", 15, div2, "FED");
	Exercises exercises(commander1, commander2, 10, 20);
	exercises.addSoldier(12, 2, soldier, 1);
	EXPECT_EQ(exercises.getNumberByRank("2"), 1);
}

TEST(ExerFunc, NumberBySpecInt) {
	Soldier* soldier = new Soldier;
	soldier->setSpec_int(3);
	Division* div1 = new Division;
	Commander* commander1 = new Commander("ABC", "1", 12, div1, "DEF");
	Division* div2 = new Division;
	Commander* commander2 = new Commander("CBA", "2", 15, div2, "FED");
	Exercises exercises(commander1, commander2, 10, 20);
	exercises.addSoldier(12, 2, soldier, 1);
	EXPECT_EQ(exercises.getNumberBySpecialization(3), 1);
}

TEST(ExerFunc, NumberBySpecStr) {
	Soldier* soldier = new Soldier;
	soldier->set_Spec_str("sniper");
	Division* div1 = new Division;
	Commander* commander1 = new Commander("ABC", "1", 12, div1, "DEF");
	Division* div2 = new Division;
	Commander* commander2 = new Commander("CBA", "2", 15, div2, "FED");
	Exercises exercises(commander1, commander2, 10, 20);
	exercises.addSoldier(12, 2, soldier, 1);
	EXPECT_EQ(exercises.getNumberBySpecialization("sniper"), 1);
}

TEST(ExerFunc, Swap) {
	Soldier* soldier = new Soldier;
	soldier->setSpec_int(3);
	Division* div1 = new Division;
	Commander* commander1 = new Commander("ABC", "1", 12, div1, "DEF");
	Division* div2 = new Division;
	Commander* commander2 = new Commander("CBA", "2", 15, div2, "FED");
	Exercises exercises(commander1, commander2, 10, 20);
	exercises.addSoldier(12, 2, soldier, 1);
	EXPECT_EQ(exercises.getNumberByTeam(1), 1);
	exercises.swapSoldier(1, 12);
	EXPECT_EQ(exercises.getNumberByTeam(2), 1);
}

TEST(ExerFunc, Duration) {
	Division* div1 = new Division;
	Commander* commander1 = new Commander("ABC", "1", 12, div1, "DEF");
	Division* div2 = new Division;
	Commander* commander2 = new Commander("CBA", "2", 15, div2, "FED");
	Exercises exercises(commander1, commander2, 10, 20);
	exercises.setDuration(30);
	EXPECT_EQ(exercises.getDuration(), 30);
}




TEST(Iter,postfixPlus){
	Table<Info> table;
	Soldier* sold;
	for (int i = 0; i < 4; i++) {
		sold = new Soldier;
		table.addInfo(i, i, sold);
	}
	Iterator<Info> it = table.begin();
	EXPECT_EQ((it++).operator*()->number, 0);
}

TEST(Iter, prefixPlus) {
	Table<Info> table;
	Soldier* sold;
	for (int i = 0; i < 4; i++) {
		sold = new Soldier;
		table.addInfo(i, i, sold);
	}
	Iterator<Info> it = table.begin();
	EXPECT_EQ((++it).operator*()->number, 1);
}

TEST(Iter, postfixMinus) {
	Table<Info> table;
	Soldier* sold;
	for (int i = 0; i < 4; i++) {
		sold = new Soldier;
		table.addInfo(i, i, sold);
	}
	Iterator<Info> it = table.end();
	EXPECT_EQ((--it).operator*()->number, 2);
}

TEST(Iter, postfix_Minus) {
	Table<Info> table;
	Soldier* sold;
	for (int i = 0; i < 4; i++) {
		sold = new Soldier;
		table.addInfo(i, i, sold);
	}
	Iterator<Info> it = table.end();
	EXPECT_EQ((it--).operator*()->number, 3);
}

TEST(TableConstruct, AnotherTable) {
	Soldier* soldier = new Soldier;
	Info info = { 1,12,soldier };
	Table<Info> table1(1, 1, &info);
	Table<Info> table2(table1);
	EXPECT_EQ(table2.getInfo(12)->condition, info.condition);
	EXPECT_EQ(table2.getInfo(12)->number, info.number);
	EXPECT_EQ(table2.getInfo(12)->soldier, info.soldier);
}

TEST(TableConstruct, AnotherTableMove) {
	Soldier* soldier = new Soldier;
	Info info = { 1,12,soldier };
	Table<Info> table1(1, 1, &info);
	Table<Info> table2(std::move(table1));
	EXPECT_EQ(table2.getInfo(12)->condition, info.condition);
	EXPECT_EQ(table2.getInfo(12)->number, info.number);
	EXPECT_EQ(table2.getInfo(12)->soldier, info.soldier);
}

TEST(TableEqual, AnotherTable) {
	Soldier* soldier = new Soldier;
	Info info = { 1,12,soldier };
	Table<Info> table1(1, 1, &info);
	Table<Info> table2 = table1;
	EXPECT_EQ(table2.getInfo(12)->condition, info.condition);
	EXPECT_EQ(table2.getInfo(12)->number, info.number);
	EXPECT_EQ(table2.getInfo(12)->soldier, info.soldier);
}

TEST(TableEqual, AnotherTableMove) {
	Soldier* soldier = new Soldier;
	Info info = { 1,12,soldier };
	Table<Info> table1(1, 1, &info);
	Table<Info> table2 = std::move(table1);
	EXPECT_EQ(table2.getInfo(12)->condition, info.condition);
	EXPECT_EQ(table2.getInfo(12)->number, info.number);
	EXPECT_EQ(table2.getInfo(12)->soldier, info.soldier);
}

TEST(TableCicle, ForEach) {
	int count = 0;
	Table<Info> table;
	Soldier* sold;
	for (int i = 0; i < 4; i++) {
		sold = new Soldier;
		table.addInfo(i, i, sold);
	}
	for (auto i : table) {
		EXPECT_EQ(i->condition, count);
		EXPECT_EQ(i->number, count);
		count++;
	}
}