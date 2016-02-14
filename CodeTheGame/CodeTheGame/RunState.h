#pragma once

#include <RGL.h>

class RunState : public rgl::GameState
{
private:

	std::shared_ptr<rgl::Level> m_pLevel;

	std::string m_initScript;
	std::string m_updateScript;

	int m_levelNumber;

	void onCancelButton();
	void onBackButton();

public:

	RunState(int levelNumber) : m_levelNumber(levelNumber) { }

	virtual void onEnter();
	virtual void onExit();

	virtual void update();
	virtual void render();

	virtual std::string getStateID() const;

};

