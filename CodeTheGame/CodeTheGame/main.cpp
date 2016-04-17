#include <RGL.h>
#include <RPL.h>

#include "MainMenu.h"

#include "Player.h"
#include "Flag.h"

int main(int argc, char** argv)
{
	if (!rgl::Game::get()->init("Code: THE_GAME();", 640, 480, false, true))
	{
		rgl::Debugger::get()->log("Could not run game.", rgl::Debugger::FATAL_ERROR);
		return 1;
	}
	
	rgl::FontManager::get()->loadFont("assets/fonts/segoeuil.ttf", 12, "Segoe");
	rgl::FontManager::get()->loadFont("assets/fonts/consola.ttf", 12, "Consola");

	rgl::SoundManager::get()->load("assets/sounds/Error.mp3", "Error", rgl::SoundManager::SFX);
	rgl::SoundManager::get()->load("assets/sounds/Flag_Hit.mp3", "FlagHit", rgl::SoundManager::SFX);
	rgl::SoundManager::get()->load("assets/sounds/Menu_Boop.mp3", "MenuBoop", rgl::SoundManager::SFX);
	rgl::SoundManager::get()->load("assets/sounds/Player_Jump1.mp3", "PlayerJump", rgl::SoundManager::SFX);
	rgl::SoundManager::get()->load("assets/sounds/Player_Step1.mp3", "Step1", rgl::SoundManager::SFX);
	rgl::SoundManager::get()->load("assets/sounds/Player_Step2.mp3", "Step2", rgl::SoundManager::SFX);
	rgl::SoundManager::get()->load("assets/sounds/Player_Step3.mp3", "Step3", rgl::SoundManager::SFX);
	rgl::SoundManager::get()->load("assets/sounds/Player_Step4.mp3", "Step4", rgl::SoundManager::SFX);

	rgl::ObjectFactory::get()->registerType("Player", std::make_shared<PlayerCreator>());
	rgl::ObjectFactory::get()->registerType("Flag", std::make_shared<FlagCreator>());

	rgl::Game::get()->run(std::make_shared<MainMenu>());

	rgl::SoundManager::get()->clean();

	return 0;
}