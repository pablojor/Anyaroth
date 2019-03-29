#include "MisilBoss1.h"
#include "TransformComponent.h"
#include "BodyComponent.h"
#include "AnimatedSpriteComponent.h"
#include "Game.h"

MisilBoss1::MisilBoss1(GameObject* target, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag) : _target(target), _play(play), GameObject(g, tag)
{
	addComponent<Texture>(texture);

	_transform = addComponent<TransformComponent>();
	_transform->setPosition(posIni.getX(), posIni.getY());

	_body = addComponent<BodyComponent>();
	_body->getBody()->SetType(b2_kinematicBody);
	_body->getBody()->SetBullet(true);

	_body->setW(20);
	_body->setH(20);
	_body->filterCollisions(MISIL, ENEMIES);

	_body->getBody()->SetFixedRotation(true);

	_anim = addComponent<AnimatedSpriteComponent>();

	_targetBody = _target->getComponent<BodyComponent>();
	
	_targetPos = Vector2D(_targetBody->getBody()->GetPosition().x * M_TO_PIXEL, _targetBody->getBody()->GetPosition().y * M_TO_PIXEL);
	_myPos = Vector2D(_body->getBody()->GetPosition().x  * M_TO_PIXEL, _body->getBody()->GetPosition().y  * M_TO_PIXEL);

	_angle = atan2(_targetPos.getY() - _myPos.getY(), _targetPos.getX() - _myPos.getX()) * 180 / M_PI;
}


MisilBoss1::~MisilBoss1()
{
}

void MisilBoss1::beginCollision(GameObject * other, b2Contact * contact)
{
	contact->SetEnabled(false);
	setActive(false);
	_body->getBody()->SetLinearVelocity(b2Vec2(0, 0));
	destroy();
}

void MisilBoss1::update(const double& deltaTime)
{
	GameObject::update(deltaTime);
	if (isActive())
	{
		
		_targetPos = Vector2D(_targetBody->getBody()->GetPosition().x * M_TO_PIXEL, _targetBody->getBody()->GetPosition().y * M_TO_PIXEL);
		_myPos = Vector2D(_body->getBody()->GetPosition().x  * M_TO_PIXEL, _body->getBody()->GetPosition().y  * M_TO_PIXEL);
		//double myX = _myPos.getX(), myY = _myPos.getY(), x=_targetPos.getX(), y = _targetPos.getY(), velX =_velocity.getX(), velY = _velocity.getY();

		//if (myX<x && myX - x>0.01)
		//{
		//	myX -= 0.01 ;
		//}
		//else if (myX > x && myX - x < -0.01)
		//	myX += 0.01;
		//else
		//	myX -= (myX - x)/10;

		//if (myY<y && myY - y>0.01)
		//{
		//	myY -= 0.01;
		//}
		//else if (myY > y && myY - y < -0.01)
		//	myY += 0.01 ;
		//else
		//	myY -= (myY - y)/10;
		//_body->getBody()->SetTransform(b2Vec2(myX / M_TO_PIXEL, myY / M_TO_PIXEL), 0);

		//Forma con el angulo peta a veces
		_angle = atan2(_targetPos.getY() - _myPos.getY(), _targetPos.getX() - _myPos.getX()) * 180 / M_PI;

		if (_targetPos.distance(_myPos) < _velocity.distance(Vector2D()) * 2)
			_velocity = {_velocity.getX() / 2, _velocity.getY() / 2};
		
		_body->getBody()->SetLinearVelocity(b2Vec2(_velocity.getX() * cos(_angle), _velocity.getY() * sin(_angle)));
		//_transform->setPosition(Vector2D(_body->getBody()->GetPosition().x * 8, _body->getBody()->GetPosition().y * 8));
		_transform->setRotation(_angle);
	}
}