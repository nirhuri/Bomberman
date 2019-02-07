#pragma once
#include "StaticObjects.h"



class Rock : public StaticObjects
{
public:
	Rock();
	Rock(bool isGift, sf::Vector2i place); // build the rock
	~Rock();
	//collide system
	void draw(sf::RenderWindow &window) override;
	virtual void collide(Objects* obj) override;
	virtual void collide(Robot* other) override;
	virtual void collide(Guards* other) override;
	virtual void collide(Bomb* other) override;
	virtual void collide(Wall* other) override {};
	virtual void collide(Door* other) override {};
	virtual void collide(Rock* other) override {};
	bool ifExploded(); //returns if rock has exploded
private:
	bool m_isGift; // is there a gift under the rock
	bool exploded = false;
};

