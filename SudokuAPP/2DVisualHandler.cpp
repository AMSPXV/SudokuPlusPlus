#include "2DVisualHandler.h"
#include <iostream>
#include "Game.h"
#include "TableInfo.h"
#define NOMINMAX
#include <Windows.h>

void TDVisualHandler::VisualizeTable(TableInfo x)
{
	HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);
	short data[9][9];
	x.getData(data);
	for (int i = 0; i < 9; i++)
	{
		SetConsoleTextAttribute(Color, 10);
		std::cout << '\t' << '\t' << '\t';
		for (int j = 0; j < 9; j++)
		{
			if (data[i][j] == 0) std::cout << "X" << '\t';
			else std::cout << data[i][j] << '\t';

		}
		std::cout << std::endl;

	}
	Game::ConsoleText("Uporabil 2DVisualHandler za izpis sudoku tabele.", 'O');
	SetConsoleTextAttribute(Color, 7);

}