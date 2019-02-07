#pragma once
#include <SFML/Graphics.hpp>
#include "PicsandSound.h"
#include "StatusBar.h"
#include <vector>


enum direction_t { down_t, left_t, right_t, up_t, static_t };
enum step_t { first_t, second_t };

class Rock;
class Bomb;
class Wall;
class Door;
class Guards;
class Robot;

class Objects
{
public:
	Objects();
	~Objects();
	//double dispatch and polymorphisem:
	virtual void draw(sf::RenderWindow & window) = 0;
	virtual void collide(Objects* obj) = 0;
	virtual void collide(Robot* other) = 0;
	virtual void collide(Guards* other) = 0;
	virtual void collide(Wall* other) = 0;
	virtual void collide(Door* other) = 0;
	virtual void collide(Bomb* other) = 0;
	virtual void collide(Rock* other) = 0;
	sf::FloatRect getCharFloatRect(); //for global bounds
	sf::Vector2f getPlace();

protected:
	sf::Vector2f m_place;
	sf::Vector2f m_prevPlace;
	sf::Vector2f m_startingPlace;
	sf::Sprite m_sprite;
	int m_step;
};

