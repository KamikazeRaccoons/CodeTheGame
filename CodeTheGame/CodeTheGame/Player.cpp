#include "Player.h"

void Player::onCreate()
{
	rgl::PhysicsObject::onCreate();

	b2PolygonShape shape;
	shape.SetAsBox(m_pLevel->toTileUnits(m_width / 2), m_pLevel->toTileUnits(m_height / 2));

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.4f;
	
	addFixture(&fixtureDef);

	m_animator.addAnimation(4, 0.15f);
	m_animator.addAnimation(4, 0.15f);
	m_animator.addAnimation(4, 0.15f);
	m_animator.addAnimation(4, 0.15f);

	m_animator.setAnimation(1);
}

void Player::onDestroy()
{
	rgl::PhysicsObject::onDestroy();
}

void Player::update()
{
	rgl::PhysicsObject::update();

	m_animator.update();
}

void Player::draw()
{
	rgl::TextureManager::get()->drawFrame(m_textureID, m_x, m_y, m_width, m_height, m_animator.getCurrentRow(), m_animator.getCurrentFrame(), 255,
		rgl::MathHelper::toDeg(m_pBody->GetAngle()));
}