#include "TableInfo.h"
#include "Game.h"
#include <string>
#include <chrono>


TableInfo::TableInfo()
{
	for (int i = 0; i < 9; i++) for (int j = 0; j < 9; j++) this->data[i][j] = 0;
	this->clicks = 0;
	Game::ConsoleText("[LOG] Inicializiran objekt TableInfo.", 'L');
}

TableInfo::~TableInfo()
{
}

int TableInfo::getClicks()
{
	Game::ConsoleText("[LOG] Izvedel branje vrednosti clicks iz objekta razreda TableInfo.", 'L');
	return clicks;
}

void TableInfo::operator=(short tab[][9])
{
	for (int i = 0; i < 9; i++) for (int j = 0; j < 9; j++) data[i][j] = tab[i][j];
}

void TableInfo::getData(short tab[][9])
{
	for (int i = 0; i < 9; i++) for (int j = 0; j < 9; j++) tab[i][j] = data[i][j];
}

void TableInfo::increaseClick()
{
	clicks++;
}