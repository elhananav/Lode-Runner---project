#include "board.h"
#include "controller.h"


board::board() : m_pushUpMsg(textures::instance().getFont()), m_tookPresent(false)
{
	srand(time(NULL));//for enemy movement
	m_clock.restart();
	m_pushUpMsg.setPosition(sf::Vector2f(400, 20));
	m_pushUpMsg.setCharacterSize(20);
	m_pushUpMsg.setColor(sf::Color::Yellow);
}//end board constructor

bool board::loadLevel(int numOfLevel)
{
	if (!m_level.loadLevel(numOfLevel))
		return false;
	m_levelCurrentTime = m_level.getLevelTime();

	m_size.x = (float)BOARDSIZE_X / (float)m_level.getNumOfSquares().x;
	m_size.y = (float)BOARDSIZE_Y / (float)m_level.getNumOfSquares().y;

	//so smartEnemies could get pointer to player
	m_moveable.push_back(std::make_unique<player>(createSprite(PLAYER, 0, 0), m_level.getScore(), m_level.getLife(), numOfLevel));

	char square;
	for (unsigned int i = 0; i < m_level.getNumOfSquares().y; ++i)
	{
		std::vector<std::unique_ptr<staticObj>> temp;
		for (unsigned int j = 0; j < m_level.getNumOfSquares().x; ++j)
		{
			square = m_level(i, j);
			if (square == '@')//player
			{
				m_moveable[PLAYER_PLACE]->setPosition(sf::Vector2f(j * m_size.x, i * m_size.y));
				temp.push_back(nullptr);
			}
			else if (square == '%')//enemy
			{
				m_moveable.push_back(createEnemy(i, j));
				temp.push_back(nullptr);
			}
			else if (square == '*')//coin
			{
				temp.push_back(std::make_unique<coin>(createSprite(COIN, i, j)));
			}
			else if (square == '#')//wall
			{
				temp.push_back(std::make_unique<wall>(createSprite(WALL, i, j)));
			}
			else if (square == 'H')//ladder
			{
				temp.push_back(std::make_unique<ladder>(createSprite(LADDER, i, j)));
			}
			else if (square == '-')//pole
			{
				temp.push_back(std::make_unique<pole>(createSprite(POLE, i, j)));
			}
			else if (square == '+')//present
			{
				temp.push_back(createPresent(i, j));
			}
			else//empty
			{
				temp.push_back(nullptr);
			}
		}
		m_static.push_back(std::move(temp));
	}
	return true;
}//end loadLevel

sf::Sprite board::createSprite(simbolIndex type, int row, int col)
{
	auto sprite = sf::Sprite(textures::instance().getTexture(type));
	if (type == PLAYER || type == ENEMY)//reduce player & enemy size
		sprite.setScale((m_size.x - 1.0f) / sprite.getLocalBounds().width,
						(m_size.y - 1.0f) / sprite.getLocalBounds().height);
	else
		sprite.setScale((m_size.x) / sprite.getLocalBounds().width,
						(m_size.y) / sprite.getLocalBounds().height);

	sprite.setPosition(col * m_size.x, row * m_size.y);
	return sprite;
}//end createSprite

void board::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < m_static.size(); ++i)//i = number of lines
		for (int j = 0; j < m_static[i].size(); ++j)//j = number of col
			if (m_static[i][j])//so it wouldn't try to print empty place 
				m_static[i][j]->draw(window);

	for (int i = 0; i < m_moveable.size(); ++i)
		m_moveable[i]->draw(window);
}//end draw

void board::move(const sf::Time& time)
{
	sf::Vector2i slotsIndex[2];
	for (int i = 0; i < m_moveable.size(); ++i)
	{
		if (m_moveable[i]->getInAHole())//if in a hole - block move
			continue;
		m_moveable[i]->move(time);
		if (i != PLAYER_PLACE)
		{//collision between player & enemies
			if (m_moveable[i]->collidesWith(*m_moveable[PLAYER_PLACE]))
				m_moveable[i]->handleCollision(*m_moveable[PLAYER_PLACE]);
		}

		getSlotslotsIndex(m_moveable[i]->getPosition(), m_moveable[i]->getDirection(), slotsIndex);

		//collision has occurred - not with empty place
		if (needToHandleCollision(slotsIndex[0], i))
			m_moveable[i]->handleCollision(*getStaticObj(slotsIndex[0]));

		//collision has occurred - not with empty place
		if (needToHandleCollision(slotsIndex[1], i))
			m_moveable[i]->handleCollision(*getStaticObj(slotsIndex[1]));

		getSlotslotsIndex(m_moveable[i]->getPosition(), sf::Vector2f(0, 1), slotsIndex);

		if (needToCheckFalldown(slotsIndex, i))
		{
			m_moveable[i]->moveFalldown(*this, time, i);
		}
	}
}//end move



bool board::slotsOutOfBounds(sf::Vector2i index) const
{
	if (index.y < 0 || index.y >= m_static[0].size() || index.x < 0 || index.x >= m_static.size())
		return true;
	return false;
}//end slotsOutOfBounds

