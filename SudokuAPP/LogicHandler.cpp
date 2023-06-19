#include "LogicHandler.h"
#include "TableInfo.h"
#include "Game.h"

bool LogicHandler::SolveCheck(TableInfo x)
{
	Game::ConsoleText("[LOG] Preverjam ce je trenutna tabela pravilna. . .", 'L');
	short sumcheck, temp[9][9];
	x.getData(temp);
	for (int i = 0; i < 9; i++) 
	{
		sumcheck = 0;
		for (int j = 0; j < 9; j++) sumcheck = sumcheck + temp[i][j];
		if (sumcheck != 45)
		{
			Game::ConsoleText("[LOG] Trenuta tabela ni pravilna | Napacno resena vrstica.", 'L');
			return false;
		}
	}

	for (int j = 0; j < 9; j++)
	{
		sumcheck = 0;
		for (int i = 0; i < 9; i++) sumcheck = sumcheck + temp[i][j];
		if (sumcheck != 45)
		{
			Game::ConsoleText("[LOG] Trenuta tabela ni pravilna | Napacno resen stolpec.", 'L');
			return false;
		}
	}

	sumcheck = 0;
	for (int i = 0; i < 9; i++) for (int j = 0; j < 9; j++) sumcheck = sumcheck + temp[i][j];
	if (sumcheck != 405)
	{
		Game::ConsoleText("[LOG] Trenutna tabela ni pravilna | Napacno resen kvadrat.", 'L');
		return false;
	}
	else
	{
		Game::ConsoleText("[LOG] Trenutna tabela je pravilna!", 'L');
		return true;
	}

	return false;
}


void LogicHandler::UpdateTable(TableInfo &current, short x, short y, short update)
{
	short temp[9][9];
	current.getData(temp);
	temp[y][x] = update;
	current = temp;
	Game::ConsoleText("[LOG] Vpisal novo vrednost v podatke objekta TableInfo.", 'L');

}