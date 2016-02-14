#pragma once

#include <RGL.h>

class Player : public rgl::PhysicsObject
{
private:

	enum PlayerDirection
	{
		LEFT = 0,
		RIGHT = 1
	} m_currentDirection = RIGHT;

	enum PlayerState
	{
		STANDING = 0,
		WALKING = 1,
		JUMPING = 2
	} m_currentState = STANDING;

	Animator m_animator;

	void setState(PlayerState state, PlayerDirection direction);

public:

	Player(int x, int y, int width, int height, std::string textureID, std::string name = "(unnamed Player)") :
		rgl::PhysicsObject(x, y, width, height, b2_dynamicBody, textureID, name) { }

	virtual void onCreate();
	virtual void onDestroy();

	virtual void update();
	virtual void draw();

	static void registerPythonClass();

	void pySetDirection(std::string direction);
	void pyJump();
};

class PlayerCreator : public rgl::ObjectCreator
{
	virtual std::shared_ptr<rgl::GameObject> createObject(const std::shared_ptr<rgl::ObjectParams> pObjectParams, std::string name) const
	{
		return std::make_shared<Player>(pObjectParams->getIntParam("x"), pObjectParams->getIntParam("y"),
			pObjectParams->getIntParam("width"), pObjectParams->getIntParam("height"), pObjectParams->getStringParam("textureID"),
			name);
	}
};
