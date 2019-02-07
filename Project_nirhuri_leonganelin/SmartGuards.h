#pragma once
#include "Guards.h"
#include <SFML/Graphics.hpp>
#include "Robot.h"
#include "Board.h"

class SmartGuards : public Guards
{
public:
	SmartGuards(sf::Vector2f place);
	~SmartGuards();
	//polymorphisem move location and step:
	void move(int step, float &time, sf::Vector2f RobotPlace) override; //mannheten distance
	virtual sf::Vector2f getLocation() override;
	virtual void setNextStep() override;

private:

	void findPath(sf::Vector2f robotPlace);
	int dir = 0;
	int timer = 110;
	bool manhattan(sf::Vector2f robotPlace);
};