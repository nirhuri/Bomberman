#pragma once
#include "StaticObjects.h"


class Door : public StaticObjects
{
public:
	Door(sf::Vector2i place); //builds the door
	~Door();
	void draw(sf::RenderWindow &window) override;
	virtual void collide(Objects* obj) override;
	virtual void collide(Robot* other) override;
	virtual void collide(Guards* other) override;
	virtual void collide(Bomb* other) override {};
	virtual void collide(Wall* other) override {};
	virtual void collide(Door* other) override {};
	virtual void collide(Rock* other) override {};
};