#include "EditState.h"
#include "Player.h"
#include "MainMenu.h"
#include "RunState.h"
#include <RPL.h>
#include <fstream>

void EditState::onEnter()
{
	m_initScript = rgl::FileIO::readFile("assets/scripts/init.py");
	m_updateScript = rgl::FileIO::readFile("assets/scripts/update.py");
	
	m_pLevel = rgl::LevelParser::parseLevel("assets/levels/level1/", "level1.tmx");

	m_pLevel->addObject(std::make_shared<rgl::Button>(544, 384, 64, 32, "RunButton", 0, "RunButton"));
	m_pLevel->addObject(std::make_shared<rgl::Button>(544, 32, 64, 32, "BackButton", 1, "BackButton"));

	m_pLevel->addCallback(std::bind(&EditState::onRunButton, this));
	m_pLevel->addCallback(std::bind(&EditState::onBackButton, this));
}

void EditState::onExit()
{
	m_pLevel->clean();
}

void EditState::update()
{
	if (rgl::InputHandler::get()->isKeyDown(SDL_SCANCODE_RETURN))
		rgl::Game::get()->getGameStateMachine()->changeState(std::make_shared<EditState>());

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

void EditState::onRunButton()
{
	rgl::Game::get()->getGameStateMachine()->changeState(std::make_shared<RunState>());
}

void EditState::onBackButton()
{
	rgl::Game::get()->getGameStateMachine()->changeState(std::make_shared<MainMenu>());
}