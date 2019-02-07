#include "Menu.h"



Menu::Menu()
{
}

void Menu::run()
{
	while (!m_exit) {
		sf::RenderWindow window(sf::VideoMode(1000, 800), "Bomberman");

		//while window is open
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
					//user pressed something
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::Up:
						MoveUp();
						break;

					case sf::Keyboard::Down:
						MoveDown();
						break;

					case sf::Keyboard::Enter:
						handleChoice(window);
						break;
					}

				}
			}
			window.clear();
			draw(window);
			window.display();
		}
	}
}

void Menu::draw(sf::RenderWindow &window)
{
	//draws the menu
	window.draw(m_sprite);
	window.draw(options[0]);
	window.draw(options[1]);
	window.draw(options[2]);
}

void Menu::MoveUp()
{

	if (selectedItemIndex - 1 >= 0)
	{
		options[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex--;
		options[selectedItemIndex].setColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < NUM_OF_OPTIONS)
	{
		options[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex++;
		options[selectedItemIndex].setColor(sf::Color::Red);
	}
}

void Menu::changeGameState()
{
	sf::Texture * temp;
	//put resume instead of new game
	temp = PicsandSound::getInstance().getPic(12);
	options[0].setTexture(*temp);
	options[0].setColor(sf::Color::Red);
}

void Menu::handleChoice(sf::RenderWindow &window)
{
	if (selectedItemIndex == 0)
	{
		window.close();
		Controller controller;
		controller.run();
		changeGameState();
	}
	else if (selectedItemIndex == 1)
		std::cout << "hs";
	else if (selectedItemIndex == 2) {
		m_exit = true;
		window.close();
	}
}

void Menu::registerHighscore()
{
	//std::cout << "Please enter you name\n";
	//std::cin >> highscores[0].
}

void Menu::build()
{
	readHighscores();
	sf::Texture *texture = PicsandSound::getInstance().getPic(8);

	m_sprite.setTexture(*texture);

	sf::Vector2u TextureSize;  //Added to store texture size.
	sf::Vector2f WindowSize;   //Added to store window size.
	TextureSize = texture->getSize(); //Get size of texture.
	WindowSize = sf::Vector2f{ 1000, 800 };          //Get size of window.
	float ScaleX = (float)WindowSize.x / TextureSize.x;
	float ScaleY = (float)WindowSize.y / TextureSize.y;     //Calculate scale.
	m_sprite.setTexture(*texture);
	m_sprite.setScale(ScaleX, ScaleY);      //Set scale.  

	sf::Texture * temp;

	temp = PicsandSound::getInstance().getPic(9);
	options[0].setTexture(*temp);
	options[0].setOrigin(PIC_SIZE_X / 2, PIC_SIZE_Y / 2);
	options[1].setOrigin(PIC_SIZE_X / 2, PIC_SIZE_Y / 2);
	options[2].setOrigin(PIC_SIZE_X / 2, PIC_SIZE_Y / 2);
	options[0].setPosition(1000 / 2, 800 / 2);
	options[0].setColor(sf::Color::Red);
	options[0].setScale(2, 2);
	temp = PicsandSound::getInstance().getPic(10);
	options[1].setTexture(*temp);
	options[1].setPosition(1000 / 2, 800 / 2 + 100);
	options[1].setScale(2, 2);
	temp = PicsandSound::getInstance().getPic(11);
	options[2].setTexture(*temp);
	options[2].setPosition(1000 / 2, 800 / 2 + 200);
	options[2].setScale(2, 2);

	options[0].setScale(0.8, 0.8);
	options[1].setScale(0.8, 0.8);
	options[2].setScale(0.8, 0.8);

	selectedItemIndex = 0;
}

void Menu::readHighscores()
{
	ifstream file;

	file.open("Highscores/highscores");

	for (int i = 0; i < 10; i++)
	{
		file >> highscores[i].name;
		file >> highscores[i].score;
	}
}
