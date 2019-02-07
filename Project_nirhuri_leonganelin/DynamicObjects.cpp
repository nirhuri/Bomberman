#include "DynamicObjects.h"



DynamicObjects::DynamicObjects()
{
	m_dirPic = left_t;
	m_step = 0;
}

DynamicObjects::~DynamicObjects()
{
}

void DynamicObjects::setDirection(direction_t dir)
{
	m_direction = dir;
}

direction_t DynamicObjects::getDirection()
{
	return m_direction;
}

