#include "StatusBar.h"



StatusBar::StatusBar()
{
}


StatusBar::~StatusBar()
{
}

int StatusBar::getLifeCount()
{
	return m_robotLife;
}

int StatusBar::getBombCount()
{
	return m_bombLeft;
}

void StatusBar::setLifeCount()
{
	m_robotLife = m_robotLife - 1;
}

void StatusBar::setBombCount(bool flag)
{
	if (flag)
	{
		m_bombLeft = m_bombLeft + 1;
	}

	else
	{
		m_bombLeft = m_bombLeft - 1;
	}
}

void StatusBar::setScore(int num)
{
	m_score = num;
}

int StatusBar::getScore()
{
	return m_score;
}
