#include <RGL.h>
#include <RPL.h>

#include "MainMenu.h"

#include "Player.h"
#include "Flag.h"

int main(int argc, char** argv)
{
	if (!rgl::Game::get()->init("Code: THE_GAME();", 640, 480, true))
	{
		rgl::Debugger::get()->log("Could not run game.", rgl::Debugger::FATAL_ERROR);
		return 1;
	}

	rgl::FontManager::get()->load("assets/fonts/segoeuil.ttf", 12, "Segoe");

	rgl::ObjectFactory::get()->registerType("Player", std::make_shared<PlayerCreator>());
	rgl::ObjectFactory::get()->registerType("Flag", std::make_shared<FlagCreator>());

	rgl::Game::get()->run(std::make_shared<MainMenu>());

	return 0;
}