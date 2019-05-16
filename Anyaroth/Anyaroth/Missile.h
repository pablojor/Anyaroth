#pragma once
#include "GameObject.h"
#include "TransformComponent.h"
#include "BodyComponent.h"
#include "AnimatedSpriteComponent.h"

class Missile : public GameObject
{
private:
	TransformComponent* _transform = nullptr;
	BodyComponent* _body = nullptr;
	AnimatedSpriteComponent* _anim = nullptr;

	GameObject * _target = nullptr;
	BodyComponent* _targetBody = nullptr;

	Vector2D _targetPos, _myPos, _velocity = Vector2D(25,25);
	double _angle = 0;

public:
	Missile(Game* g, Vector2D pos, GameObject* target);
	virtual ~Missile() {}

	virtual void beginCollision(GameObject* other, b2Contact* contact);
	virtual void update(double deltaTime);
};