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
	} m_currentState = STANDING;

	Animator m_animator;

	bool m_levelComplete;
	int m_currentLevel;

	void setState(PlayerState state, PlayerDirection direction);

public:

	Player(int x, int y, int width, int height, int currentLevel, std::string textureID, std::string name = "(unnamed Player)") :
		rgl::PhysicsObject(x, y, width, height, b2_dynamicBody, textureID, name), m_levelComplete(false), m_currentLevel(currentLevel) { }

	virtual void onCreate();
	virtual void onDestroy();

	virtual void update();
	virtual void draw();

	virtual void onBeginContact(rgl::Vector2 contactPosition, PhysicsObject* pPhysicsObject);

	static void registerPythonClass();

	void pySetDirection(std::string direction);
	void pyJump();
	bool pyRelativeBlockAt(int relative_x, int relative_y);
};

class PlayerCreator : public rgl::ObjectCreator
{
	virtual std::shared_ptr<rgl::GameObject> createObject(const std::shared_ptr<rgl::ObjectParams> pObjectParams, std::string name) const
	{
		return std::make_shared<Player>(pObjectParams->getIntParam("x"), pObjectParams->getIntParam("y"),
			pObjectParams->getIntParam("width"), pObjectParams->getIntParam("height"), pObjectParams->getIntParam("currentLevel"),
			pObjectParams->getStringParam("textureID"), name);
	}
};
