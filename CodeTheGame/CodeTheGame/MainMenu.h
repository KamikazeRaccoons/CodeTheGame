#pragma once

#include <RGL.h>

class MainMenu : public rgl::GameState
{
private:

	std::shared_ptr<rgl::Level> m_pLevel;

	static void onPlayButton();
	static void onOptionsButton();
	static void onExitButton();

public:
	
	MainMenu() { }

	virtual void onEnter();
	virtual void onExit();

	virtual void update();
	virtual void render();

	virtual std::string getStateID() const;
};

