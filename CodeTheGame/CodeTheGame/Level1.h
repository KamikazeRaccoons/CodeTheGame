#pragma once

#include <RGL.h>

class Level1 : public rgl::GameState
{
private:

	std::shared_ptr<rgl::Level> m_pLevel;

public:

	Level1() { }

	virtual void onEnter();
	virtual void onExit();

	virtual void update();
	virtual void render();

	virtual std::string getStateID() const;

};