void board::handlePresent(sf::Clock& clockPresent)
{//check if the player took present - if does, then implement the exact present 
	auto Player = dynamic_cast<player*>(m_moveable[PLAYER_PLACE].get());
	if (Player->getPresentKind() == nothing)
		return;
	switch (Player->getPresentKind())
	{
	case addEnemy:
		addEnemytoGame();
		m_tookPresent = true;
		m_presentType = addEnemy;
		break;
	case addTime:
		m_levelCurrentTime += 15;
		m_tookPresent = true;
		m_presentType = addTime;
		break;
	case addScore:
		Player->addScore(20);
		m_tookPresent = true;
		m_presentType = addScore;
		break;
	case addLife:
		Player->addLife(1);
		m_tookPresent = true;
		m_presentType = addLife;
		break;
	}
	Player->setPresentKind(nothing);
	clockPresent.restart();
}//end handlePresent

std::unique_ptr<staticObj> board::createPresent(int row, int col)
{
	int kind;
	(m_levelCurrentTime == -1) ? kind = rand() % 7 + 1 : kind = rand() % 7;//if no time limit - no addTime present
	switch (kind)
	{
	case addTime:
		return std::make_unique<timePresent>(createSprite(PRESENT, row, col));
	case addEnemy:
		return std::make_unique<badPresent>(createSprite(PRESENT, row, col));
	case addScore:
		return std::make_unique<scorePresent>(createSprite(PRESENT, row, col));
	case addLife:
		return std::make_unique<lifePresent>(createSprite(PRESENT, row, col));
	default://so most present will be additional score
		return std::make_unique<scorePresent>(createSprite(PRESENT, row, col));
	}
	return std::unique_ptr<staticObj>();//only for the compiler
}//end createPresent

std::unique_ptr<moveable> board::createEnemy(int row, int col)
{
	auto kind = rand() % 3;
	switch (kind)
	{
	case 0:
		return std::make_unique<randomEnemy>(createSprite(ENEMY, row, col));
	case 1:
		return std::make_unique<constEnemy>(createSprite(ENEMY, row, col), *this);
	case 2:
		return std::make_unique<smartEnemy>(createSprite(ENEMY, row, col), dynamic_cast<player*>(m_moveable[PLAYER_PLACE].get()));
	}
	return std::unique_ptr<moveable>();
}//end createEnemy

void board::addEnemytoGame()
{//add enemy to level(when player 'eat' enemyPresent)
	m_moveable.push_back(createEnemy(0, 0));
}//end addEnemytoGame

bool board::needToCheckFalldown(const sf::Vector2i index[], int i)
{//if beneath you there is: empty place/coin/present = true(keep falling)
	if (!getStaticObj(index[0]) && !getStaticObj(index[1]))
	{
		m_moveable[i]->setUpPossibale(false);
		return true;
	}
	if (m_moveable[i]->getNeedToFall())
		return true;
	return false;
}//end needToCheckFalldown

void board::getSlotslotsIndex(const sf::Vector2f& location, const sf::Vector2f& direction, sf::Vector2i* index) const
{//return the indexes of static objects in static vector - according to location and direction
	if (direction == sf::Vector2f(-1, 0))//direction = left
	{
		index[0] = sf::Vector2i((int)((location.y + 1.0f) / m_size.y), (int)((location.x + 1.0f) / m_size.x));//left up vertex
		index[1] = sf::Vector2i((int)((location.y + m_size.y - 1.0f) / m_size.y), (int)((location.x + 1.0f) / m_size.x));//left down vertex
	}
	else if (direction == sf::Vector2f(1, 0))//direction = right
	{
		index[0] = sf::Vector2i((int)((location.y + 1.0f) / m_size.y), (int)((location.x + m_size.x - 1.0f) / m_size.x));//right up vertex
		index[1] = sf::Vector2i((int)((location.y + m_size.y - 1.0f) / m_size.y), (int)((location.x + m_size.x - 1.0f) / m_size.x));//right down vertex
	}
	else if (direction == sf::Vector2f(0, 1) || direction == sf::Vector2f(0, -1))//direction = down/up
	{
		index[0] = sf::Vector2i((int)((location.y + m_size.y - 1.0f) / m_size.y), (int)((location.x + 1.0f) / m_size.x));//left down vertex
		index[1] = sf::Vector2i((int)((location.y + m_size.y - 1.0f) / m_size.y), (int)((location.x + m_size.x - 1.0f) / m_size.x));//right down vertex
	}
}//end getSlotslotsIndex

void board::levelEnded(int numOfLevel)
{
	m_level.setScore(getScore());
	int sum = m_level.getScore() + (numOfLevel * LEVELFINISH);
	m_level.setScore(sum);
	m_level.setLife(getLife());
	m_tookPresent = false;//to remove the present push message
	clearVectors();
}//end levelEnded

void board::clearVectors()
{
	m_moveable.clear();
	m_level.clear();
	m_static.clear();
}//end clearVectors

