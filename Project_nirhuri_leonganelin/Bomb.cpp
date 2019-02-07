#include "Bomb.h"
#include "Robot.h"
#include "Guards.h"
#include "Rock.h"

Bomb::Bomb(sf::Vector2f location)
{
	sf::Texture *texture = PicsandSound::getInstance().getPic(5);
	m_sprite.setTexture(*texture);
	m_sprite.setPosition(location.x, location.y);
	m_sprite.setOrigin(SHAPE_SIZE / 2, SHAPE_SIZE / 2);
	timer = 6;
	m_sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	m_location.x = location.x;
	m_location.y = location.y;
	expLocs.resize(5);
	expLocs[0].x = location.x;
	expLocs[0].y = location.y;
	expLocs[1].x = location.x - SHAPE_SIZE;
	expLocs[1].y = location.y;
	expLocs[2].x = location.x + SHAPE_SIZE;
	expLocs[2].y = location.y;
	expLocs[3].x = location.x;
	expLocs[3].y = location.y + SHAPE_SIZE;
	expLocs[4].x = location.x;
	expLocs[4].y = location.y - SHAPE_SIZE;

}
Bomb::~Bomb()
{
}

void Bomb::draw(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}

void Bomb::move(sf::Vector2f position, int direction, int step)
{
}

bool Bomb::decTimer()
{
	elapsed = clock.getElapsedTime(); // get time

	if (timer <= 2) // bomb exploded
		exploded = true;

	if (timer <= 0) // delete the bomb
		return false;
	else if (exploded && elapsed.asSeconds() > 0.5) // create explosion
	{
		timer--;
		elapsed = clock.restart();
		sf::Texture *texture = PicsandSound::getInstance().getPic(13);
		m_sprite.setTexture(*texture);
		m_sprite.setTextureRect(sf::IntRect(0, 0, 90, 90));
		m_sprite.setPosition(m_sprite.getPosition().x - 32, m_sprite.getPosition().y - 32);
	}
	else if (!exploded && elapsed.asSeconds() > 0.5) // change bomb animation
	{
		timer--;
		elapsed = clock.restart();

		if (animation == 1)
		{
			m_sprite.setTextureRect(sf::IntRect(96, 0, 32, 32));
			animation--;
		}
		else
		{
			m_sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
			animation++;
		}
	}

	return true;
}

sf::Vector2f Bomb::getLocation()
{
	return m_location;
}

bool Bomb::getFlag()
{
	return exploded;
}

void Bomb::setExplode(bool flag)
{
	exploded = flag;
}

void Bomb::collide(Objects * obj)
{
	obj->collide(this);
}

void Bomb::collide(Robot * other)
{
	other->collide(this);
}

void Bomb::collide(Guards * other)
{
	other->collide(this);
}


void Bomb::collide(Rock * other)
{
	other->collide(this);
}



