#pragma once
#include <memory>
#include "Objects.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "PicsandSound.h"
#include "Robot.h"
#include "Guards.h"
#include "Board.h"
#include "RandomGuards.h"
#include "SmartGuards.h"
#include <time.h>
#include "StatusBar.h"
#include "Bomb.h"
#include <string>
#include <iostream>

using std::time;
const float ROBOT_MOVE_TIME = 0.05f;

class Controller
{
public:
	Controller();
	~Controller();
	void run();

private:
	void keyPressedHandler(const sf::Event & event, sf::RenderWindow &window); //for key press
	void setGuards(); //set guards location from file
	void handleGuardsMove(float &time); //main function for guards move
	void resetLevel(); //reset the level and locations
	void draw(sf::RenderWindow &window); //print the objects and pics on window
	void resetLocations(); //reset objects location when robot deads
	void bombHandler(); //managing the bomb behavior
	void checkCollision(float &time); //main func for collision managing
	void checkStaticCollision(); //collision with static objects
	void checkCollisionWithGuards(float &time); //collision with guards
	void checkCollisioWithBomb(); //collision with bombs
	void checkIfLvlEnd(sf::RenderWindow &window); //checks if robot escaped from level
	void setDynamiFont(sf::RenderWindow &window, float &time); //managing tool bar fonts
	Board m_board;
	std::vector <std::unique_ptr<Guards>> m_guards; //holds the guards stats
	Robot m_robot;
	int m_step = 0; //robot step for pics
	int m_stepGuards = 0; //guards step for pics
	float m_robotTimeToMove = 0; //clock for robot move
	float m_guardTimeToMove = 0; //clock for guards move
	StatusBar m_statusBar; 
	bool gamePaused = true; 
	std::vector<Bomb> m_bombs; //stores the bombs
	int m_numOfBombs = 0;
	std::vector<sf::Text> texts; //store the fonts
	float stopWatch = 0; 
	float m_alarm = 120; //for game stop watch
	sf::Sprite m_background;
};

