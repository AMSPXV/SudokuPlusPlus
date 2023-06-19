#include "DebuggingFunctions.h"
#include "TableInfo.h"
#include <iostream>
#include <ctime>
#include "LogicHandler.h"

void generateData(short help[][9])
{
	for (int i = 0; i < 9; i++) for (int j = 0; j < 9; j++) help[i][j] = std::rand() % 10;
}

void outputData(short help[][9])
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++) std::cout << help[i][j] << '\t';
		std::cout << std::endl;

	}

	std::cout << std::endl;

}

void outputList(LevelNode* &start)
{
	LevelNode* tmp;
	for (tmp = start; tmp != nullptr; tmp = tmp->next) outputData(tmp->data);
}

void directConsoleInput(TableInfo &ja)
{
	short x, y, vrednost;
	std::cout << "Vnos v tabelo [X] [Y] [VREDNOST]" << std::endl;
	std::cin >> x >> y >> vrednost;
	std::cout << std::endl;
	LogicHandler::UpdateTable(ja, x, y, vrednost);



}