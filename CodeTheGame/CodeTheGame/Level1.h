#pragma once

#include <RGL.h>

class Level1 : public rgl::GameState
{
private:

	enum LevelState
	{
		EDITING = 0,
		RUNNING = 1
	} m_currentState = EDITING;

	std::shared_ptr<rgl::Level> m_pLevel;

	std::string m_initScript;
	std::string m_updateScript;

	void changeState(LevelState state);
	void onRunButton();

public:

	Level1() { }

	virtual void onEnter();
	virtual void onExit();

	virtual void update();
	virtual void render();

	virtual std::string getStateID() const;

};

