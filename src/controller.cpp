#include "controller.h"

controller::controller()
	:m_window(sf::VideoMode(1200, 800), "LODE_RUNNER", sf::Style::Titlebar | sf::Style::Close),
	m_textures(textures::instance()), m_menu(m_textures, m_textures.getFont()), m_gamestats(m_textures.getFont())
	, m_numOfLevel(1)
{
	m_background.setTexture(m_textures.getTexture(GAME_BACKGROUND));
	m_background.setScale((BOARDSIZE.x / m_background.getLocalBounds().width),
		(BOARDSIZE.y / m_background.getLocalBounds().height));
	m_background.setPosition(sf::Vector2f(0, 0));
}

void controller::run()
{
	sf::Sound bGSound(music::instance().getSoundbuffer());
	bGSound.setVolume(30);
	bGSound.play();
	bGSound.setLoop(true);
	runMenu();
	sf::Clock clockPresent;//for the time present push up message will appear on screen. 
	if (!m_board.loadLevel(m_numOfLevel))
		gameOver(Finish);
	waitUntilKeyPress();//the level start when key press

	while (m_window.isOpen())
	{
		m_window.clear();
		m_window.draw(m_background);
		m_board.draw(m_window);
		setGameStats();//score/life/time/level
		m_gamestats.draw(m_window);
		//when player take present message(kind of present) will appear on screen
		m_board.pushUpMsg(clockPresent, m_window);
		m_window.display();

		m_board.bringBackExcavated();
		m_board.move(m_clock.restart());
		m_board.handlePresent(clockPresent);
		m_board.updateTime();
		checkLevelFinish();

		//check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			// "close requested" event: close the window
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;
			case sf::Event::KeyPressed:
			{
				if (event.key.code == sf::Keyboard::Escape)
					m_window.close();
				//z key excavate on the left size
				else if (event.key.code == sf::Keyboard::Z)
					m_board.excavate(left);
				//x key excavate on the left size
				else if (event.key.code == sf::Keyboard::X)
					m_board.excavate(right);
			}
			}
		}
	}
}//end run

void controller::runMenu()//print menu,than wait player to choose play/exit
{
	while (m_window.isOpen())
	{
		m_window.clear();
		m_menu.draw(m_window);
		m_window.display();
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window.close();
			if (sf::Event::MouseMoved)
			{
				auto location = m_window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
				m_menu.handleMouse(location);
			}
			if (sf::Event::MouseButtonReleased)
			{
				auto location = m_window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
				auto answer = m_menu.whoIsPressed(location);
				if (answer == Play)
					return;
				if (answer == Exit)
					m_window.close();
			}
		}
	}
}//end runMenu

//check if the player 'eat' all coins in level, than he finish
bool controller::isLevelFinish() const
{
	if (coin::getCoinCounter() == 0)
		return true;
	return false;
}//end isLevelFinish

//set the current game stats(level, life, score, time)
void controller::setGameStats()
{
	if(m_board.getLevelTime() < 0)//when loading level with '-1' time, you get unlimited time
		m_gamestats.setstring("Time: Unlimited", -1, Time);
	else
		m_gamestats.setstring("Time: ", m_board.getLevelTime(), Time);
	//change time color to red when lower than 10 seconds
	if (m_board.getLevelTime() <= 10 && m_board.getLevelTime() >= 0)
		m_gamestats.changeColor(sf::Color::Red, Time);
	else
		m_gamestats.changeColor(sf::Color::White, Time);

	m_gamestats.setstring("Level: ", m_numOfLevel, level);
	m_gamestats.setstring("Score: ", m_board.getScore(), score);
	m_gamestats.setstring("Life: ", m_board.getLife(), life);
}//end setGameStats

void controller::setGameOverStats(gameStatus status)
{
	if (status)//player finish/won the game
	{
		m_menu.setstring("You won the game - great job:  ", GameOver);
		m_menu.setstring("You   finish   at   Level: ", Level, m_numOfLevel - 1);
	}
	else
	{
		m_menu.setstring("Unfortunately   you   didn't   succeed   to   win:  ", GameOver, m_numOfLevel);
		m_menu.setstring("You   finish   at   Level: ", Level, m_numOfLevel);
	}
	m_menu.setstring("Your   Score   is: ", Score, m_board.getlevel().getScore());

}//end setGameOverStats

//check if any keyboard key pressed
bool controller::isAnyKeyPressed() const
{
	for (int k = -1; k < sf::Keyboard::KeyCount; ++k)
	{
		if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(k)))
			return true;
	}
	return false;
}//end isAnyKeyPressed

void controller::checkLevelFinish()
{
	//when player 'dead' if left life, restart level. otherwise the game-over with strike(failed)
	if (m_board.getIsPlayerDead())
	{
		if (m_board.getLife() < 1)
			gameOver(Failed);
		m_board.restartLevel(m_numOfLevel);
		waitUntilKeyPress();
		return;
	}
	//if player 'eat' all coins, than the level end,
	//and check if there is a new level to load, or the game-over successfully
	if (isLevelFinish())
	{
		m_board.levelEnded(m_numOfLevel);//clear level data
		++m_numOfLevel;
		if (!m_board.loadLevel(m_numOfLevel))//try to load a new level, if failed the game is over successfully
		{
			gameOver(Finish);
			return;
		}
		else
			waitUntilKeyPress();
	}
}//end checkLevelFinish

void controller::waitUntilKeyPress()
{
	m_window.clear();
	m_window.draw(m_background);
	m_board.draw(m_window);
	setGameStats();
	m_gamestats.draw(m_window);
	m_window.display();
	while (!isAnyKeyPressed()) {};
	m_clock.restart();
}//end waitUntilKeyPress

void controller::gameOver(gameStatus status)
{
	setGameOverStats(status);//set the game-over stat to print of the game over menu
	if (!status)//if player loose the game
		m_board.levelEnded(m_numOfLevel);

	while (m_window.isOpen())
	{
		m_window.clear();
		m_menu.drawFinal(m_window);//draw game-over menu
		m_window.display();
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_window.close();
				exit(EXIT_SUCCESS);
			}
			if (sf::Event::MouseMoved)
			{
				auto location = m_window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
				m_menu.handleMouse(location);
			}
			if (sf::Event::MouseButtonReleased)
			{
				auto location = m_window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
				auto answer = m_menu.whoIsPressed(location);
				if (answer == Play)//if player want to start again the game from beginning
				{
					m_numOfLevel = 1; //starting level
					m_board.resetGameData(); //reset to new game the data(score, life)
					run();//start game again
				}
				if (answer == Exit)
				{
					m_window.close();
					exit(EXIT_SUCCESS);
				}
			}
		}
	}
}//end gameOver

