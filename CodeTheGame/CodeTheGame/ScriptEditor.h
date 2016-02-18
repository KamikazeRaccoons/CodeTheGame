#pragma once

#include <RGL.h>

class ScriptEditor : public rgl::TextBox
{
public:

	ScriptEditor(bool enabled, int x, int y, int width, int height, std::string name = "(unnamed ScriptEditor)")
		: rgl::TextBox(enabled, x, y, width, height, 2, 0, 0, 0, 0, 127, 127, 127, 0, "Consola", name) { }

	virtual void update();
	virtual void draw();

};

