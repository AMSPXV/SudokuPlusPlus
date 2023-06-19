#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "TableInfo.h"
#include <ctime>
#include <chrono>

namespace StateHandler
{
	enum States
	{
		SplashScreen, MainMenu, GameSelect, Gameplay, Complete

	};

	class SplashScreen 
	{
		sf::RectangleShape whiteOverlay;
		sf::RectangleShape splashIcon;
		sf::Texture splashIconTexture;
		sf::Clock clock;
		bool firstFade;
		bool secondFade;

		public:
	
		SplashScreen();
		~SplashScreen();
		int DrawState(States &gameState,sf::RenderWindow &gameWindow);
	};

	class MainMenu 
	{
		sf::Clock clock;

		sf::RectangleShape overlay;

		// Play
		sf::RectangleShape playButton;
		sf::Texture playTexture;

		// Exit
		sf::RectangleShape exitButton;
		sf::Texture exitTexture;

		// Quitting
		sf::Font quittingFont;
		sf::Text quittingText;

		// Logo
		sf::RectangleShape logoShape;
		sf::Texture logoTexture;

		sf::RectangleShape background;

		bool transition, pendingPlay;

		public:
		
		MainMenu();
		~MainMenu();
		int DrawState(States& gameState, sf::RenderWindow& gameWindow);
	};

	class GameSelect 
	{
		sf::Clock clock;
		sf::Font sceneFont;

		// Quitting
		sf::Font quittingFont;
		sf::Text quittingText;

		// Difficulty Text
		sf::Text difficultyText;

		// Difficulty Select
		sf::Texture difficultySelectTextures;
		sf::RectangleShape difficultySelect;

		// Start Button
		sf::RectangleShape startButton;
		sf::Texture startButtonTexture;

		bool gameSelected, quitHeld;
		int difficulty, quitTextTransparency, quitCD;

		public:

		GameSelect();
		~GameSelect();

		int DrawState(States& gameState, sf::RenderWindow& gameWindow, std::string &gameDifficulty);
	};

	class Gameplay
	{

		// Quitting
		sf::Font quittingFont;
		sf::Text quittingText;

		// Sudoku

		sf::RectangleShape IndividualSudokuCharacters[9][9];
		sf::Texture SudokuCharacterTextures[10];
		
		// Background

		sf::RectangleShape background;
		sf::Texture backgroundTexture;

		// Check Button

		sf::RectangleShape checkButton;
		sf::Texture checkTexture;

		sf::Clock clock;

		bool gameComplete, animationsPlayed, quitHeld;
		int quitTextTransparency, quitCD;

		public:

		Gameplay();
		void drawTable(TableInfo instance, sf::RenderWindow& gameWindow);
		int DrawState(States& gameState, sf::RenderWindow& gameWindow, TableInfo& instance);
		~Gameplay();
	};

}