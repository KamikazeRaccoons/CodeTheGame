#pragma once

#include <RGL.h>

class LevelPassed : public rgl::SimpleActor
{
private:

	int m_timeLeft;

public:

	LevelPassed(int width, int height, std::string name)
		: rgl::SimpleActor(0, 0, width, height, 0, "LevelPassed", name), m_timeLeft(120) { }

	virtual void onCreate();
	virtual void onDestroy();

	virtual void update();
	virtual void draw();

};

