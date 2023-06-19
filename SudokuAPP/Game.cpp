// HEADER 
#include "Game.h"
// STANDARD LIB.
#include <fstream>
#include <string>
#include <iostream>
// SPECIAL DEF
#define NOMINMAX
#include <Windows.h>


int Game::ConsoleIntro(std::fstream &introfile)
{
	if (introfile.is_open())
	{
		HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(color, 4);
		std::string temp;

		while (getline(introfile,temp))
		{
			std::cout << temp << std::endl;
		}

		SetConsoleTextAttribute(color, 15);

		std::cout << std::endl << std::endl;
		return 1;
	}

	else
	{
		ConsoleText("[ERR] Datoteka CONSOLEINTRO ni bila najdena!", 'E');
		return 101;
	}
}

void Game::ConsoleText(std::string text, char type)
{
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);

	switch(type)
	{
		case 'E':
			SetConsoleTextAttribute(color, 12);
			std::cout << text;
			break;
		case 'L':
			SetConsoleTextAttribute(color, 8);
			std::cout << text;
			break;
		case 'O':
			SetConsoleTextAttribute(color, 9);
			std::cout << text;
			break;
	}
	SetConsoleTextAttribute(color, 15);
	std::cout << std::endl;
}