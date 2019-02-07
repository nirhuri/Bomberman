#include "Wall.h"
#include "RandomGuards.h"
#include "SmartGuards.h"


Wall::Wall(sf::Vector2i place)
{
	//build the wall
	m_place.x = (float)(place.x * SHAPE_SIZE + SHAPE_SIZE / 2);
	m_place.y = (float)(place.y * SHAPE_SIZE + SHAPE_SIZE / 2);
	sf::Texture *texture = PicsandSound::getInstance().getPic(2);
	m_sprite.setTexture(*texture);
	m_sprite.setOrigin(SHAPE_SIZE / 2, SHAPE_SIZE / 2);
	m_sprite.setPosition((sf::Vector2f)m_place);
}


Wall::~Wall()
{
}

void Wall::draw(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}

void Wall::collide(Objects * obj)
{
	obj->collide(this);
}

void Wall::collide(Robot * other)
{
	other->collide(this);
}

void Wall::collide(Guards * other)
{
	other->collide(this);
}


