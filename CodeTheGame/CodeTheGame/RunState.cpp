#include "RunState.h"
#include "MainMenu.h"
#include "EditState.h"
#include "Player.h"
#include "LevelPassed.h"
#include <RPL.h>

void RunState::onEnter()
{
	m_initScript = rgl::FileIO::readFile(m_levelPath + "scripts/init.py");
	m_updateScript = rgl::FileIO::readFile(m_levelPath + "scripts/update.py");

	if (!rpl::Interpreter::get()->initialize())
	{
		rgl::Debugger::get()->log("Could not initialize interpreter.", rgl::Debugger::FATAL_ERROR);
		return;
	}

	Player::registerPythonClass();

	m_pLevel = rgl::LevelParser::parseLevel(m_levelPath, m_levelFile);

	m_pLevel->addObject(std::make_shared<rgl::Button>(544, 384, 64, 32, "CancelButton", 0, "CancelButton"));
	m_pLevel->addObject(std::make_shared<rgl::Button>(544, 32, 64, 32, "BackButton", 1, "BackButton"));

	m_pLevel->addCallback(std::bind(&RunState::onCancelButton, this));
	m_pLevel->addCallback(std::bind(&RunState::onBackButton, this));

	m_pLevel->update();
	rgl::Debugger::get()->log(rpl::Interpreter::get()->execute(m_initScript, false));
}

void RunState::onExit()
{
	rpl::Interpreter::get()->reset();

	m_pLevel->clean();
}

void RunState::update()
{
	rgl::Debugger::get()->log(rpl::Interpreter::get()->execute(m_updateScript, false));

	m_pLevel->update();
}

void RunState::render()
{
	SDL_SetRenderDrawColor(rgl::Game::get()->getRenderer(), 0, 191, 255, 255);
	SDL_RenderClear(rgl::Game::get()->getRenderer());

	m_pLevel->render();
}

std::string RunState::getStateID() const
{
	return "MainMenu";
}

void RunState::onCancelButton()
{
	rgl::Game::get()->getGameStateMachine()->changeState(std::make_shared<EditState>(m_levelPath, m_levelFile));
	rgl::SoundManager::get()->playSound("MenuBoop", 0);
}

void RunState::onBackButton()
{
	rgl::Game::get()->getGameStateMachine()->changeState(std::make_shared<MainMenu>());
	rgl::SoundManager::get()->playSound("MenuBoop", 0);
}