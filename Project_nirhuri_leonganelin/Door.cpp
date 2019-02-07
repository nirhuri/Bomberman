#include "Door.h"
#include "Guards.h"
#include "Robot.h"

Door::Door(sf::Vector2i place)
{
	//builds the door
	m_place.x = (float)(place.x * SHAPE_SIZE + SHAPE_SIZE / 2);
	m_place.y = (float)(place.y * SHAPE_SIZE + SHAPE_SIZE / 2);
	sf::Texture *texture = PicsandSound::getInstance().getPic(7);
	m_sprite.setTexture(*texture);
	m_sprite.setOrigin(SHAPE_SIZE / 2, SHAPE_SIZE / 2);
	m_sprite.setPosition((sf::Vector2f)m_place);
}


Door::~Door()
{
}

void Door::draw(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}

void Door::collide(Objects * obj)
{
	obj->collide(this);
}

void Door::collide(Robot * other)
{
	other->collide(this);
}


void Door::collide(Guards * other)
{
	other->collide(this);
}


