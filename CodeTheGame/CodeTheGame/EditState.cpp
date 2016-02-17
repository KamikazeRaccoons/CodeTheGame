#include "EditState.h"
#include "Player.h"
#include "Label.h"
#include "MainMenu.h"
#include "RunState.h"
#include "LevelManager.h"
#include <RPL.h>

void EditState::onEnter()
{
	m_pLevel = rgl::LevelParser::parseLevel(m_levelPath, m_levelFile);

	m_pLevel->addObject(std::make_shared<rgl::Button>(544, 384, 64, 32, "RunButton", 0, "RunButton"));
	m_pLevel->addObject(std::make_shared<rgl::Button>(544, 32, 64, 32, "BackButton", 1, "BackButton"));

	m_pLevel->addObject(m_pInitTextBox = std::make_shared<rgl::TextBox>(false, 0, 0, 384, 224, 127, 127, 127, 191, "Consola", "InitEditor"));
	m_pLevel->addObject(m_pUpdateTextBox = std::make_shared<rgl::TextBox>(false, 0, 256, 384, 224, 127, 127, 127, 191, "Consola", "UpdateEditor"));

	m_pInitTextBox->setText(loadScript("scripts/init.py"));
	m_pUpdateTextBox->setText(loadScript("scripts/update.py"));

	m_pLevel->addObject(std::make_shared<Label>(320, 0, 64, 32, "InitOn", "InitLabel"));
	m_pLevel->addObject(std::make_shared<Label>(320, 256, 64, 32, "UpdateOn", "UpdateLabel"));

	m_pLevel->addCallback(std::bind(&EditState::onRunButton, this));
	m_pLevel->addCallback(std::bind(&EditState::onBackButton, this));
}

void EditState::onExit()
{
	m_pLevel->clean();
}

void EditState::update()
{
	m_pLevel->update();
}

void EditState::render()
{
	SDL_SetRenderDrawColor(rgl::Game::get()->getRenderer(), 0, 191, 255, 255);
	SDL_RenderClear(rgl::Game::get()->getRenderer());

	m_pLevel->render();
}

std::string EditState::getStateID() const
{
	return "MainMenu";
}

std::string EditState::loadScript(std::string filename)
{
	std::string fullFileName = m_levelPath + filename;

	if (rgl::FileIO::fileExists(fullFileName))
		return rgl::FileIO::readFile(fullFileName);

	if (LevelManager::get()->getCurrentLevel() != 1)
	{
		std::string prevFullFileName = LevelManager::get()->getLevelPath(LevelManager::get()->getCurrentLevel() - 1) + filename;

		if (rgl::FileIO::fileExists(prevFullFileName))
			return rgl::FileIO::readFile(prevFullFileName);
	}

	return std::string();
}

void EditState::onRunButton()
{
	rgl::FileIO::writeFile(m_levelPath + "scripts/init.py", m_pInitTextBox->getText());
	rgl::FileIO::writeFile(m_levelPath + "scripts/update.py", m_pUpdateTextBox->getText());

	rgl::Game::get()->getGameStateMachine()->changeState(std::make_shared<RunState>(m_levelPath, m_levelFile));

	rgl::SoundManager::get()->playSound("MenuBoop", 0);
}

void EditState::onBackButton()
{
	rgl::Game::get()->getGameStateMachine()->changeState(std::make_shared<MainMenu>());
	rgl::SoundManager::get()->playSound("MenuBoop", 0);
}