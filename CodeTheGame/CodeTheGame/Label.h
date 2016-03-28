#pragma once

#include <RGL.h>

class Label : public rgl::GameObject
{
private:

	std::string m_textureID;

	int m_x;
	int m_y;

	int m_width;
	int m_height;

public:
	
	Label(int x, int y, int width, int height, std::string textureID, std::string name = "(unnamed Label)")
		: rgl::GameObject(name), m_x(x), m_y(y), m_width(width), m_height(height), m_textureID(textureID) { }

	virtual void update() { }
	virtual void draw();

	virtual int getX() { return m_x; }
	virtual int getY() { return m_y; }

	virtual int getWidth() { return m_width; }
	virtual int getHeight() { return m_height; }

};

