#pragma once
#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include <Box2D/Box2D.h>

class BodyComponent : public PhysicsComponent
{
private:
	b2World* _world;
	b2Body* _body = nullptr;
	b2FixtureDef _fixture;
	TransformComponent* _transform;
	double textW, textH, aX, aY;
public:
	BodyComponent(GameComponent* obj);
	virtual ~BodyComponent();

	virtual void update();
	b2Body* getBody();
};