#include "levelObj.h"

levelObj::levelObj() : m_score(0), m_life(3)
{
}

bool levelObj::loadLevel(int numOfLevel)//load level from file
{
	char NAME_FILE[] = "board#.txt";
	NAME_FILE[5] = numOfLevel + '0';//change the text file number, every new load
									//each new level goes up in the number to the next 
	m_file.open(NAME_FILE, std::ios::in);

	if (!m_file.is_open())
		return false; //when there are no new levels file

	m_numOfCoins = 0; 
	m_file >> m_numOfSquares.x >> m_numOfSquares.y >> m_levelTime;
	char square;
	m_file.get(square);//skip first '\n'
	for (unsigned int i = 0; i < m_numOfSquares.y; ++i)
	{
		std::vector<char> Ctemp;
		for (unsigned int j = 0; j < m_numOfSquares.x; ++j)
		{
			m_file.get(square);
			if (square == '@')//player
			{
				Ctemp.push_back('@');
			}
			else if (square == '%')//enemy
			{
				Ctemp.push_back('%');
			}
			else if (square == '*')//coin
			{
				Ctemp.push_back('*');
				m_numOfCoins++;
			}
			else if (square == '#')//wall
			{
				Ctemp.push_back('#');
			}
			else if (square == 'H')//ladder
			{
				Ctemp.push_back('H');
			}
			else if (square == '-')//pole
			{
				Ctemp.push_back('-');
			}
			else if (square == '+')//present
			{
				Ctemp.push_back('+');
			}
			else
			{
				Ctemp.push_back(' ');
			}
		}
		m_level.push_back(Ctemp);
		m_file.get(square);//skip first '\n'
	}
	m_file.close();
	return true;
}//end loadLevel


int levelObj::getScore() const
{
	return m_score;
}//end getScore

int levelObj::getLife() const
{
	return m_life;
}//end getLife

int levelObj::getNumOfCoin() const
{
	return m_numOfCoins;
}//end getNumOfCoin

int levelObj::getLevelTime() const
{
	return m_levelTime;
}//end getLevelTime

void levelObj::setScore(int score)
{
	m_score = score;
}//end setScore

void levelObj::setLife(int life)
{
	m_life = life;
}//end setLife

void levelObj::clear()
{
	m_level.clear();
}//end clear

const sf::Vector2i& levelObj::getNumOfSquares() const
{
	return m_numOfSquares;
}//end getNumOfSquares

char levelObj::operator()(int row, int col) const
{
	return m_level[row][col];
}//end operator()
