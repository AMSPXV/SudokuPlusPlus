#include "StateHandler.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

StateHandler::SplashScreen::SplashScreen()
{
	Game::ConsoleText("[LOG] Ustvaril state objekt SPLASHSCREEN.", 'L');
}

StateHandler::SplashScreen::~SplashScreen()
{
	Game::ConsoleText("[LOG] Izbrisal state objekt SPLASHSCREEN.", 'L');
}

int StateHandler::SplashScreen::DrawState(States& gameState, sf::RenderWindow& gameWindow)
{
	firstFade = false;
	secondFade = false;
	whiteOverlay.setPosition(sf::Vector2f(0, 0));
	whiteOverlay.setFillColor(sf::Color(255, 255, 255, 255));
	whiteOverlay.setSize(sf::Vector2f(1024, 576));
	if (!splashIconTexture.loadFromFile("splashScreen.png"))
	{
		Game::ConsoleText("[ERR] Datoteka SPLASHSCREEN ni bila najdena", 'E');
		return 101;
	}
	splashIcon.setSize(sf::Vector2f(1024, 576));
	splashIcon.setPosition(sf::Vector2f(0, 0));
	splashIcon.setTexture(&splashIconTexture);

	// SOUND

	sf::SoundBuffer splashBuffer;
	if (!splashBuffer.loadFromFile("bleepreverb.wav"))
	{
		Game::ConsoleText("[ERR] Datoteka REVERBBLEEP ni bila najdena", 'E');
		return 101;
	}

	int i = 255;
	int count = 5;
	bool soundPlayed = false;

	sf::Sound splashBeep;
	splashBeep.setBuffer(splashBuffer);

	while (firstFade != true)
	{
		sf::Event SplashScreenEvent;
		while (gameWindow.pollEvent(SplashScreenEvent))
		{
			if (SplashScreenEvent.type == sf::Event::Closed)
			{
				gameWindow.close();
				return 1;

			}
		}

		if (clock.getElapsedTime() > sf::seconds(1) && count > 0 && i != 0)
		{
			count--;
			clock.restart();
		}


		if (clock.getElapsedTime() > sf::seconds(0.001) && i > 0 && count == 0) 
		{

			i--;
			if (soundPlayed == false)
			{
				splashBeep.play();
				soundPlayed = true;
			}
			whiteOverlay.setFillColor(sf::Color(255, 255, 255, i));
			clock.restart();
		}

		if (count < 5 && i == 0 && clock.getElapsedTime() > sf::seconds(1))
		{
			count++;
			clock.restart();

		}
		
		if (i == 0 && count == 5) firstFade = true;

		gameWindow.clear(sf::Color::Black);
		gameWindow.draw(splashIcon);
		gameWindow.draw(whiteOverlay);
		gameWindow.display();

	}

	int secondCount = 5;

	while (secondFade != true)
	{
		sf::Event SplashScreenEvent;
		while (gameWindow.pollEvent(SplashScreenEvent))
		{
			if (SplashScreenEvent.type == sf::Event::Closed)
			{
				gameWindow.close();
				return 1;
			}
		}

		if (clock.getElapsedTime() > sf::seconds(0.001) && i < 255)
		{
			i++;
			whiteOverlay.setFillColor(sf::Color(255, 255, 255, i));
			clock.restart();
		}

		if (i == 255 && count < 5 && clock.getElapsedTime() > sf::seconds(1))
		{
			count++;
			clock.restart();
		}

		if (i == 255 && count == 5 && clock.getElapsedTime() > sf::seconds(1) && secondCount > 0)
		{
			secondCount--;
			clock.restart();
		}

		if (i == 255 && count == 5 && secondCount == 0) secondFade = true;

		gameWindow.clear(sf::Color::Black);
		gameWindow.draw(splashIcon);
		gameWindow.draw(whiteOverlay);
		gameWindow.display();
	}

	if (firstFade == true && secondFade == true)
	{
		gameState = MainMenu;
		Game::ConsoleText("[LOG] Spremenil stanje igre v stanje MAINMENU.", 'L');
	}

	return 1;
}

