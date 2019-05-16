#include "MovingComponent.h"
#include "GameObject.h"
#include <iostream>

MovingComponent::MovingComponent(GameObject* obj) : PhysicsComponent(obj)
{
	_body = obj->getComponent<BodyComponent>();
	_body->getBody()->SetLinearDamping(_damping);
	_body->getBody()->SetGravityScale(_gravScale);
}

void MovingComponent::update(double deltaTime) 
{
	b2Vec2 pos = _body->getBody()->GetPosition();
	double x = pos.x;
	double y = pos.y;

	_body->getBody()->SetLinearVelocity(b2Vec2(_dir.x*_speed, _body->getBody()->GetLinearVelocity().y));

	/*if (!_dashing)
	{
		if (((_body->getBody()->GetLinearVelocity().x > _speed || _body->getBody()->GetLinearVelocity().x < -1 * _speed) && _dir.x != 0) && _body->getBody()->GetLinearVelocity().x / _dir.x != -abs(_body->getBody()->GetLinearVelocity().x))
			_body->getBody()->SetLinearVelocity(b2Vec2(_dir.x*_speed, _body->getBody()->GetLinearVelocity().y));
		else
			_body->getBody()->ApplyLinearImpulse(b2Vec2(_dir.x*_speed * 2, 0), _body->getBody()->GetWorldCenter(), true);

		_body->getBody()->ApplyLinearImpulse(b2Vec2(0, _dir.y*_jumpForce), _body->getBody()->GetWorldCenter(), true);
	}
	else
	{
		if (_dir.y == 0)
		{
			if (SDL_GetTicks() < (_dashTimer + _dashDur))
				_body->getBody()->SetLinearVelocity(b2Vec2(_dir.x*_speed * 2.5, _dir.y*_speed * 2));
			else
			{
				_body->getBody()->SetLinearVelocity(b2Vec2(_dir.x*_speed *0.8, _dir.y*_speed * 0.8));
				changeDash(false);
			}
		}
		else
			_body->getBody()->SetLinearVelocity(b2Vec2(_dir.x*_speed * 2, _dir.y*_speed * 2));
	}*/
}

void MovingComponent::changeDash(bool dash)
{
	_dashing = dash;
	if (!dash)
	{
		_body->getBody()->SetGravityScale(_gravScale);
		_body->getBody()->SetLinearDamping(_damping);
	}
	else
	{
		_dashTimer = SDL_GetTicks();
		_body->getBody()->SetGravityScale(0);
		_body->getBody()->SetLinearDamping(0);
	}
}