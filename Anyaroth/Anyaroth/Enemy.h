#pragma once
#include "GameComponent.h"

class Player;

class AnimatedSpriteComponent;
class MovingComponent;
class TransformComponent;
class BodyComponent;


class Enemy : public GameComponent
{
private:
	int life;
protected:
	AnimatedSpriteComponent* _anim = nullptr;
	MovingComponent* _movement = nullptr;
	TransformComponent* _transform = nullptr;
	TransformComponent* _playerTransform = nullptr;
	BodyComponent* _body = nullptr;


	bool _attacking = false;

	double _time;
	int _vision, _flipRange, _attackRange, _attackTime, _life;

public:
	Enemy(Texture* texture,Vector2D posIni, Player* player, Game* g, string tag);
	virtual ~Enemy();

		virtual void update();
};