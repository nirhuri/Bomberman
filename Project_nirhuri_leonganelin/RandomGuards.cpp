#include "RandomGuards.h"


RandomGuards::RandomGuards(sf::Vector2f place)
{
	m_place.x = place.x;
	m_place.y = place.y;
	m_startingPlace = m_place;
	sf::Texture *texture = PicsandSound::getInstance().getPic(3);
	m_sprite.setTexture(*texture);
	m_sprite.setOrigin(SHAPE_SIZE / 2, SHAPE_SIZE / 2);
	m_sprite.setTextureRect(sf::IntRect(SHAPE_SIZE, 0, SHAPE_SIZE, SHAPE_SIZE));
	m_sprite.setPosition(m_place);
}


RandomGuards::~RandomGuards()
{
}

//the guard randoms a direction evry few second and goes until he collide or random new direction
void RandomGuards::move(int step, float &time, sf::Vector2f RobotPlace)
{

	m_prevPlace = m_place;

	m_timeToChangeDir += time;
	if (m_timeToChangeDir >= 2.f)
	{
		changeDir();
		m_timeToChangeDir = 0;
	}

	switch (m_dirPic)
	{
	case 0: m_place.y = m_place.y + 2;
		m_step = step;
		break;
	case 1: m_place.x = m_place.x - 2;
		m_step = step;
		break;
	case 2: m_place.x = m_place.x + 2;
		m_step = step;
		break;
	case 3: m_place.y = m_place.y - 2;
		m_step = step;
		break;
	case 4: break;
	}
	m_sprite.setTextureRect(sf::IntRect((m_step * 32), m_dirPic * 32, 32, 32));
	m_sprite.setPosition(m_place);
}

sf::Vector2f RandomGuards::getLocation()
{
	return m_place;
}

//print the new step if not collide:
void RandomGuards::setNextStep()
{
	m_sprite.setTextureRect(sf::IntRect(m_step * SHAPE_SIZE,
		m_dirPic * SHAPE_SIZE, SHAPE_SIZE, SHAPE_SIZE));
	m_sprite.setOrigin(SHAPE_SIZE / 2, SHAPE_SIZE / 2);
	m_sprite.setPosition(m_place);
}




