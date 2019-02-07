#include "Robot.h"
#include "Bomb.h"

Robot::Robot()
{
	m_life = 3;
	m_startingPlace = m_place;
	sf::Texture *texture = PicsandSound::getInstance().getPic(0);
	m_sprite.setTexture(*texture);
	m_sprite.setOrigin(SHAPE_SIZE / 2, SHAPE_SIZE / 2);
	m_sprite.setTextureRect(sf::IntRect(static_t, 32 * 4, 30, 30));
	m_sprite.setPosition(m_place.x, m_place.y);
}

Robot::~Robot()
{
}

bool Robot::changeLvl()
{
	return nextLvl;
}

void Robot::setNextLvl()
{
	nextLvl = false;
}

//when robot dead or finished level:
void Robot::setStartPlace(sf::Vector2f place)
{
	m_startingPlace = place;
	m_place = place;
	m_life = 3;
	sf::Texture *texture = PicsandSound::getInstance().getPic(0);
	m_sprite.setTexture(*texture);
	m_sprite.setOrigin(SHAPE_SIZE / 2, SHAPE_SIZE / 2);
	m_sprite.setTextureRect(sf::IntRect(static_t, 32 * 4, 30, 30));
	m_sprite.setPosition(m_startingPlace.x, m_startingPlace.y);
}

//moving the robot (not part from polymorphisem):
void Robot::move(int step)
{
	m_prevPlace = m_place;
	changeStep(step);

	switch (m_direction)
	{
	case right_t: m_place.x += 4;
		setPic(1);
		break;
	case left_t:m_place.x -= 4;
		setPic(0);
		break;
	case up_t:m_place.y -= 4;
		setPic(3);
		break;
	case down_t:m_place.y += 4;
		setPic(2);
		break;
	}
	m_sprite.setTextureRect(sf::IntRect((m_step * 32), m_dirPic * 32, 30, 30));
	m_sprite.setPosition(m_place);

}

void Robot::draw(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}

void Robot::setRobotPlace(float x, float y)
{
	m_place = { x, y };
}

sf::Vector2f Robot::getRobotPlace()
{
	return m_place;
}

//double dispatch:
void Robot::collide(Objects * obj)
{
	obj->collide(this);
}

//collide with guards
void Robot::collide(Guards * other)
{
	m_life--;
	m_place = m_startingPlace;
}

//collide with bomb
void Robot::collide(Bomb * other)
{
	robotExploded = true;
	m_life--;
}

//collide with door
void Robot::collide(Door * other)
{
	nextLvl = true;
}

//collide with rock
void Robot::collide(Rock * other)
{
	if (m_sprite.getGlobalBounds().intersects(other->getCharFloatRect()))
		m_place = m_prevPlace;
}

//collide with wall
void Robot::collide(Wall * other)
{
	if (m_sprite.getGlobalBounds().intersects(other->getCharFloatRect()))
		m_place = m_prevPlace;
}

//taking the right pic from the sheets
void Robot::setPic(int direction)
{
	switch (direction)
	{
	case 0: m_dirPic = down_t;
		break;
	case 1: m_dirPic = left_t;
		break;
	case 2: m_dirPic = right_t;
		break;
	case 3: m_dirPic = up_t;
		break;
	case 4: m_dirPic = static_t;
		break;
	}
}

int Robot::getRobotLife()
{
	return m_life;
}

void Robot::decreaseRobotLife()
{
	m_life--;
}

void Robot::resetLocation()
{
	m_place = m_startingPlace;
	m_sprite.setPosition(m_place);
}

bool Robot::ifRobotExploded()
{
	return robotExploded;
}

void Robot::setRobotStatus(bool status)
{
	robotExploded = status;
}



void Robot::changeStep(int step)
{
	if (step == 0)
		m_step = 0;
	else
		m_step = 1;
}


