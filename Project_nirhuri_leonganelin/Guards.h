#pragma once
#include "DynamicObjects.h"
#include <memory>	

class Guards : public DynamicObjects
{
public:
	Guards();
	~Guards();
	//polymorphisem move and collide with double sidpatch:
	virtual void move(int step, float &time, sf::Vector2f RobotPlace) = 0;
	virtual sf::Vector2f getLocation() = 0;
	virtual void draw(sf::RenderWindow &window);
	void collide(Objects* obj);
	virtual void collide(Robot* other);
	virtual void collide(Bomb* other);
	virtual void collide(Guards* other) {};
	virtual void collide(Wall* other);
	virtual void collide(Door* other);
	virtual void collide(Rock* other);
	//check for guards life, direction and previous place
	bool isAlive();
	int getDirection();
	void setStartingPlace();
	sf::Vector2f getPrevPlace();
	virtual void setNextStep() = 0;
	void setAlive(bool flag);
	sf::Vector2f getLoc();

protected:
	void changeDir();
	bool stillAlive = true;
	int isDead = 0;
private:
};

