#include "Board.h"

Board::Board()
{
	loadLevelFromFile();
}


Board::~Board()
{
}

void Board::loadLevelFromFile()
{
	m_lvlCount++;
	//get input about map
	std::string num = std::to_string(m_lvlCount);
	std::string fileName("Levels/Lvl");
	ifstream file;
	num.append(".txt");
	fileName.append(num);

	file.open(fileName);
	if (!file.is_open())
	{
		std::cerr << "Cannot open Level from File" << std::endl;
		exit(EXIT_FAILURE);
	}

	file >> m_boardSize.x >> m_boardSize.y;
	setBoardSize();
	readCharFromFile(file);//set the board
}

void Board::setBoardSize()
{
	//create the sizes of the array
	m_board.resize(m_boardSize.x);
	for (int i = 0; i < m_boardSize.x; i++)
	{
		m_board[i].resize(m_boardSize.y);
		for (int j = 0; j < m_boardSize.y; j++)
		{
			m_board[i][j] = nullptr;
		}
	}
}

//the function runs on the file map and read the characters. its send the
//character to the function that check the type of the chararcter
void Board::readCharFromFile(ifstream &file)
{
	char object;
	for (int i = 0; i < m_boardSize.x; i++)
	{
		file.get();
		for (int j = 0; j < m_boardSize.y; j++)
		{
			object = file.get();
			identifyObject(object, i, j);
		}
	}
}

void Board::identifyObject(char obj, int x, int y)
{
	//discovers what kind of obj it is from the file
	switch (obj)
	{
	case '!':
		m_numOfGuards++;
		m_guardPlace.resize(m_numOfGuards);
		m_guardPlace[m_numOfGuards - 1].place.x = x * SHAPE_SIZE + SHAPE_SIZE / 2;
		m_guardPlace[m_numOfGuards - 1].place.y = y * SHAPE_SIZE + SHAPE_SIZE / 2;
		break;
	case '/':
		m_robotPlace = { (float)x*SHAPE_SIZE + SHAPE_SIZE / 2,(float)y*SHAPE_SIZE + SHAPE_SIZE / 2 };
		m_robotStart = m_robotPlace;
		break;

	case '+':
		m_numOfBombs++;
		m_visibleBomb.resize(m_numOfBombs);
		m_visibleBomb[m_numOfBombs - 1].place.x = x * SHAPE_SIZE + SHAPE_SIZE / 2;
		m_visibleBomb[m_numOfBombs - 1].place.y = y * SHAPE_SIZE + SHAPE_SIZE / 2;
		break;

	case '#':
		insertStaticObjectsIntoBoard(x, y, '#');
		break;

	case '@':
		insertStaticObjectsIntoBoard(x, y, '@');
		break;

	case '&':
		insertStaticObjectsIntoBoard(x, y, '&');
		break;
	case 'D':
		insertStaticObjectsIntoBoard(x, y, 'D');
	}
}


void Board::insertStaticObjectsIntoBoard(int x, int y, char obj)
{
	//setting the object into the board
	if (obj == '#')
		m_board[x][y] = std::make_unique <Wall>(sf::Vector2i{ x,y });
	else if (obj == '@')
		m_board[x][y] = std::make_unique <Rock>(false, sf::Vector2i{ x,y });
	else if (obj == '&')
		m_board[x][y] = std::make_unique <Rock>(true, sf::Vector2i{ x,y });
	else if (obj == 'D')
		m_board[x][y] = std::make_unique <Door>(sf::Vector2i{ x,y });
}

void Board::draw(sf::RenderWindow & m_window)
{
	//draws the board
	for (int i = 0; i < m_boardSize.x; i++)
	{
		for (int j = 0; j < m_boardSize.y; j++)
		{
			if (m_board[i][j] != nullptr)
				m_board[i][j].get()->draw(m_window);
		}
	}
}

sf::Vector2f Board::getRobotPlace()
{
	return m_robotStart;
}

sf::Vector2i Board::getBoardSize()
{
	return m_boardSize;
}

int Board::getNumOfGuards()
{
	return m_numOfGuards;
}

sf::Vector2f Board::getGuardPlace(int index)
{
	return m_guardPlace[index].place;
}

std::vector<StaticObjects*> Board::getNeighbors(int direction, sf::Vector2f place)
{
	std::vector<StaticObjects*> neighbors;

	switch (direction) //check collision in radius 16px from the object
	{
	case down_t:place.y += 16.f;
		break;
	case left_t:  place.x -= 16.f;
		break;
	case right_t: place.x += 16.f;
		break;
	case up_t: place.y -= 16.f;
		break;
	}

	int i = (int)place.x / SHAPE_SIZE; //for getting the object place in array index
	int j = (int)place.y / SHAPE_SIZE;
	checkCells(i, j);
	neighbors.emplace_back(m_board[i][j].get());

	int temp = m_board.size();
	int temp2 = m_board[0].size();
	switch (direction)
	{
	case right_t:
	case left_t:
		if (j > 0)
			neighbors.emplace_back(m_board[i][j - 1].get());//k, m are the neigbors of object
		if (j < m_board[i].size() - 1)
			neighbors.emplace_back(m_board[i][j + 1].get());

		break;
	case down_t:
	case up_t:
		if (i < m_board.size() - 1)
			neighbors.emplace_back(m_board[i + 1][j].get());
		if (i > 0)
			neighbors.emplace_back(m_board[i - 1][j].get());
		break;
	}

	return neighbors;
}

void Board::deleteObject(int i, int j)
{
	int k = i / SHAPE_SIZE;
	int m = j / SHAPE_SIZE;
	Rock temp;
	if (typeid(*m_board[k][m]) == typeid(temp))
		m_board[k][m].reset(nullptr);
}

void Board::checkCells(int & i, int & j)
{
	i >= m_boardSize.x ? i = i % m_boardSize.x : i;
	j >= m_boardSize.y ? j = j % m_boardSize.y : j;
	i <= 0 ? i = 0 : i;
	j <= 0 ? j = 0 : j;
}

