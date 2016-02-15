#include "Player.h"
#include "Flag.h"
#include "LevelPassed.h"
#include <RPL.h>

void Player::onCreate()
{
	rgl::PhysicsObject::onCreate();

	m_pBody->SetFixedRotation(true);

	b2PolygonShape shape;
	shape.SetAsBox(m_pLevel->toTileUnits(m_width / 2), m_pLevel->toTileUnits(m_height / 2));

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.0f;
	
	addFixture(&fixtureDef);

	m_animator.setAnimation(0, 0.0f);

	rpl::Interpreter::get()->addObject(m_name, this);
}

void Player::onDestroy()
{
	rgl::PhysicsObject::onDestroy();
}

void Player::update()
{
	rgl::PhysicsObject::update();

	if (m_currentState != STANDING)
	{
		switch (m_currentDirection)
		{
		case Player::LEFT:
			if (m_pBody->GetLinearVelocity().x > -5.0f)
				m_pBody->ApplyForce(b2Vec2(-100.0f, 0.0f), m_pBody->GetWorldCenter(), true);
			break;
		case Player::RIGHT:
			if (m_pBody->GetLinearVelocity().x < 5.0f)
				m_pBody->ApplyForce(b2Vec2(100.0f, 0.0f), m_pBody->GetWorldCenter(), true);
			break;
		}
	}

	m_animator.update();
}

void Player::draw()
{
	rgl::TextureManager::get()->drawFrame(m_textureID, m_x, m_y, m_width, m_height, 1, m_animator.getCurrentFrame(), 255,
		rgl::MathHelper::toDeg(m_pBody->GetAngle()), 0,
		m_currentDirection == LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);

	SDL_Rect rect;
	rect.x = m_x;
	rect.y = m_y + 32;
	rect.w = 32;
	rect.h = 32;
}

void Player::onBeginContact(rgl::Vector2 contactPosition, PhysicsObject* pPhysicsObject)
{
	if (pPhysicsObject != 0 && !m_levelComplete)
	{
		if (dynamic_cast<Flag*>(pPhysicsObject))
		{
			m_levelComplete = true;
			m_pLevel->addObject(std::make_shared<LevelPassed>(464, 55, m_currentLevel + 1, "LevelPassedObject"));
			rgl::SoundManager::get()->playSound("FlagHit", 0);
		}
		else
		{
			m_collidingObjects.push_back(pPhysicsObject);
		}
	}
}

void Player::onEndContact(rgl::Vector2 contactPosition, PhysicsObject* pPhysicsObject)
{
	std::remove(m_collidingObjects.begin(), m_collidingObjects.end(), pPhysicsObject);
}

void Player::registerPythonClass()
{
	rpl::Interpreter::get()->registerClass("Player",
		boost::python::class_<Player>("Player", boost::python::no_init)
		.def("setDirection", &Player::pySetDirection)
		.def("getDirection", &Player::pyGetDirection)
		.def("jump", &Player::pyJump)
		.def("relativeBlockAt", &Player::pyRelativeBlockAt)
		.def("relativeObjectAt", &Player::pyIsCollidingWithObject));
}

void Player::pySetDirection(std::string direction)
{
	if (direction == "LEFT")
		setState(WALKING, LEFT);
	else if (direction == "RIGHT")
		setState(WALKING, RIGHT);
}

std::string Player::pyGetDirection()
{
	return m_currentDirection == LEFT ? "LEFT" : "RIGHT";
}

void Player::pyJump()
{
	if (m_pLevel->isTileAt((int)m_pLevel->toTileUnits(m_x), (int)m_pLevel->toTileUnits(m_y + 1) + 1))
	{
		m_pBody->SetLinearVelocity(b2Vec2(m_pBody->GetLinearVelocity().x, -12.0f));
		rgl::SoundManager::get()->playSound("PlayerJump", 0);
	}
}

bool Player::pyRelativeBlockAt(int relative_x, int relative_y)
{
	return m_pLevel->isTileAt((int)m_pLevel->toTileUnits(m_x + relative_x * m_pLevel->getTileSize() + m_pLevel->getTileSize() / 2),
		(int)m_pLevel->toTileUnits(m_y + relative_y * m_pLevel->getTileSize() + m_pLevel->getTileSize() / 2));
}

bool Player::pyIsCollidingWithObject()
{
	return m_collidingObjects.size() > 0;
}

void Player::setState(PlayerState state, PlayerDirection direction)
{
	if (m_currentState == state && m_currentDirection == direction)
		return;

	switch (direction)
	{
	case LEFT:
		switch (state)
		{
		case Player::STANDING:
			m_pBody->SetLinearVelocity(b2Vec2(0.0f, m_pBody->GetLinearVelocity().y));
			m_animator.setAnimation(0, 0.0f);
			break;
		case Player::WALKING:
			m_animator.setAnimation(4, 0.15f);
			break;
		}
		break;
	case RIGHT:
		switch (state)
		{
		case Player::STANDING:
			m_pBody->SetLinearVelocity(b2Vec2(0.0f, m_pBody->GetLinearVelocity().y));
			m_animator.setAnimation(0, 0.0f);
			break;
		case Player::WALKING:
			m_animator.setAnimation(4, 0.15f);
			break;
		}
		break;
	}

	m_currentState = state;
	m_currentDirection = direction;
}