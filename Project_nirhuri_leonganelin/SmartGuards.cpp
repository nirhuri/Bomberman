#include "SmartGuards.h"

SmartGuards::SmartGuards(sf::Vector2f place)
{
	m_place.x = place.x;
	m_place.y = place.y;
	m_startingPlace = m_place;
	sf::Texture *texture = PicsandSound::getInstance().getPic(3);
	m_sprite.setTexture(*texture);
	m_sprite.setTextureRect(sf::IntRect(SHAPE_SIZE, 0, SHAPE_SIZE, SHAPE_SIZE));
	m_sprite.setOrigin(SHAPE_SIZE / 2, SHAPE_SIZE / 2);
	m_sprite.setPosition(m_place);
}


SmartGuards::~SmartGuards()
{
}

//move with manhatten distance and if the robot is far from guards the 
//guards moves randomly untill the robot got in his raduis:
void SmartGuards::move(int step, float &time, sf::Vector2f RobotPlace)
{
	m_prevPlace = m_place;
	m_step = step;

	findPath(RobotPlace);

	m_sprite.setTextureRect(sf::IntRect((m_step * 32), m_dirPic * 32, 32, 32));
	m_sprite.setPosition(m_place);
}


sf::Vector2f SmartGuards::getLocation()
{
	return m_place;
}

void SmartGuards::setNextStep()
{
	m_sprite.setTextureRect(sf::IntRect(m_step * SHAPE_SIZE,
		m_dirPic * SHAPE_SIZE, SHAPE_SIZE, SHAPE_SIZE));
	m_sprite.setOrigin(SHAPE_SIZE / 2, SHAPE_SIZE / 2);
	m_sprite.setPosition(m_place);
}


void SmartGuards::findPath(sf::Vector2f robotPlace)
{
	timer++;

	if (timer > 5)
	{
		timer = 0;
		int temp = rand() % 2;

		if (temp == 0 || manhattan(robotPlace))
		{

			if (robotPlace.y < m_place.y)
				dir = 3;
			else if (robotPlace.x > m_place.x)
				dir = 0;
			else if (robotPlace.y > m_place.y)
				dir = 2;
			else if (robotPlace.x < m_place.x)
				dir = 1;
		}
		else
		{
			int temp2 = rand() % 4;
			if (temp2 == 0)
			{
				dir = 0;
			}
			else if (temp2 == 1)
			{
				dir = 1;
			}
			else if (temp2 == 2)
			{
				dir = 2;
			}
			else if (temp2 == 3)
			{
				dir = 3;
			}
		}
	}

	if (dir == 0)
	{
		m_place.x = m_place.x + 2;
		m_dirPic = right_t;
	}

	else if (dir == 1)
	{
		m_place.x = m_place.x - 2;
		m_dirPic = left_t;
	}
	else if (dir == 2)
	{
		m_place.y = m_place.y + 2;
		m_dirPic = down_t;
	}
	else if (dir == 3)
	{
		m_place.y = m_place.y - 2;
		m_dirPic = up_t;
	}

}

bool SmartGuards::manhattan(sf::Vector2f robotPlace)
{
	int m1, m2;

	m1 = abs(m_place.x - robotPlace.x);
	m2 = abs(m_place.y - robotPlace.y);

	int m3 = sqrt(pow(m1, 2) + pow(m2, 2));

	if (m3 < 200)
	{
		return true;
	}

	return false;
}