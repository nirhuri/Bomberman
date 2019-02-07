#pragma once
#include "PicsandSound.h"
#include <SFML/Graphics.hpp> 
#include "Board.h"
#include "Controller.h"
#include "Highscore.h"
#include <fstream>


#define SFML_NO_DEPRECATED_WARNINGS

#define NUM_OF_OPTIONS 3
#define WIDTH 1200
#define HEIGHT 700
const int PIC_SIZE_X = 320;
const int PIC_SIZE_Y = 50;

class Menu
{


public:
	Menu();
	void run();
	void draw(sf::RenderWindow &window);
	void changeGameState(); // is it new game or paused by esc
	void build(); // builds the menu

private:

	Highscore highscores[10]; // player highscores
	sf::Sprite m_sprite; //background
	int selectedItemIndex; // option menu
	sf::Sprite options[NUM_OF_OPTIONS]; //pics of options
	void readHighscores();
	//Board m_board;
	void MoveUp();
	void MoveDown();
	void handleChoice(sf::RenderWindow &window); // users choice
	bool m_exit = false;
	void registerHighscore();
};