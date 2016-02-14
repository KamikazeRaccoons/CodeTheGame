#include "MainMenu.h"
#include "EditState.h"

void MainMenu::onEnter()
{
	m_pLevel = rgl::LevelParser::parseLevel("assets/levels/main_menu/", "main_menu.tmx");

	m_pLevel->addCallback(&onPlayButton);
	m_pLevel->addCallback(&onOptionsButton);
	m_pLevel->addCallback(&onExitButton);
}

void MainMenu::onExit()
{
}

void MainMenu::update()
{
	m_pLevel->update();
}

void MainMenu::render()
{
	SDL_SetRenderDrawColor(rgl::Game::get()->getRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(rgl::Game::get()->getRenderer());

	m_pLevel->render();
}

std::string MainMenu::getStateID() const
{
	return "MainMenu";
}

void MainMenu::onPlayButton()
{
	rgl::Game::get()->getGameStateMachine()->changeState(std::make_shared<EditState>());
}

void MainMenu::onOptionsButton()
{

}

void MainMenu::onExitButton()
{
	rgl::Game::get()->quit();
}
