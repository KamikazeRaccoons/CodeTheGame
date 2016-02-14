#include "Level1.h"
#include <RPL.h>
#include <fstream>

void Level1::onEnter()
{
	m_pLevel = rgl::LevelParser::parseLevel("assets/levels/level1/", "level1.tmx");

	m_pLevel->addCallback(std::bind(&Level1::onRunButton, this));

	m_initScript = rgl::FileIO::readFile("assets/scripts/init.py");
	m_updateScript = rgl::FileIO::readFile("assets/scripts/update.py");

	rpl::Interpreter::get()->execute(m_initScript, false);
}

void Level1::onExit()
{
	m_pLevel->clean();
}

void Level1::update()
{
	if (rgl::InputHandler::get()->isKeyDown(SDL_SCANCODE_RETURN))
		rgl::Game::get()->getGameStateMachine()->changeState(std::make_shared<Level1>());

	rpl::Interpreter::get()->execute(m_updateScript, false);
	m_pLevel->update();
}

void Level1::render()
{
	SDL_SetRenderDrawColor(rgl::Game::get()->getRenderer(), 0, 191, 255, 255);
	SDL_RenderClear(rgl::Game::get()->getRenderer());

	m_pLevel->render();
}

std::string Level1::getStateID() const
{
	return "MainMenu";
}

void Level1::changeState(LevelState state)
{
	if (m_currentState == state)
		return;

	switch (state)
	{
	case EDITING:

		break;
	case RUNNING:

		break;
	}
}

void Level1::onRunButton()
{
	rgl::Debugger::get()->log("Running...");
}