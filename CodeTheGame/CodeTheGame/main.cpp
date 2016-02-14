#include <RGL.h>
#include <RPL.h>

#include "MainMenu.h"
#include "Level1.h"

#include "Player.h"

int main(int argc, char** argv)
{
	if (!rgl::Game::get()->init("Code: The Game", 640, 480, true))
	{
		rgl::Debugger::get()->log("Could not run game.", rgl::Debugger::FATAL_ERROR);
		return 1;
	}

	rgl::FontManager::get()->load("assets/fonts/segoeuil.ttf", 12, "Segoe");

	rgl::ObjectFactory::get()->registerType("Player", std::make_shared<PlayerCreator>());

	if (!rpl::Interpreter::get()->initialize())
	{
		rgl::Debugger::get()->log("Could not initialize interpreter.", rgl::Debugger::FATAL_ERROR);
		return 1;
	}

	Player::registerPythonClass();

	rgl::Game::get()->run(std::make_shared<MainMenu>());

	return 0;
}