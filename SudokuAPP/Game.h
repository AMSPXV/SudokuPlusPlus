#pragma once
#include <string>
#include <fstream>

class Game
{
	public:
	static int ConsoleIntro(std::fstream& introfile);
	static void ConsoleText(std::string text, char type);
	static bool Run();
};

