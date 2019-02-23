#include "MovingComponent.h"
#include "GameComponent.h"
#include <iostream>

MovingComponent::MovingComponent(GameComponent* obj) : PhysicsComponent(obj)
{
	_body = obj->getComponent<BodyComponent>();
	if (_body == nullptr) _body = obj->addComponent<BodyComponent>();
	/*_anim = obj->getComponent<AnimatedSpriteComponent>();
	if (_anim == nullptr) _anim = obj->addComponent<AnimatedSpriteComponent>();*/
	_body->getBody()->SetLinearDamping(1.5);
}

void MovingComponent::update() 
{
	b2Vec2 pos = _body->getBody()->GetPosition();
	double x = pos.x;
	double y = pos.y;
	//_body->getBody()->SetLinearVelocity(b2Vec2(_dir.x*_speed, _body->getBody()->GetLinearVelocity().y));
	if (!_dashing)
	{
		if (((_body->getBody()->GetLinearVelocity().x > _speed || _body->getBody()->GetLinearVelocity().x < -1 * _speed) && _dir.x != 0) && _body->getBody()->GetLinearVelocity().x / _dir.x != -abs(_body->getBody()->GetLinearVelocity().x))
		{

			_body->getBody()->SetLinearVelocity(b2Vec2(_dir.x*_speed, _body->getBody()->GetLinearVelocity().y));
		}
		else
			_body->getBody()->ApplyLinearImpulse(b2Vec2(_dir.x*_speed * 2, 0), _body->getBody()->GetWorldCenter(), true);
		_body->getBody()->ApplyLinearImpulse(b2Vec2(0, _dir.y*_jumpForce), _body->getBody()->GetWorldCenter(), true);
	}
	else
	{
		_body->getBody()->SetLinearVelocity(b2Vec2(_dir.x*_speed * 2, _dir.y*_speed * 2));
	}
	
}

void MovingComponent::changeDash(bool dash) {
	_dashing = dash;
	if (!dash)
	{
		_body->getBody()->SetType(b2_dynamicBody);
		_body->getBody()->SetLinearDamping(1.5);
	}
	else
	{
		_body->getBody()->SetType(b2_kinematicBody);
		_body->getBody()->SetLinearDamping(0);
	}
}