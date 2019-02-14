#include "PhysicsComponent.h"
#include "GameComponent.h"

PhysicsComponent::PhysicsComponent(GameComponent* obj) 
{
	obj->addPhysicsComponent(this);
}

PhysicsComponent::~PhysicsComponent() 
{

}