#include "Player.h"
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

	bool shouldJump = rgl::InputHandler::get()->isKeyDown(SDL_SCANCODE_UP) && m_pLevel->isTileAt((int)m_pLevel->toTileUnits(m_x), (int)m_pLevel->toTileUnits(m_y + 1) + 1);

	//if (rgl::InputHandler::get()->isKeyDown(SDL_SCANCODE_LEFT))
	//	setState(shouldJump ? JUMPING : WALKING, LEFT);
	//else if (rgl::InputHandler::get()->isKeyDown(SDL_SCANCODE_RIGHT))
	//	setState(shouldJump ? JUMPING : WALKING, RIGHT);
	//else
	//	setState(shouldJump ? JUMPING : STANDING, m_currentDirection);

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

void Player::registerPythonClass()
{
	rpl::Interpreter::get()->registerClass("Player",
		boost::python::class_<Player>("Player", boost::python::no_init)
		.def("setDirection", &Player::pySetDirection));
}

void Player::pySetDirection(std::string direction)
{
	if (direction == "LEFT")
		setState(WALKING, LEFT);
	else if (direction == "RIGHT")
		setState(WALKING, RIGHT);
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
			rgl::Debugger::get()->log("Standing");
			m_pBody->SetLinearVelocity(b2Vec2(0.0f, m_pBody->GetLinearVelocity().y));
			m_animator.setAnimation(0, 0.0f);
			break;
		case Player::WALKING:
			rgl::Debugger::get()->log("Walking");
			m_animator.setAnimation(4, 0.15f);
			break;
		case Player::JUMPING:
			rgl::Debugger::get()->log("Jumping");
			m_pBody->SetLinearVelocity(b2Vec2(m_pBody->GetLinearVelocity().x, -12.0f));
			break;
		}
		break;
	case RIGHT:
		switch (state)
		{
		case Player::STANDING:
			rgl::Debugger::get()->log("Standing");
			m_pBody->SetLinearVelocity(b2Vec2(0.0f, m_pBody->GetLinearVelocity().y));
			m_animator.setAnimation(0, 0.0f);
			break;
		case Player::WALKING:
			rgl::Debugger::get()->log("Walking");
			m_animator.setAnimation(4, 0.15f);
			break;
		case Player::JUMPING:
			rgl::Debugger::get()->log("Jumping");
			m_pBody->SetLinearVelocity(b2Vec2(m_pBody->GetLinearVelocity().x, -12.0f));
			break;
		}
		break;
	}

	m_currentState = state;
	m_currentDirection = direction;
}