#include "StateHandler.h"
#include "Game.h"
#include "TableInfo.h"
#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "LogicHandler.h"
#include "FileHandler.h"

StateHandler::Gameplay::Gameplay()
{
	gameComplete = false;
	quitTextTransparency = 0;
	quitCD = 3;
	Game::ConsoleText("[LOG] Ustvaril state objekt GAMEPLAY.", 'L');

}

StateHandler::Gameplay::~Gameplay()
{

	Game::ConsoleText("[LOG] Izbrisal state objekt GAMEPLAY.", 'L');

}

void StateHandler::Gameplay::drawTable(TableInfo instance, sf::RenderWindow& gameWindow)
{
	short tempDataStorage[9][9];
	instance.getData(tempDataStorage);

	// Adjust Textures To Match Data

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			IndividualSudokuCharacters[i][j].setTexture(&SudokuCharacterTextures[tempDataStorage[i][j]]);
			if (instance.primordialCheck[i][j] == true) IndividualSudokuCharacters[i][j].setFillColor(sf::Color::Red);
		}

	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++) gameWindow.draw(IndividualSudokuCharacters[i][j]);

	}

}

int StateHandler::Gameplay::DrawState(States& gameState, sf::RenderWindow& gameWindow, TableInfo& instance)
{
	instance.startofsolving = std::chrono::steady_clock::now();
	int loopX = 146;
	int loopY = 49;

	for (int i = 0; i < 10; i++)
	{
		SudokuCharacterTextures[i].loadFromFile("sudokuTexture" + std::to_string(i) + ".png");
	}

	// QUITTING TEXT

	if (!quittingFont.loadFromFile("cubecavern_memesbruh03.ttf"))
	{
		Game::ConsoleText("[ERR] Datoteka za pisavo ni bila najdena", 'E');
		return 101;
	}
	quittingText.setFont(quittingFont);
	quittingText.setCharacterSize(35);
	quittingText.setPosition(sf::Vector2f(10, 0));
	quittingText.setString("QUITTING");
	quittingText.setFillColor(sf::Color(255, 255, 255, 0));


	// SUDOKU CHARACTERS I.

	sf::IntRect IndividualSudokuCharacterHitbox[9][9];


	short temp[9][9];
	instance.getData(temp);


	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			IndividualSudokuCharacters[i][j].setSize(sf::Vector2f(57, 57));
			IndividualSudokuCharacters[i][j].setOrigin(sf::Vector2f(IndividualSudokuCharacters[i][j].getSize().x / 2, IndividualSudokuCharacters[i][j].getSize().y / 2));
			IndividualSudokuCharacters[i][j].setPosition(sf::Vector2f(loopX, loopY));
			IndividualSudokuCharacterHitbox[i][j].top = IndividualSudokuCharacters[i][j].getPosition().y - IndividualSudokuCharacters[i][j].getSize().y/2;
			IndividualSudokuCharacterHitbox[i][j].left = IndividualSudokuCharacters[i][j].getPosition().x - IndividualSudokuCharacters[i][j].getSize().x/2;
			IndividualSudokuCharacterHitbox[i][j].height = IndividualSudokuCharacters[i][j].getSize().y;
			IndividualSudokuCharacterHitbox[i][j].width = IndividualSudokuCharacters[i][j].getSize().x;
			if (temp[i][j] != 0) instance.primordialCheck[i][j] = true;
			if ((j+1) % 3 == 0 && j != 0) loopX = loopX + 161; else loopX = loopX + 12 + IndividualSudokuCharacters[i][j].getSize().x;
		}

		loopY = loopY + 2 + IndividualSudokuCharacters[i][i].getSize().y;
		loopX = 146;

	}

	// CHECK BUTTON I.

	if (!checkTexture.loadFromFile("checkTexture.png"))
	{
		Game::ConsoleText("[ERR] Datoteka CHECKTEXTURE ni bila najdena", 'E');
		return 101;
	}
	checkButton.setTexture(&checkTexture);
	checkButton.setSize(sf::Vector2f(180, 60));
	checkButton.setOrigin(sf::Vector2f(checkButton.getSize().x / 2, checkButton.getSize().y / 2));
	checkButton.setPosition(sf::Vector2f(994,450));
	checkButton.setRotation(90.f);
	sf::IntRect checkButtonArea(964,361,checkButton.getSize().y,checkButton.getSize().x);

	while (gameComplete != true)
	{
		sf::Event GamePlayEvent;
		while (gameWindow.pollEvent(GamePlayEvent))
		{
			switch (GamePlayEvent.type)
			{

				case sf::Event::Closed:
				{
				gameWindow.close();
				return 1;
				}

				case sf::Event::KeyPressed:
				{
					if (GamePlayEvent.key.code == sf::Keyboard::Escape)
					{
						quitHeld = true;
					}

					break;
				}

				case sf::Event::KeyReleased:
				{

					if (GamePlayEvent.key.code == sf::Keyboard::Escape)
					{
						quitHeld = false;
					}
					break;
				}

				case sf::Event::MouseButtonPressed:
				{
					if (GamePlayEvent.mouseButton.button == sf::Mouse::Button::Left)
					{
						short temp[9][9];
						instance.getData(temp);

						if (checkButtonArea.contains(sf::Mouse::getPosition(gameWindow)))
						{
							gameComplete = LogicHandler::SolveCheck(instance);
							if (gameComplete == true)
							{
								gameState = Complete;
								instance.endofsolving = std::chrono::steady_clock::now();
							}
							else goto end;

						}

						for (int i = 0; i < 9; i++)
						{
							for (int j = 0; j < 9; j++)
							{
								if (IndividualSudokuCharacterHitbox[i][j].contains(sf::Mouse::getPosition(gameWindow)) && instance.primordialCheck[i][j] != true)
								{
									if (temp[i][j] == 9) temp[i][j] = 1; else
									temp[i][j]++;
									instance = temp;
									instance.increaseClick();
									goto end;

								}

							}

						}
					}

					if (GamePlayEvent.mouseButton.button == sf::Mouse::Button::Right)
					{
						short temp[9][9];
						instance.getData(temp);

						for (int i = 0; i < 9; i++)
						{
							for (int j = 0; j < 9; j++)
							{
								if (IndividualSudokuCharacterHitbox[i][j].contains(sf::Mouse::getPosition(gameWindow)) && instance.primordialCheck[i][j] != true)
								{
									if (temp[i][j] == 1 || temp[i][j] == 0) temp[i][j] = 9; else
										temp[i][j]--;
									instance = temp;
									instance.increaseClick();
									goto end;

								}

							}

						}

					}

					end:
					break;
					
				}

			

				default: {}
			}
		}
		
		// LOGIC

		// QUIT TEXT

		if (quitHeld == true && quitTextTransparency < 255 && clock.getElapsedTime() > sf::milliseconds(7.85))
		{
			clock.restart();
			quitTextTransparency++;
		}
		else if (quitHeld == false && quitTextTransparency > 0) quitTextTransparency--;

		if (quitHeld == true && clock.getElapsedTime() > sf::milliseconds(7.85) && quitCD > 0)
		{
			quitCD--;
			clock.restart();
		}
		else if (quitHeld == false && clock.getElapsedTime() > sf::milliseconds(7.85)) quitCD = 3;

		if (quitCD == 0)
		{
			Game::ConsoleText("[LOG] Igralec je izklopil igro!", 'L');
			gameWindow.close();
			return 1;
		}

		quittingText.setFillColor(sf::Color(255, 255, 255, quitTextTransparency));


		gameWindow.clear(sf::Color::Black);
		drawTable(instance, gameWindow);
		gameWindow.draw(checkButton);
		gameWindow.draw(quittingText);
		gameWindow.display();

	}

	

	return 1;
}