#include "Objects.h"



Objects::Objects()
{
}


Objects::~Objects()
{
}

sf::FloatRect Objects::getCharFloatRect()
{
	return m_sprite.getGlobalBounds();
}

sf::Vector2f Objects::getPlace()
{
	return m_place;
}
