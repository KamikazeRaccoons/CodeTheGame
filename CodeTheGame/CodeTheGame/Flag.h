#pragma once

#include <RGL.h>

class Flag : public rgl::PhysicsObject
{
public:
	
	Flag(int x, int y, int width, int height, std::string textureID, std::string name = "(unnamed Flag)")
		: rgl::PhysicsObject(x, y, width, height, b2_staticBody, textureID, name) { }

	virtual void onCreate();
	virtual void onDestroy();

	virtual void update();
	virtual void draw();

};

class FlagCreator : public rgl::ObjectCreator
{
	virtual std::shared_ptr<rgl::GameObject> createObject(const std::shared_ptr<rgl::ObjectParams> pObjectParams, std::string name) const
	{
		return std::make_shared<Flag>(pObjectParams->getIntParam("x"), pObjectParams->getIntParam("y"),
			pObjectParams->getIntParam("width"), pObjectParams->getIntParam("height"), pObjectParams->getStringParam("textureID"),
			name);
	}
};

