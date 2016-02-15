#include "LevelManager.h"
#include "EditState.h"
#include "MainMenu.h"

LevelManager* LevelManager::m_pInstance = 0;

LevelManager* LevelManager::get()
{
	if (m_pInstance == 0)
		m_pInstance = new LevelManager();

	return m_pInstance;
}

void LevelManager::advanceLevel()
{
	setLevel(m_currentLevel + 1);
}

void LevelManager::setLevel(int levelNumber)
{
	std::string levelName = "level" + std::to_string(levelNumber);
	std::string levelPath = "assets/levels/" + levelName + "/";

	if (rgl::FileIO::fileExists(levelPath + levelName + ".tmx"))
	{
		rgl::Game::get()->getGameStateMachine()->changeState(std::make_shared<EditState>(levelPath, levelName + ".tmx"));
		m_currentLevel = levelNumber;
	}
	else
	{
		rgl::Game::get()->getGameStateMachine()->changeState(std::make_shared<MainMenu>());
		m_currentLevel = 0;
	}
}