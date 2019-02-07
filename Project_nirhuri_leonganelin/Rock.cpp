#include "Rock.h"
#include "Robot.h"
#include "Guards.h"

Rock::Rock()
{
}

Rock::Rock(bool isGift, sf::Vector2i place) : m_isGift(isGift)
{
	//builds the rock location and picture
	m_place.x = (float)(place.x * SHAPE_SIZE + SHAPE_SIZE / 2);
	m_place.y = (float)(place.y * SHAPE_SIZE + SHAPE_SIZE / 2);
	sf::Texture *texture = PicsandSound::getInstance().getPic(1);
	m_sprite.setTexture(*texture);
	m_sprite.setOrigin(SHAPE_SIZE / 2, SHAPE_SIZE / 2);
	m_sprite.setPosition((sf::Vector2f)m_place);
}


Rock::~Rock()
{
}

void Rock::draw(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}

void Rock::collide(Objects * obj)
{
	obj->collide(this);
}

void Rock::collide(Robot * other)
{
	other->collide(this);
}

void Rock::collide(Guards * other)
{
	other->collide(this);
}


void Rock::collide(Bomb * other)
{
	exploded = true;
}

bool Rock::ifExploded()
{
	return exploded;
}
