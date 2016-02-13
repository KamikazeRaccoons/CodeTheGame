#include <RGL.h>
#include <RPL.h>

#include "MainMenu.h"
#include "Level1.h"

#include "Player.h"

int main(int argc, char** argv)
{
	rpl::Interpreter::getInstance()->initialize();

	rgl::ObjectFactory::get()->registerType("Player", std::make_shared<PlayerCreator>());

	if (!rgl::Game::get()->run("Code: The Game", 640, 480, std::make_shared<Level1>(), true))
	{
		rgl::Debugger::get()->log("Could not run game.", rgl::Debugger::FATAL_ERROR);
		::system("PAUSE");
	}

	return 0;
}