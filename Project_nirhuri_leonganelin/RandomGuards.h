#pragma once
#include "Guards.h"
#include <time.h>
#include "Board.h"

using std::time;
const float MOVE_TIME = 1.f;

class RandomGuards : public Guards
{
public:
	RandomGuards(sf::Vector2f place);
	~RandomGuards();
	//polymorphisem move location and step:
	void move(int step, float &time, sf::Vector2f RobotPlace) override;
	sf::Vector2f getLocation() override;
	virtual void setNextStep() override;

private:
	float m_timeToChangeDir = 0;
};

