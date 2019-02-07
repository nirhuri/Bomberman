#pragma once
#include "StaticObjects.h"


class Wall : public StaticObjects
{
public:
	Wall(sf::Vector2i place); //builds the wall
	~Wall();
	//collide system
	void draw(sf::RenderWindow &window) override;
	virtual void collide(Objects* obj) override;
	virtual void collide(Robot* other) override;
	virtual void collide(Guards* other)override;
	virtual void collide(Bomb* other) override {};
	virtual void collide(Wall* other) override {};
	virtual void collide(Door* other) override {};
	virtual void collide(Rock* other) override {};

};

