#include "PhysicsComponent.h"
#include "GameObject.h"

PhysicsComponent::PhysicsComponent(GameObject* obj) 
{
	obj->addPhysicsComponent(this);
}