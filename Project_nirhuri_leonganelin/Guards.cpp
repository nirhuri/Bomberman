#include "Guards.h"
#include "Robot.h"
#include "Bomb.h"

Guards::Guards()
{

}


Guards::~Guards()
{
}

void Guards::draw(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}

void Guards::changeDir()
{
	int direction = rand() % 4;
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
		//case 4: m_dir = static_t;
			//break;
	}
}

void Guards::setStartingPlace()
{
	m_place = m_startingPlace;
}

sf::Vector2f Guards::getPrevPlace()
{
	return m_prevPlace;
}

void Guards::setAlive(bool flag)
{
	stillAlive = flag;
}

sf::Vector2f Guards::getLoc()
{
	return sf::Vector2f{ m_place.x / SHAPE_SIZE, m_place.y / SHAPE_SIZE };
}


void Guards::collide(Objects * obj)
{
	obj->collide(this);
}

void Guards::collide(Robot * other)
{
	other->collide(this);
}

void Guards::collide(Bomb * other)
{
		stillAlive = false;
		m_place = { 0,0 };
		m_sprite.setPosition(m_place);
}

void Guards::collide(Wall * other)
{
	if (m_sprite.getGlobalBounds().intersects(other->getCharFloatRect()))
	{
		changeDir();
		m_place = m_prevPlace;
	}
}

void Guards::collide(Door * other)
{
	if (m_sprite.getGlobalBounds().intersects(other->getCharFloatRect()))
	{
		changeDir();
		m_place = m_prevPlace;
	}
}

void Guards::collide(Rock * other)
{
	if (m_sprite.getGlobalBounds().intersects(other->getCharFloatRect()))
	{
		changeDir();
		m_place = m_prevPlace;
	}
}

bool Guards::isAlive()
{
	return stillAlive;
}

int Guards::getDirection()
{
	return m_dirPic;
}
