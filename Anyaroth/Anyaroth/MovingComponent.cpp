#include "MovingComponent.h"
#include "GameComponent.h"

MovingComponent::MovingComponent(GameComponent* obj) : PhysicsComponent(obj)
{
	_transform = obj->getComponent<TransformComponent>();
	if (_transform == nullptr) _transform = obj->addComponent<TransformComponent>();
	/*_anim = obj->getComponent<AnimatedSpriteComponent>();
	if (_anim == nullptr) _anim = obj->addComponent<AnimatedSpriteComponent>();*/
}

void MovingComponent::update() 
{
	Vector2D pos = _transform->getPosition();
	double x = pos.getX();
	double y = pos.getY();
	_transform->setPosition(_dir.getX()*_speed + x, _dir.getY()*_speed + y);


}