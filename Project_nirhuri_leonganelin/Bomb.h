#pragma once
#include "DynamicObjects.h"
#include <vector>

class Bomb : public DynamicObjects
{
public:
	Bomb(sf::Vector2f location); //builds the bomb
	~Bomb();
	void draw(sf::RenderWindow &window) override;
	void move(sf::Vector2f position, int direction, int step);
	//collide system
	virtual void collide(Objects* obj) override;
	virtual void collide(Robot* other) override;
	virtual void collide(Guards* other)override;
	virtual void collide(Wall* other) override {};
	virtual void collide(Door* other) override {};
	virtual void collide(Bomb* other) override {};
	virtual void collide(Rock* other) override;
	bool decTimer(); // handles bomb time functionality
	sf::Vector2f getLocation();
	bool getFlag(); // is it exploded
	void setExplode(bool flag);


private:
	std::vector<sf::Vector2f> expLocs;
	sf::Sprite sprite;
	sf::Vector2f m_location;
	int timer;
	int animation = 1;
	int m_power = 1;
	sf::Clock clock;
	sf::Time elapsed = clock.restart();
	bool exploded = false;
};

