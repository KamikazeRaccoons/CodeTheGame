#include "Level1.h"


void Level1::onEnter()
{
	m_pLevel = rgl::LevelParser::parseLevel("assets/levels/level1/", "level1.tmx");
}

void Level1::onExit()
{

}

void Level1::update()
{
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