// HEADER //
#include "GameContainer.h"
// STANDARD LIB //
// LOCAL INCLUDES //
#include "Game.h"
#include "TableInfo.h"
#include "FileHandler.h"
#include "StateHandler.h"
//OTHER LIB
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

GameContainer::GameContainer()
{
	Game::ConsoleText("C++ SUDOKU ver.1", 'O');
}

GameContainer::~GameContainer()
{
	Game::ConsoleText("[LOG] Izbrisal objekt GameContainer.", 'L');
}


int GameContainer::Play()
{
	// STARTUP VARIABLES & OBJECTS
	
	int returnCode = 1;
	int selectedLevel = 1;
	LevelNode* globalStart = nullptr;
	std::fstream introFile, levelFile, saveFile;
	std::string gameDifficulty;
	TableInfo sudokuDataInstance;
	StateHandler::States gameState = StateHandler::States::SplashScreen;
	Game::ConsoleText("[LOG] Spremenil stanje igre v stanje SPLASHSCREEN.", 'L');

	// STARTUP

	introFile.open("ConsoleIntro.txt", std::ios::in);
	returnCode = Game::ConsoleIntro(introFile);
	levelFile.open("Levels.txt", std::ios::in);
	returnCode = FileHandler::CreateLevelList(globalStart,levelFile);
	sf::Image icon;
	icon.loadFromFile("windowIcon.png");
	sf::RenderWindow gameWindow(sf::VideoMode(1024, 576), "C++ Sudoku",sf::Style::Close);
	gameWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	Game::ConsoleText("[LOG] Ustvaril okno za grafiko.", 'L');

	// GAME LOOP
	
	while (gameWindow.isOpen())
	{
		switch (gameState)
		{
			case StateHandler::States::SplashScreen:
			{
				class StateHandler::SplashScreen splashScreen;
				returnCode = splashScreen.DrawState(gameState,gameWindow);
				if (returnCode != 1) return returnCode;
				break;
			}
			
			default:
			{
				return 1;
			}

			case StateHandler::States::MainMenu:
			{
				class StateHandler::MainMenu mainMenu;
				returnCode = mainMenu.DrawState(gameState,gameWindow);
				if (returnCode != 1) return returnCode;
				break;
			}
			
			case StateHandler::States::GameSelect:
			{
				class StateHandler::GameSelect gameSelect;
				returnCode = gameSelect.DrawState(gameState,gameWindow,gameDifficulty);
				if (returnCode != 1) return returnCode;
				break;
			}
			
			case StateHandler::States::Gameplay:
			{
				class StateHandler::Gameplay gameplay;
				FileHandler::WriteLevel(sudokuDataInstance, gameDifficulty, selectedLevel, globalStart);
				returnCode = gameplay.DrawState(gameState,gameWindow,sudokuDataInstance);
				break;
			}

			case StateHandler::States::Complete:
			{
				FileHandler::SaveScore(sudokuDataInstance, gameDifficulty);
				goto end;
			}
			
		};

	}
	
	end:

	FileHandler::ClearList(globalStart);
	introFile.close();
	levelFile.close();

	return returnCode;

}
