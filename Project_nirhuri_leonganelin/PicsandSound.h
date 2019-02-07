#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "StatusBar.h"
#include <string> 


const int SHAPE_SIZE = 32;

class PicsandSound
{
public:
	~PicsandSound();
	static PicsandSound & getInstance(); //singelton
	/*	void playGuardCatch();
		void playHighScore();
		void playExplosion();
		void playClick();
		void playGift();
		void playBackGround();
		void muteMusic();
		void unMuteMusic();	*/
	sf::Texture* getPic(int index); //get specific picture
	sf::Font* getFont(); //get font

private:
	PicsandSound(); //private c.tor
	int m_numOfPics = 15;
	int m_numOfAudio = 6;
	std::vector<sf::Texture> m_texture;
	//std::vector<sf::> m_music;
	sf::Text text1;
	sf::Font font;
};

