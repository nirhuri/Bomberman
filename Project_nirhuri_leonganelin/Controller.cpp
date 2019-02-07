#include "Controller.h"



Controller::Controller()
{
	m_robot.setStartPlace(m_board.getRobotPlace());
}


Controller::~Controller()
{
}

void Controller::run()
{
	float timeToCollide = 0; //for propriate collide times
	sf::Clock clock; // for game time
	sf::Event event;
	sf::RenderWindow window(sf::VideoMode((m_board.getBoardSize().x * SHAPE_SIZE),
		m_board.getBoardSize().y * SHAPE_SIZE), "Bomberman");
	sf::Texture* background = PicsandSound::getInstance().getPic(14);
	m_background.setTexture(*background);
	setGuards(); //sets guards locations
	m_robot.setRobotPlace(m_board.getRobotPlace().x, m_board.getRobotPlace().y);
	m_robot.draw(window);

	int lives = 3; // robot's life
	while (window.isOpen() && m_robot.getRobotLife() > 0)
	{
		lives = m_robot.getRobotLife();

		//clock section:
		m_guardTimeToMove += clock.getElapsedTime().asSeconds();
		stopWatch += clock.getElapsedTime().asSeconds();
		timeToCollide += clock.getElapsedTime().asSeconds();
		m_robotTimeToMove += clock.restart().asSeconds();

		if (m_robotTimeToMove >= ROBOT_MOVE_TIME)
		{
			while (window.pollEvent(event) && lives > 0)
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					keyPressedHandler(event, window);
					break;
				}
			}
			m_robotTimeToMove = 0;
		}

		handleGuardsMove(m_guardTimeToMove); //guards move
		bombHandler(); //bombs managing
		checkCollision(timeToCollide); //manage all collision functions
		draw(window); //draw all objects
		setDynamiFont(window, stopWatch); //managing fonts 
		window.display();
		window.clear();
		if (m_alarm <= 0)
		{
			m_robot.decreaseRobotLife(); //if time out
		}
		if (lives > m_robot.getRobotLife())
		{ //if robot dead
			lives--;
			resetLocations();
		}
		if (m_robot.changeLvl())
		{ //if player finished the level
			m_statusBar.setScore((20 * m_board.getNumOfGuards()) + m_statusBar.getScore());
			checkIfLvlEnd(window);
		}

	}
}

//function for managing guards places and type (random or smart):
void Controller::setGuards()
{
	m_guards.resize(m_board.getNumOfGuards());

	for (int i = 0; i < m_board.getNumOfGuards(); i++)
	{
		sf::Vector2f temp = m_board.getGuardPlace(i);

		int randomNum = rand() % 2;
		if (randomNum == 0)
		{
			m_guards[i] = std::make_unique<SmartGuards>(temp);
		}
		else
		{
			m_guards[i] = std::make_unique<RandomGuards>(temp);
		}
	}
}

//moving guards with polymorphisem:
void Controller::handleGuardsMove(float &time)
{
	if (time >= 0.05f)
	{
		m_stepGuards++;
		for (int i = 0; i < m_guards.size(); i++)
		{
			if (m_guards[i]->isAlive() && m_guards[i] != nullptr)
			{
				m_guards[i]->move(m_stepGuards, time, m_robot.getPlace());
			}
		}
		time = 0;
	}
	if (m_stepGuards == 2)
	{
		m_stepGuards = 0;
	}
}

void Controller::resetLevel()
{
	for (int i = 0; i < m_guards.size(); i++)
	{
		m_guards[i].reset(nullptr);
	}
	setGuards();
}

//for loading new level
void Controller::checkIfLvlEnd(sf::RenderWindow &window)
{
	m_robot.setNextLvl();
	window.close();
	m_board.loadLevelFromFile();
	resetLocations();
	run();
}

void Controller::setDynamiFont(sf::RenderWindow &window, float &time)
{
	texts.resize(6);
	texts[0].setFont(*PicsandSound::getInstance().getFont());
	texts[0].setString("Life: ");
	texts[0].setPosition({ 5, 3 });
	texts[0].setCharacterSize(15);
	texts[0].setFillColor(sf::Color::Blue);
	texts[0].setOutlineColor(sf::Color::White);
	texts[0].setOutlineThickness(2);

	texts[1].setFont(*PicsandSound::getInstance().getFont());
	int temp = m_robot.getRobotLife();
	std::string life = std::to_string(temp);
	texts[1].setString(life);
	texts[1].setPosition({ 45, 3 });
	texts[1].setCharacterSize(15);
	texts[1].setFillColor(sf::Color::Blue);
	texts[1].setOutlineColor(sf::Color::White);
	texts[1].setOutlineThickness(2);

	texts[2].setFont(*PicsandSound::getInstance().getFont());
	texts[2].setString("Timer: ");
	texts[2].setPosition({ 65, 3 });
	texts[2].setCharacterSize(15);
	texts[2].setFillColor(sf::Color::Blue);
	texts[2].setOutlineColor(sf::Color::White);
	texts[2].setOutlineThickness(2);
	if (time > 1) {
		texts[3].setFont(*PicsandSound::getInstance().getFont());
		m_alarm -= time;
		std::string timer = std::to_string((int)m_alarm);
		texts[3].setString(timer);
		texts[3].setPosition({ 120, 3 });
		texts[3].setCharacterSize(15);
		texts[3].setFillColor(sf::Color::Blue);
		texts[3].setOutlineColor(sf::Color::White);
		texts[3].setOutlineThickness(2);
		time = 0;
	}


	texts[4].setFont(*PicsandSound::getInstance().getFont());
	texts[4].setString("Score: ");
	texts[4].setPosition({ 160, 3 });
	texts[4].setCharacterSize(15);
	texts[4].setFillColor(sf::Color::Blue);
	texts[4].setOutlineColor(sf::Color::White);
	texts[4].setOutlineThickness(2);

	texts[5].setFont(*PicsandSound::getInstance().getFont());
	int temp3 = m_statusBar.getScore();
	std::string score = std::to_string(temp3);
	texts[5].setString(score);
	texts[5].setPosition({ 215, 3 });
	texts[5].setCharacterSize(15);
	texts[5].setFillColor(sf::Color::Blue);
	texts[5].setOutlineColor(sf::Color::White);
	texts[5].setOutlineThickness(2);

	for (int i = 0; i < texts.size(); i++)
	{
		window.draw(texts[i]);
	}
}

