#pragma once

class StatusBar
{
public:
	StatusBar();
	~StatusBar();
	int getLifeCount(); //return the amount of life the robot left
	int getBombCount(); //return the amount of bomb the robot left
	void setLifeCount(); //if we need to decrease the robot life
	void setBombCount(bool flag); //true for add bomb 
	void setScore(int num); //set the player score
	int getScore();

private:
	int m_robotLife = 5; //life counter
	int m_bombLeft = 3; //stores the amount of bomb the robot left
	int	m_lvl = 0; //for print on screen the current level
	int m_score = 0;
};

