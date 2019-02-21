#include "MovingComponent.h"
#include "GameComponent.h"
#include <iostream>

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
	//_body->getBody()->SetLinearVelocity(b2Vec2(_dir.x*_speed, _body->getBody()->GetLinearVelocity().y));
	
	if (((_body->getBody()->GetLinearVelocity().x > _speed || abs(_body->getBody()->GetLinearVelocity().x) < -1*_speed) && _dir.x != 0)&& _body->getBody()->GetLinearVelocity().x/_dir.x!=-abs(_body->getBody()->GetLinearVelocity().x))
	{

		_body->getBody()->SetLinearVelocity(b2Vec2(_dir.x*_speed, _body->getBody()->GetLinearVelocity().y));
	}
	else
		_body->getBody()->ApplyLinearImpulse(b2Vec2(_dir.x*_speed*3, 0), _body->getBody()->GetWorldCenter(), true);
	_body->getBody()->ApplyLinearImpulse(b2Vec2(0, _dir.y*_jumpForce), _body->getBody()->GetWorldCenter(), true);
	
}