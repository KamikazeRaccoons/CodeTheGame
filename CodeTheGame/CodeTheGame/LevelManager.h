#pragma once

#include <RGL.h>

class LevelManager
{
private:

	static LevelManager* m_pInstance;

	int m_currentLevel;

public:

	LevelManager() : m_currentLevel(0) { }

	static LevelManager* get();

	void advanceLevel();
	void setLevel(int levelNumber);

};

