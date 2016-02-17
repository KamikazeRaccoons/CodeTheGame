#pragma once

#include <RGL.h>

class EditState : public rgl::GameState
{
private:

	std::shared_ptr<rgl::Level> m_pLevel;

	std::shared_ptr<rgl::TextBox> m_pInitTextBox;
	std::shared_ptr<rgl::TextBox> m_pUpdateTextBox;

	std::string m_levelPath;
	std::string m_levelFile;

	std::string loadScript(std::string filename);

	void onRunButton();
	void onBackButton();

public:

	EditState(std::string levelPath, std::string levelFile) : m_levelPath(levelPath), m_levelFile(levelFile) { }

	virtual void onEnter();
	virtual void onExit();

	virtual void update();
	virtual void render();

	virtual std::string getStateID() const;

};