bool board::needToHandleCollision(const sf::Vector2i& index, int i) const
{
	return getStaticObj(index) && m_moveable[i]->collidesWith(*getStaticObj(index));
}//end needToHandleCollision

staticObj* board::getStaticObj(const sf::Vector2i& index) const
{
	if (index.x < 0 || index.x >= m_static.size() || index.y < 0 || index.y >= m_static[0].size())
	{
		std::cout << "vector is out of range\n";
		exit(EXIT_FAILURE);
	}
	return m_static[index.x][index.y].get();
}//end getStaticObj

const levelObj& board::getlevel() const
{
	return m_level;
}//end getlevel

int board::getScore() const
{
	auto Player = static_cast<player*>(m_moveable[PLAYER_PLACE].get());
	return Player->getScore();
}//end getScore

int board::getLife() const
{
	auto Player = static_cast<player*>(m_moveable[PLAYER_PLACE].get());
	return Player->getLife();
}//end getLife

int board::getLevelTime() const
{
	return  m_levelCurrentTime;
}//end getLevelTime

bool board::getIsPlayerDead() const
{//check if player dead - collide with enemy/time's up
	auto Player = static_cast<player*>(m_moveable[PLAYER_PLACE].get());
	if (Player->getIAmDead())
		return true;
	if (m_levelCurrentTime == 0)
	{
		Player->reduceLife();
		return true;
	}
	return false;
}//end getIsPlayerDead

void board::updateTime()
{
	if (m_clock.getElapsedTime().asSeconds() > 1)
	{
		m_clock.restart();
		m_levelCurrentTime -= 1;
	}
}//end updateTime

void board::pushUpMsg(sf::Clock& clockPresent, sf::RenderWindow& window)
{//display on screen the kind of present that taken
	std::string str;
	if (m_tookPresent)
	{
		//so the push-up will appear on screen for three seconds
		if (clockPresent.getElapsedTime().asSeconds() < 3)
		{
			if (m_presentType == addScore)
				str = "Good gift :    20 POINTS ADDED";
			else if (m_presentType == addTime)
				str = "Good gift :    15 SECENDS ADDED";
			else if (m_presentType == addEnemy)
				str = "Bad gift :    1   ENEMY ADDED";
			else if (m_presentType == addLife)
				str = "Good gift :    LIFE ADDED";
		}
		else
		{
			m_tookPresent = false;
			clockPresent.restart();
		}
		m_pushUpMsg.setText(str);
		m_pushUpMsg.draw(window);
	}
}//end pushUpMsg


void board::excavate(excavateSide side)
{
	dynamic_cast<player*>(m_moveable[PLAYER_PLACE].get())->excavate(side, *this);
}//end excavate

void board::bringBackExcavated()
{	//bring back the excavated walls(after 3 seconds)
	//set the location of the objects that in a hole to be one cell above the hole
	auto Player = dynamic_cast<player*>(m_moveable[PLAYER_PLACE].get());
	for (int i = 0; i < Player->getNumOfexcavateed(); ++i)
	{
		auto Wall = dynamic_cast<wall*>(getStaticObj(Player->getExcavatedWallIndex(i)));
		if (Wall->getTime().asSeconds() > 3)
		{
			if (Wall->getIsFull())
			{
				auto location = Wall->getPosition();
				location.y -= (m_size.y + 2.0f);
				m_moveable[Wall->getMovableIndex()]->setPosition(location);
				m_moveable[Wall->getMovableIndex()]->setInAHole(false);
				Wall->setIsFull(false);
			}
			Wall->setExistens(true);
		}
	}
}//end bringBackExcavated

void board::restartLevel(int numOfLevel)
{
	m_tookPresent = false;//to remove the present push message
	m_level.setScore(getScore());
	m_level.setLife(getLife());
	m_levelCurrentTime = m_level.getLevelTime();
	coin::setCoinCounter(m_level.getNumOfCoin());//restore the starting level num of coins
	m_moveable.clear();
	m_moveable.push_back(std::make_unique<player>(createSprite(PLAYER, 0, 0), m_level.getScore(), m_level.getLife(), numOfLevel));
	for (int i = 0; i < m_level.getNumOfSquares().y; ++i)
	{
		for (unsigned int j = 0; j < m_level.getNumOfSquares().x; ++j)
		{
			if (m_level(i, j) == '@')//player 
				m_moveable[PLAYER_PLACE]->setPosition(sf::Vector2f(j * m_size.x, i * m_size.y));
			else if (m_level(i, j) == '%')//enemy
				m_moveable.push_back(createEnemy(i, j));
		}
	}
	for (int i = 0; i < m_level.getNumOfSquares().y; ++i)
	{
		for (unsigned int j = 0; j < m_level.getNumOfSquares().x; ++j)
			if (m_static[i][j])
				m_static[i][j]->setExistens(true);
	}
}//end restartLevel

void board::resetGameData()
{
	m_level.setScore(0);
	m_level.setLife(3);
	coin::setCoinCounter(0);
}//end resetGameData
