#pragma once

#include "PhysicsComponent.h"
#include "MovingComponent.h"
#include "AnimatedSpriteComponent.h"
#include "TransformComponent.h"
#include "MeleeComponent.h"

class GameComponent;
class Player;

class IAControllerComponent : public PhysicsComponent
{
	private:
		AnimatedSpriteComponent* _anim;
		MovingComponent* _movement = nullptr;
		TransformComponent* _myTransform = nullptr;
		TransformComponent* _playerTransform = nullptr;
		MeleeComponent* _meleeAttack = nullptr;

		bool _attacking = false;
	
	public:
		IAControllerComponent(GameComponent* obj);

		void addPlayer(Player* player);
		void addMelee();
		void noLongerAttacking() { _attacking = false; }
		virtual void update();
};