//managing key presses
void Controller::keyPressedHandler(const sf::Event & event, sf::RenderWindow &window)
{
	int direction = 0;
	sf::Vector2i robotMove{ 0,0 };

	switch (event.key.code)
	{
	case sf::Keyboard::Escape:
		window.close();
		break;
	case sf::Keyboard::Right:
		m_robot.setDirection(right_t);
		break;
	case sf::Keyboard::Left:
		m_robot.setDirection(left_t);
		break;
	case sf::Keyboard::Up:
		m_robot.setDirection(up_t);
		break;
	case sf::Keyboard::Down:
		m_robot.setDirection(down_t);
		break;
	case sf::Keyboard::B:
	{
		m_numOfBombs++;
		Bomb bomb(m_robot.getRobotPlace());
		m_bombs.push_back(bomb);
		break;
	};
	}
	if (m_step == 0)
		m_step++;
	else
		m_step--;

	m_robot.move(m_step);
}

//draw all objects
void Controller::draw(sf::RenderWindow & window)
{
	window.draw(m_background);
	m_board.draw(window);
	for (int i = 0; i < m_guards.size(); i++)
	{
		if (m_guards[i]->isAlive() && m_guards[i] != nullptr)
		{
			m_guards[i]->draw(window);
		}
	}
	for (int i = 0; i < m_bombs.size(); i++)
	{
		m_bombs[i].draw(window);
	}

	m_robot.draw(window);
}

//reset objects locations
void Controller::resetLocations()
{
	for (int i = 0; i < m_guards.size(); i++)
	{
		m_guards[i]->setStartingPlace();
	}
	m_robot.setRobotPlace(m_board.getRobotPlace().x, m_board.getRobotPlace().y);
}

//bomb managing
void Controller::bombHandler()
{
	for (int i = 0; i < m_numOfBombs; i++)
	{
		if (!m_bombs[i].decTimer())
		{
			m_numOfBombs--;
			m_bombs.erase(m_bombs.begin() + i);
		}
	}
}

//main function for collisions 
void Controller::checkCollision(float &time)
{
	checkStaticCollision();
	checkCollisionWithGuards(time);
	checkCollisioWithBomb();
}

//collision with statics objects
void Controller::checkStaticCollision()
{
	std::vector <StaticObjects*> neighborsVec;
	neighborsVec = m_board.getNeighbors(m_robot.getDirection(), m_robot.getPlace());
	for (int i = 0; i < neighborsVec.size(); i++)
	{
		if (neighborsVec[i] != nullptr)
		{
			m_robot.collide(neighborsVec[i]);
		}
	}

	for (int i = 0; i < m_guards.size(); i++)
	{
		neighborsVec = m_board.getNeighbors(m_guards[i]->getDirection(), m_guards[i]->getPlace());
		for (int j = 0; j < neighborsVec.size(); j++)
		{
			if (neighborsVec[j] != nullptr)
			{
				m_guards[i]->collide(neighborsVec[j]);
			}
		}
	}
}

//collision with guards
void Controller::checkCollisionWithGuards(float &time)
{
	for (int i = 0; i < m_guards.size(); i++)
	{
		sf::Vector2f temp = m_guards[i]->getLocation();
		if (m_robot.getCharFloatRect().intersects(m_guards[i]->getCharFloatRect()))
		{
			if (time > 1)
			{
				m_guards[i]->collide(&m_robot);
				time = 0;
			}
		}
	}
}

//collision with bombs
void Controller::checkCollisioWithBomb()
{

	std::vector<StaticObjects*> neighbors;
	for (int i = 0; i < m_bombs.size(); i++)
	{
		if (m_bombs[i].getFlag() && !m_robot.ifRobotExploded())
		{
			if (m_robot.getCharFloatRect().intersects(m_bombs[i].getCharFloatRect()))
			{
				m_robot.collide(&m_bombs[i]);
			}
		}

		if (m_bombs[i].getFlag())
		{
			for (int j = 0; j < 5; j++)
			{
				neighbors = m_board.getNeighbors(j, m_bombs[i].getLocation());
				for (int k = 0; k < neighbors.size(); k++)
				{
					if (neighbors[k] != nullptr)
					{
						Rock* rock = (Rock*)neighbors[k];
						m_bombs[i].collide(neighbors[k]);

						if (rock->ifExploded())
						{
							m_board.deleteObject(rock->getPlace().x, rock->getPlace().y);
						}
					}
				}
				for (int t = 0; t < m_guards.size(); t++)
				{
					if (m_guards[t] != nullptr &&
						m_guards[t]->getCharFloatRect().intersects(m_bombs[i].getCharFloatRect()))
					{
						m_guards[t]->collide(&m_bombs[i]);
						m_guards[t] == nullptr;
						m_statusBar.setScore((5 * m_board.getNumOfGuards()) +
							m_statusBar.getScore());
					}
				}
			}
		}
	}
}
