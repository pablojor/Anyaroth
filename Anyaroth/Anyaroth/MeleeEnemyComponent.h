#pragma once

#include "PhysicsComponent.h"
#include "MovingComponent.h"
#include "AnimatedSpriteComponent.h"
#include "TransformComponent.h"

class GameComponent;
class Player;

class MeleeEnemyComponent : public PhysicsComponent
{
	private:
		AnimatedSpriteComponent* _anim;
		MovingComponent* _movement = nullptr;
		TransformComponent* _myTransform = nullptr;
		TransformComponent* _playerTransform = nullptr;

		bool _attacking = false;
		double _time;
		int _vision = 300, _flipRange = 40, _attackRange = 100, _attackTime = 1500;
	
	public:
		MeleeEnemyComponent(GameComponent* obj);

		void addPlayer(Player* player);
		void noLongerAttacking() { _attacking = false; }
		virtual void update();
};