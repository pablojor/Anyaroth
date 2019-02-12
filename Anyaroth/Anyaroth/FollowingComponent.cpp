#include "FollowingComponent.h"
#include "GameComponent.h"


FollowingComponent::FollowingComponent(GameComponent* obj, GameComponent* other) : PhysicsComponent(obj)
{
	_transformOther = other->getComponent<TransformComponent>();
	_transform = obj->getComponent<TransformComponent>();
	
	_offset = {0,0};//_transformOther->getPosition() - _transform->getPosition();
}


FollowingComponent::~FollowingComponent()
{

}

void FollowingComponent::update()
{
	double x = _transformOther->getPosition().getX() + _offset.getX();
	double y = _transformOther->getPosition().getY() + _offset.getY();

	_transform->setPosition(x,y);
}