StateHandler::MainMenu::MainMenu()
{
	Game::ConsoleText("[LOG] Ustvaril state objekt MAINMENU.", 'L');
}

StateHandler::MainMenu::~MainMenu()
{
	Game::ConsoleText("[LOG] Izbrisal state objekt MAINMENU.", 'L');
}

int StateHandler::MainMenu::DrawState(States& gameState, sf::RenderWindow& gameWindow)
{
	transition = false;
	pendingPlay = false;
	int i = 0;
	

	// Clear & transition from previous state
	overlay.setPosition(sf::Vector2f(0, 0));
	overlay.setSize(sf::Vector2f(1024, 576));
	overlay.setFillColor(sf::Color(255, 255, 255, 255));

	while (transition != true)
	{
		sf::Event MainMenuTransitionEvent;
		while (gameWindow.pollEvent(MainMenuTransitionEvent))
		{
			if (MainMenuTransitionEvent.type == sf::Event::Closed)
			{
				gameWindow.close();
				return 1;
			}
		}

		if (clock.getElapsedTime() > sf::milliseconds(11.76) && i < 255)
		{
			i++;
			overlay.setFillColor(sf::Color((255 - i), (255 - i), (255 - i), 255));
			clock.restart();
		}

		if (i == 255)
		{
			gameState = GameSelect;
			transition = true;
		}

		gameWindow.clear(sf::Color::Black);
		gameWindow.draw(overlay);
		gameWindow.display();

	}
	
	// Generate elements of state
	// Variables
	int logoTransparency = 0;
	int playButtonTransparency = 0;
	int playButtonSizeX = 0;
	int playButtonSizeY = 0;
	int playButtonSizeAdd = 0;
	int quitTextTransparency = 0;
	int exitButtonTransparency = 0;
	int exitButtonSizeAdd = 0;
	int exitButtonSizeX = 0;
	int exitButtonSizeY = 0;
	int quitCD = 3;
	bool quitHeld = false;

	// MAIN LOGO I.

	if (!logoTexture.loadFromFile("mainMenuLogo.png"))
	{
		Game::ConsoleText("[ERR] Datoteka MAINMENULOGO ni bila najdena", 'E');
		return 101;
	}

	logoShape.setSize(sf::Vector2f(570, 170));
	logoShape.setOrigin(sf::Vector2f(285, 85));
	logoShape.setTexture(&logoTexture);
	logoShape.setPosition(sf::Vector2f(512, 180));

	// PLAY BUTTON I.

	if (!playTexture.loadFromFile("playButtonTexture.png"))
	{
		Game::ConsoleText("[ERR] Datoteka PLAYBUTTONTEXTURE ni bila najdena", 'E');
		return 101;
	}
	playTexture.setSmooth(true);
	playButton.setTexture(&playTexture);
	playButton.setSize(sf::Vector2f(300, 70));
	playButton.setPosition(sf::Vector2f(512, 340));
	playButtonSizeX = playButton.getSize().x;
	playButtonSizeY = playButton.getSize().y;
	playButton.setOrigin(sf::Vector2f(playButtonSizeX / 2, playButtonSizeY / 2));
	sf::IntRect playButtonArea(362, 305, playButtonSizeX, playButtonSizeY);

	// EXIT BUTTON I.

	if (!exitTexture.loadFromFile("exitTexture.png"))
	{
		Game::ConsoleText("[ERR] Datoteka PLAYBUTTONTEXTURE ni bila najdena", 'E');
		return 101;
	}
	exitTexture.setSmooth(true);
	exitButton.setTexture(&exitTexture);
	exitButton.setSize(sf::Vector2f(170, 50));
	exitButton.setPosition(sf::Vector2f(512, 425));
	sf::IntRect exitArea(427, 400, 170, 50);
	exitButtonSizeX = exitButton.getSize().x;
	exitButtonSizeY = exitButton.getSize().y;
	exitButton.setOrigin(sf::Vector2f(exitButtonSizeX/2, exitButtonSizeY/2));

	// Quitting Text
	if (!quittingFont.loadFromFile("cubecavern_memesbruh03.ttf"))
	{
		Game::ConsoleText("[ERR] Datoteka za pisavo ni bila najdena", 'E');
		return 101;
	}
	quittingText.setFont(quittingFont);
	quittingText.setCharacterSize(35);
	quittingText.setPosition(sf::Vector2f(10,0));
	quittingText.setString("QUITTING");
	quittingText.setFillColor(sf::Color(255,255,255,255));

	while (pendingPlay != true)
	{
		// LOGIC CHECK

		sf::Event MainMenuEvents;
		while (gameWindow.pollEvent(MainMenuEvents))
		{
			switch (MainMenuEvents.type) {

			case sf::Event::Closed:
				{
					gameWindow.close();
					return 1;
				}

			case sf::Event::KeyPressed: 
				{
					if (MainMenuEvents.key.code == sf::Keyboard::Escape)
					{
						quitHeld = true;
					}

					break;
				}

			case sf::Event::KeyReleased:
				{
				
					if (MainMenuEvents.key.code == sf::Keyboard::Escape)
					{ 
						quitHeld = false;
					}

				}

			case sf::Event::MouseButtonPressed:
				{
					switch (MainMenuEvents.mouseButton.button)
					{
						
						case sf::Mouse::Button::Left:
						{
							if (exitArea.contains(sf::Mouse::getPosition(gameWindow)))
							{
								Game::ConsoleText("[LOG] Igralec je izklopil igro!", 'L');
								gameWindow.close();
								return 1;
							}

							if (playButtonArea.contains(sf::Mouse::getPosition(gameWindow)) && playButtonTransparency == 255 && exitButtonTransparency == 255)
							{
								Game::ConsoleText("[LOG] Spremenil stanje igre v stanje GAMESELECT.", 'L');
								gameState = GameSelect;
								pendingPlay = true;
							}

						}


					}

			
				
				}

			default:{}

			}


		}

		// LOGIC

		// LOGO
		
		if (clock.getElapsedTime() > sf::milliseconds(7.84) && logoTransparency < 255)
		{
			logoTransparency++;
			clock.restart();
		}
		logoShape.setFillColor(sf::Color(255, 255, 255, logoTransparency));

		// QUIT TEXT
		
		if (quitHeld == true && quitTextTransparency < 255 && clock.getElapsedTime() > sf::milliseconds(7.85))
		{
			clock.restart();
			quitTextTransparency++;
		}
		else if (quitHeld == false && quitTextTransparency > 0) quitTextTransparency--;
		quittingText.setFillColor(sf::Color(255, 255, 255, quitTextTransparency));

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

		// PLAY BUTTON

		if (logoTransparency == 255 && playButtonTransparency < 255 && clock.getElapsedTime() > sf::milliseconds(7.84))
		{
			clock.restart();
			playButtonTransparency++;
		}

		if (playButtonArea.contains(sf::Mouse::getPosition(gameWindow)) && playButtonSizeAdd < 20 && clock.getElapsedTime() > sf::milliseconds(8) && playButtonTransparency == 255)
		{
			clock.restart();
			playButtonSizeAdd++;
		}
		else if (!playButtonArea.contains(sf::Mouse::getPosition(gameWindow)) && playButtonSizeAdd > 0 && clock.getElapsedTime() > sf::milliseconds(8))
		{
			clock.restart();
			playButtonSizeAdd--;
		}

		// SOUND



		playButton.setFillColor(sf::Color(255, 255, 255, playButtonTransparency));
		playButton.setSize(sf::Vector2f(playButtonSizeX + (playButtonSizeX * 0.01 * playButtonSizeAdd), playButtonSizeY + (playButtonSizeY * 0.01 * playButtonSizeAdd)));
		playButton.setOrigin(sf::Vector2f(playButton.getSize().x / 2, playButton.getSize().y / 2));


		// EXIT BUTTON

		if (exitButtonTransparency < 255 && playButtonTransparency == 255 && clock.getElapsedTime() > sf::milliseconds(7.84))
		{
			clock.restart();
			exitButtonTransparency++;
		}

		if (exitArea.contains(sf::Mouse::getPosition(gameWindow)) && exitButtonSizeAdd < 20 && clock.getElapsedTime() > sf::milliseconds(8) && exitButtonTransparency == 255)
		{
			clock.restart();
			exitButtonSizeAdd++;

		}
		else if (!exitArea.contains(sf::Mouse::getPosition(gameWindow)) && exitButtonSizeAdd > 0 && clock.getElapsedTime() > sf::milliseconds(8))
		{
			clock.restart();
			exitButtonSizeAdd--;
		}

		exitButton.setFillColor(sf::Color(255, 255, 255, exitButtonTransparency));
		exitButton.setSize(sf::Vector2f(exitButtonSizeX + (exitButtonSizeX*0.01*exitButtonSizeAdd), exitButtonSizeY + (exitButtonSizeY * 0.01 * exitButtonSizeAdd)));
		exitButton.setOrigin(sf::Vector2f(exitButton.getSize().x / 2, exitButton.getSize().y / 2));

		// DRAWING


		gameWindow.clear(sf::Color::Black);
		gameWindow.draw(logoShape);
		gameWindow.draw(playButton);
		gameWindow.draw(exitButton);
		gameWindow.draw(quittingText);
		gameWindow.display();

	}


	return 1;
}

