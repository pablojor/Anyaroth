#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"

class Capsule : public GameObject
{
protected:
	TransformComponent* _transform = nullptr;
	BodyComponent* _body = nullptr;
	AnimatedSpriteComponent* _anim = nullptr;

	Player* _player = nullptr;
	Enemy* _father = nullptr;

	bool _spawning = false;

public:
	Capsule(Game* g, Player* player, Vector2D pos, Enemy* father);
	virtual ~Capsule() {}

	virtual void spawn() {};
	virtual void update(double deltaTime);
	virtual void beginCollision(GameObject* other, b2Contact* contact);
};