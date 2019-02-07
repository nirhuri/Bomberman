#pragma once
#include "Objects.h"



class StaticObjects : public Objects
{
public:
	StaticObjects();
	virtual void draw(sf::RenderWindow &win) = 0;
	~StaticObjects();
protected:
	int temp = 0;
};

