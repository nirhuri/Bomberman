#pragma once
#include <vector>
#include <memory>
#include <fstream>
#include <string>
#include <iostream>
#include <typeinfo>
#include "StaticObjects.h"
#include "Rock.h"
#include "Wall.h"
#include "Door.h"
#include "Objects.h"
#include <typeinfo>


using std::ofstream;
using std::ifstream;

struct storage
{
	//guards storage
	sf::Vector2f place;
};

class Board
{
public:
	Board(); //const
	~Board();
	void loadLevelFromFile();
	void setBoardSize();
	void readCharFromFile(ifstream &file);
	void identifyObject(char obj, int x, int y); // check the char and get obj
	void insertStaticObjectsIntoBoard(int x, int y, char obj); //inserting m_board the pointers to objects
	void draw(sf::RenderWindow &m_window);
	sf::Vector2f getRobotPlace();
	sf::Vector2i getBoardSize();
	int getNumOfGuards();
	sf::Vector2f getGuardPlace(int index);
	//returns the tile neighbors of the direction of the object
	std::vector<StaticObjects*> getNeighbors(int direction, sf::Vector2f place);
	void deleteObject(int i, int j);

private:
	//check val of cells
	void checkCells(int &i, int &j);
	std::vector<std::vector<std::unique_ptr<StaticObjects>>> m_board;
	std::vector <storage> m_guardPlace;
	std::vector<storage> m_visibleBomb;//shows the regular bombs
	sf::Vector2i m_boardSize;
	sf::Vector2f m_robotPlace;
	sf::Vector2f m_robotStart;
	sf::Vector2f m_shapeSize;
	int m_numOfGuards = 0;
	int m_numOfBombs = 0;
	int m_lvlCount = 0; // counts lvls
};

