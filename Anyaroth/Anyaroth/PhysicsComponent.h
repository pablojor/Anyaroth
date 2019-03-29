#pragma once
#include "Component.h"

class GameObject;

class PhysicsComponent : public virtual Component
{
public:
	PhysicsComponent(GameObject* obj);
	virtual ~PhysicsComponent() {}
	virtual void update(const double& deltaTime) = 0;
};