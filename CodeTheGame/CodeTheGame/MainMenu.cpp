#include "MainMenu.h"
#include "LevelManager.h"

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
	LevelManager::get()->setLevel(1);
	rgl::SoundManager::get()->playSound("MenuBoop", 0);
}

void MainMenu::onOptionsButton()
{
	rgl::SoundManager::get()->playSound("MenuBoop", 0);
}

void MainMenu::onExitButton()
{
	rgl::Game::get()->quit();
	rgl::SoundManager::get()->playSound("MenuBoop", 0);
}
