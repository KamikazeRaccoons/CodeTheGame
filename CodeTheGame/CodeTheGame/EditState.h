#pragma once

#include <RGL.h>

class EditState : public rgl::GameState
{
private:

	std::shared_ptr<rgl::Level> m_pLevel;

	std::shared_ptr<rgl::TextBox> m_pInitTextBox;
	std::shared_ptr<rgl::TextBox> m_pUpdateTextBox;

	int m_levelNumber;

	void onRunButton();
	void onBackButton();

public:

	EditState(int levelNumber) : m_levelNumber(levelNumber) { }

	virtual void onEnter();
	virtual void onExit();

	virtual void update();
	virtual void render();

	virtual std::string getStateID() const;

};

