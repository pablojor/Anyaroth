#pragma once
#include "PhysicsComponent.h"
#include <Box2D/Box2D.h>

class BodyComponent : public PhysicsComponent
{
private:
	b2World* _world = new b2World(b2Vec2(0, 0));
	b2BodyDef _bodydef;
	b2BodyType _bodyType = b2_staticBody;
	b2Vec2 _position = b2Vec2(0, 0);
	float32 _angle = 0.0f;
	b2Body* _body = nullptr;

public:
	BodyComponent(GameComponent* obj);
	virtual ~BodyComponent();

	virtual void update();
	b2BodyDef getBodyDef();
	b2Body* getBody();
};