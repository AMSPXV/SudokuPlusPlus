#include "FileHandler.h"
#include <string>
#include <chrono>
#include "Game.h"
#include <fstream>
#include <iostream>

void FileHandler::PushList(LevelNode* &start, short tab[][9], std::string inputdiff, short inum)
{
	LevelNode* temp = new LevelNode;
	for (int i = 0; i < 9; i++) for (int j = 0; j < 9; j++) temp->data[i][j] = tab[i][j];
	temp->dific = inputdiff;
	temp->num = inum;

	if (start == nullptr)
	{
		start = temp;
		temp->next = nullptr;
	}
	else
	{
		temp->next = start;
		start = temp;
	}
	Game::ConsoleText("[LOG] Dodan je bil element seznamu.", 'L');

}

bool FileHandler::PopList(LevelNode* &start)
{
	LevelNode* deletep;
	if (start != nullptr)
	{
		deletep = start;
		start = deletep->next;
		delete deletep;
		Game::ConsoleText("[LOG] Izbrisan je bil element seznama.", 'L');
		return true;
	}
	else return false;
}

int FileHandler::CreateLevelList(LevelNode *&start, std::fstream& levelfile)
{
	LevelNode temp;

	if (levelfile.is_open())
	{
		while (levelfile.eof() == false)
		{
			levelfile >> temp.dific;
			levelfile >> temp.num;
			for (int i = 0; i < 9; i++) for (int j=0;j<9;j++) levelfile >> temp.data[i][j];
			PushList(start, temp.data, temp.dific, temp.num);

		}

		Game::ConsoleText("[LOG] Ustvarjen je bil seznam nivojev.", 'L');
		return true;

	}
	else Game::ConsoleText("[ERR] Datoteka LEVELFILE ni bila najdena", 'E');
	
	return 101;

}

void FileHandler::ClearList(LevelNode*& start)
{
	if (PopList(start)) return ClearList(start);
	else
	{
		Game::ConsoleText("[LOG] Izbrisan je bil seznam nivojev.", 'L');
		return;

	}
}

int FileHandler::WriteLevel(TableInfo &x, std::string diff, short levelnum, LevelNode*& start)
{
	LevelNode* temp;
	temp = start;
	while (!(temp->num == levelnum && temp->dific == diff))
	{
		temp = temp->next;
		if (temp == nullptr)
		{
			Game::ConsoleText("[ERR] Nisem uspel najti nivoja v seznamu.", 'E');
			return 102;
		}

	}
	x = temp->data;
	return 1;
}

void FileHandler::SaveScore(TableInfo& x, std::string diff)
{
	std::fstream saveFile;
	saveFile.open("SavedPlays.txt", std::ios::out);

		if (saveFile.is_open())
		{
			saveFile << "SHRANJENA IGRA +";
			saveFile << " CAS REŠEVANJA - " << std::chrono::duration_cast<std::chrono::seconds> (x.endofsolving - x.startofsolving).count();
			saveFile << " + STEVILO KLIKOV - " << x.getClicks();
			saveFile << " + TEŽAVNOST - " << diff;
			saveFile << std::endl;
		}
	saveFile.close();
}