#include "Flag.h"

void Flag::onCreate()
{
	rgl::PhysicsObject::onCreate();

	b2PolygonShape shape;
	shape.SetAsBox(m_pLevel->toTileUnits(m_width / 2), m_pLevel->toTileUnits(m_height / 2));

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.isSensor = true;
	
	addFixture(&fixtureDef);
}

void Flag::onDestroy()
{
	rgl::PhysicsObject::onDestroy();
}

void Flag::update()
{
	rgl::PhysicsObject::update();
}

void Flag::draw()
{
	rgl::PhysicsObject::draw();
}