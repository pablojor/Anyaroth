#pragma once
#include "Component.h"

class GameObject;

class PhysicsComponent : public virtual Component
{
public:
	PhysicsComponent(GameObject* obj);
	virtual ~PhysicsComponent() {}
	virtual void update(double deltaTime) = 0;
};