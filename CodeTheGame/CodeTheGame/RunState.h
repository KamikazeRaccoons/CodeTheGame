#pragma once

#include <RGL.h>

class RunState : public rgl::GameState
{
private:

	std::shared_ptr<rgl::Level> m_pLevel;

	std::string m_initScript;
	std::string m_updateScript;

	std::string m_levelPath;
	std::string m_levelFile;

	void onCancelButton();
	void onBackButton();

public:

	RunState(std::string levelPath, std::string levelFile) : m_levelPath(levelPath), m_levelFile(levelFile) { }

	virtual void onEnter();
	virtual void onExit();

	virtual void update();
	virtual void render();

	virtual std::string getStateID() const;

};
