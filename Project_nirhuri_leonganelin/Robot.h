#pragma once
#include "DynamicObjects.h"
#include "PicsandSound.h"
#include "Board.h"
#include "StatusBar.h"

class Robot : public DynamicObjects
{
public:
	Robot();
	~Robot();
	//move and draw functions:
	void setStartPlace(sf::Vector2f place);
	void move(int step);
	void draw(sf::RenderWindow &window) override;
	void setRobotPlace(float x, float y);
	sf::Vector2f getRobotPlace();
	//double dispatch and polymorphisem:
	virtual void collide(Objects* obj) override;
	virtual void collide(Guards* other) override;
	virtual void collide(Bomb* other) override;
	virtual void collide(Door* other) override;
	void collide(Rock* other) override;
	virtual void collide(Wall* other) override;
	virtual void collide(Robot* other) override {};
	//life and when robot finished level:
	bool changeLvl();
	void setNextLvl();
	int getRobotLife();
	void decreaseRobotLife();
	void resetLocation();
	bool ifRobotExploded();
	void setRobotStatus(bool status);

private:
	int m_life;
	void changeStep(int step);
	void setPic(int direction);
	bool nextLvl = false;
	bool robotExploded = false;
};

