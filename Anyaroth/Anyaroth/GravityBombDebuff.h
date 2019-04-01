#pragma once
#include "PhysicsComponent.h"
#include "GameObject.h"

class GravityBombDebuff :
	public PhysicsComponent
{
private:
	GameObject* _gravityZone = nullptr;
public:
	GravityBombDebuff(GameObject* obj, GameObject* gravityZone);
	virtual ~GravityBombDebuff();

	virtual void update(const double& deltaTime);
};

