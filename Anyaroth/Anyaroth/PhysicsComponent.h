#pragma once
#include "Component.h"

class GameComponent;

class PhysicsComponent : public virtual Component
{
public:
	PhysicsComponent(GameComponent* obj);
	virtual ~PhysicsComponent() {}
	virtual void update() = 0;
};