#pragma once
#include "Objects.h"



class DynamicObjects : public Objects
{
public:
	DynamicObjects();
	~DynamicObjects();
	//polymorphisem draw
	virtual void draw(sf::RenderWindow &win) = 0;
	void setDirection(direction_t dir);
	direction_t getDirection();

protected:
	int m_step;
	direction_t m_dirPic;
	direction_t m_direction;
};

