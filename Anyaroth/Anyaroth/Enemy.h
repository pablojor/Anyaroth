#pragma once
#include "GameComponent.h"

class Player;

class AnimatedSpriteComponent;
class MovingComponent;
class TransformComponent;
class BodyComponent;


class Enemy : public GameComponent
{
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
		Enemy(Player* player, Game* g, Texture* texture,Vector2D posIni);
		virtual ~Enemy() {}

		virtual void update();
};