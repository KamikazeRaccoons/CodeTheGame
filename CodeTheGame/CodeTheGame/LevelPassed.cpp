#include "LevelPassed.h"
#include "MainMenu.h"
#include "EditState.h"

void LevelPassed::onCreate()
{
	rgl::SimpleActor::onCreate();

	m_position.setX(rgl::Game::get()->getWidth() / 2 - m_width / 2);
	m_position.setY(-m_height);
}

void LevelPassed::onDestroy()
{
	rgl::SimpleActor::onDestroy();
}

void LevelPassed::update()
{
	m_velocity.setY((rgl::Game::get()->getHeight() / 2 - (m_position.getY() + m_height / 2)) * 0.1);

	if (--m_timeLeft < 0)
	{
		if (rgl::FileIO::fileExists("assets/levels/level" + std::to_string(m_nextLevel) + "/level" + std::to_string(m_nextLevel) + ".tmx"))
			rgl::Game::get()->getGameStateMachine()->changeState(std::make_shared<EditState>(m_nextLevel));
		else
			rgl::Game::get()->getGameStateMachine()->changeState(std::make_shared<MainMenu>());
	}

	rgl::SimpleActor::update();
}

void LevelPassed::draw()
{
	rgl::TextureManager::get()->draw(m_textureID, (int)m_position.getX(), (int)m_position.getY(), m_width, m_height);
}