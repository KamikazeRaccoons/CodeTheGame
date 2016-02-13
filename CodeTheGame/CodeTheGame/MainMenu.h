#pragma once

#include <RGL.h>

class MainMenu : public rgl::GameState
{
public:
	
	MainMenu() { }

	virtual void onEnter();
	virtual void onExit();

	virtual void update();
	virtual void render();

	virtual std::string getStateID() const;
};

