#include "MovingComponent.h"
#include "GameComponent.h"

MovingComponent::MovingComponent(GameComponent* obj) : PhysicsComponent(obj)
{
	_body = obj->getComponent<BodyComponent>();
	if (_body == nullptr) _body = obj->addComponent<BodyComponent>();
	/*_anim = obj->getComponent<AnimatedSpriteComponent>();
	if (_anim == nullptr) _anim = obj->addComponent<AnimatedSpriteComponent>();*/
}

void MovingComponent::update() 
{
	b2Vec2 pos = _body->getBody()->GetPosition();
	double x = pos.x;
	double y = pos.y;
	_body->getBody()->ApplyLinearImpulse(b2Vec2(_dir.x*_speed, _dir.y*_speed), _body->getBody()->GetLocalCenter(),true);
	//_body->getBody()->SetTransform(b2Vec2(_dir.x*_speed + x, _dir.y*_speed + y + _gravity), _body->getBody()->GetAngle());
}