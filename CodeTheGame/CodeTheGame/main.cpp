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
		::system("PAUSE");
	}

	rpl::Interpreter::getInstance()->initialize();

	rgl::ObjectFactory::get()->registerType("Player", std::make_shared<PlayerCreator>());

	rgl::Game::get()->run(std::make_shared<MainMenu>());

	return 0;
}