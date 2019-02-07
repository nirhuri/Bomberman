#include "PicsandSound.h"



PicsandSound::PicsandSound()
{
	m_texture.resize(m_numOfPics);
	m_texture[0].loadFromFile("Pics/bomberman.png");
	m_texture[1].loadFromFile("Pics/rock.png");
	m_texture[2].loadFromFile("Pics/wall.png");
	m_texture[3].loadFromFile("Pics/guard.png");
	m_texture[4].loadFromFile("Pics/gift.png");
	m_texture[5].loadFromFile("Pics/bomb.png");
	m_texture[7].loadFromFile("Pics/door.png");
	m_texture[8].loadFromFile("Pics/menu.png");
	m_texture[9].loadFromFile("Pics/newgame.png");
	m_texture[10].loadFromFile("Pics/highscores.png");
	m_texture[11].loadFromFile("Pics/exit.png");
	m_texture[12].loadFromFile("Pics/resume.png");
	m_texture[13].loadFromFile("Pics/exp.png");
	m_texture[14].loadFromFile("Pics/background.jpg");

	/*m_music.resize(m_numOfAudio);
	m_music[0].openFromFile("Sound/Background/flac");
	m_music[0].setVolume(50);
	m_music[1].openFromFile("Sound/HighScore.flac");
	m_music[2].openFromFile("Sound/Click.wav");
	m_music[3].openFromFile("Sound/Gift.wav");
	m_music[4].openFromFile("Sound/GuardCatch.wav");
	m_music[5].openFromFile("Sound/Explosion.wav");*/
}


PicsandSound::~PicsandSound()
{
}

PicsandSound & PicsandSound::getInstance()
{
	static PicsandSound m_instance;
	return m_instance;
}

/*void PicsandSound::playGuardCatch()
{
	m_music[4].play();
}

void PicsandSound::playHighScore()
{
	m_music[1].setLoop(true);
	m_music[1].play();
}

void PicsandSound::playExplosion()
{
	m_music[5].play();
}

void PicsandSound::playClick()
{
	m_music[2].play();
}

void PicsandSound::playGift()
{
	m_music[3].play();
}

void PicsandSound::playBackGround()
{
	m_music[0].setLoop(true);
	m_music[0].play();
}

void PicsandSound::muteMusic()
{
	for (int i = 0; i < m_numOfAudio; i++)
	{
		m_music[i].setVolume(0);
	}
}

void PicsandSound::unMuteMusic()
{
	for (int i = 0; i < m_numOfAudio; i++)
	{
		m_music[i].setVolume(100);
	}
	m_music[0].setVolume(50);
}
*/
sf::Texture * PicsandSound::getPic(int index)
{
	return &m_texture[index];
}

sf::Font* PicsandSound::getFont()
{

	if (!font.loadFromFile("Fonts/font.otf"))
	{
		std::cerr << "Cannot open Font file" << std::endl;
		exit(EXIT_FAILURE);
	}

	return &font;
}
