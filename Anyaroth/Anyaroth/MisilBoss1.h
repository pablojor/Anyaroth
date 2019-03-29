#pragma once
#include "GameObject.h"
#include "Boss1.h"

class PlayState;
class AnimatedSpriteComponent;
class TransformComponent;
class BodyComponent;

class MisilBoss1 : public GameObject
{
private:
	AnimatedSpriteComponent* _anim = nullptr;
	TransformComponent* _transform = nullptr;
	GameObject * _target = nullptr;
	BodyComponent* _body = nullptr;
	BodyComponent* _targetBody = nullptr;
	Vector2D _targetPos, _myPos, _velocity = Vector2D(25,25);
	double _angle = 0;


	PlayState* _play = nullptr;
	list<GameObject*>::iterator _itList;
public:
	MisilBoss1(GameObject* target, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag);
	virtual ~MisilBoss1();

	virtual void beginCollision(GameObject* other, b2Contact* contact);
	virtual void update(const double& deltaTime);
};