StateHandler::GameSelect::GameSelect()
{
	gameSelected = false;
	quitTextTransparency = 0;
	quitCD = 3;
	difficulty = 0;
	Game::ConsoleText("[LOG] Ustvaril state objekt GAMESELECT.", 'L');
}

StateHandler::GameSelect::~GameSelect()
{
	Game::ConsoleText("[LOG] Izbrisal state objekt GAMESELECT.", 'L');
}

int StateHandler::GameSelect::DrawState(States& gameState, sf::RenderWindow& gameWindow, std::string &gameDifficulty)
{
	int startButtonSizeX = 0;
	int startButtonSizeY = 0;
	int startButtonSizeAdd = 0;

	// GRAPHICAL ELEMENT INITIALIZATION
	
	// SCENE FONT I.

	if (!sceneFont.loadFromFile("cubecavern_memesbruh03.ttf"))
	{
		Game::ConsoleText("[ERR] Datoteka za pisavo ni bila najdena", 'E');
		return 101;
	}

	// QUIT TEXT I.

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

	// DIFFICULTY TEXT I.

	difficultyText.setFont(sceneFont);
	difficultyText.setCharacterSize(60);
	difficultyText.setString("DIFFICULTY:");
	difficultyText.setFillColor(sf::Color(255,255,255,255));
	difficultyText.setOrigin(sf::Vector2f(difficultyText.getGlobalBounds().width / 2, difficultyText.getGlobalBounds().height / 2));
	difficultyText.setPosition(sf::Vector2f(gameWindow.getSize().x/8*3, (gameWindow.getSize().y/3)*2));
	
	// DIFFICULTY SELECT I.
	difficultySelectTextures.loadFromFile("difficultyTexture.png");
	difficultySelectTextures.setSmooth(true);
	difficultySelect.setSize(sf::Vector2f(160, 160));
	difficultySelect.setOrigin(sf::Vector2f(difficultySelect.getSize().x/2,difficultySelect.getSize().y/2));
	difficultySelect.setPosition(sf::Vector2f(gameWindow.getSize().x/8*5.5,gameWindow.getSize().y/3*2));
	difficultySelect.setFillColor(sf::Color::Green);
	sf::IntRect difficultySelectArea(difficultySelect.getPosition().x-difficultySelect.getSize().x / 2,difficultySelect.getPosition().y-difficultySelect.getSize().y/2, difficultySelect.getSize().x, difficultySelect.getSize().y);

	// START BUTTON I.
	if (!startButtonTexture.loadFromFile("startGameSelect.png"))
	{
		Game::ConsoleText("[ERR] Datoteka STARTBUTTONTEXTURE ni bila najdena", 'E');
		return 101;
	}
	startButton.setSize(sf::Vector2f(420, 140));
	startButton.setTexture(&startButtonTexture);
	startButton.setOrigin(startButton.getSize().x / 2, startButton.getSize().y / 2);
	startButton.setPosition(sf::Vector2f(gameWindow.getSize().x / 2, gameWindow.getSize().y / 3.5));
	sf::IntRect startButtonArea(startButton.getPosition().x-startButton.getSize().x/2,startButton.getPosition().y-startButton.getSize().y/2,startButton.getSize().x,startButton.getSize().y);
	startButtonSizeX = startButton.getSize().x;
	startButtonSizeY = startButton.getSize().y;

	// GAME LOOP
	int red, green, blue = 0;

	while (gameSelected == false)
	{
		sf::Event GameSelectEvent;
		while (gameWindow.pollEvent(GameSelectEvent))
		{
			switch (GameSelectEvent.type) 
			{

				case sf::Event::Closed:
				{
					gameWindow.close();
					return 1;
				}

				case sf::Event::KeyPressed:
				{
					if (GameSelectEvent.key.code == sf::Keyboard::Escape)
					{
						quitHeld = true;
					}

					break;
				}

				case sf::Event::KeyReleased:
				{

					if (GameSelectEvent.key.code == sf::Keyboard::Escape)
					{
						quitHeld = false;
					}
					break;
				}

				case sf::Event::MouseButtonPressed:
				{
					switch (GameSelectEvent.mouseButton.button)
					{

						case sf::Mouse::Button::Left:
						{
							if (difficultySelectArea.contains(sf::Mouse::getPosition(gameWindow)))
							{


								Game::ConsoleText("[LOG] Tezavnost igre je bila spremenjena.", 'L');
								if (difficulty == 2) difficulty = 0; else difficulty++;

								switch (difficulty)
								{
									case 0:
									{
									difficultySelect.setFillColor(sf::Color::Green);
									break;
									}

									case 1:

									{

									difficultySelect.setFillColor(sf::Color::Yellow);
									break;

									}

									case 2:

									{

									difficultySelect.setFillColor(sf::Color::Red);
									break;

									}

								}

							}

							if (startButtonArea.contains(sf::Mouse::getPosition(gameWindow)))
							{
								Game::ConsoleText("[LOG] Spremenil stanje igre v stanje GAMEPLAY.", 'L');
								gameState = Gameplay;
								gameSelected = true;
								switch (difficulty)
								{
									case 0:
									{
									gameDifficulty = "EASY";
									break;
									}

									case 1:
									{
									gameDifficulty = "MEDIUM";
									break;
									}

									case 2:
									{
									gameDifficulty = "HARD";
									break;
									}

								}

							}
						}


					}



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
		
		// BEGIN BUTTON

		if (startButtonArea.contains(sf::Mouse::getPosition(gameWindow)) && startButtonSizeAdd < 20 && clock.getElapsedTime() > sf::milliseconds(8))
		{
			clock.restart();
			startButtonSizeAdd++;
		}
		else if (!startButtonArea.contains(sf::Mouse::getPosition(gameWindow)) && startButtonSizeAdd > 0 && clock.getElapsedTime() > sf::milliseconds(8))
		{
			clock.restart();
			startButtonSizeAdd--;
		}
		startButton.setSize(sf::Vector2f(startButtonSizeX + (startButtonSizeX * 0.01 * startButtonSizeAdd), startButtonSizeY + (startButtonSizeY * 0.01 * startButtonSizeAdd)));
		startButton.setOrigin(sf::Vector2f(startButton.getSize().x / 2, startButton.getSize().y / 2));

		// DIFFICULTY

		difficultySelect.setTexture(&difficultySelectTextures);

		// DRAWING

		gameWindow.clear(sf::Color::Black);
		gameWindow.draw(quittingText);
		gameWindow.draw(difficultyText);
		gameWindow.draw(difficultySelect);
		gameWindow.draw(startButton);
		gameWindow.display();

	}


}