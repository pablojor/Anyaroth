#pragma once

#include "PhysicsComponent.h"
#include "AnimatedSpriteComponent.h"

class GameComponent;
class IAControllerComponent;

class MeleeComponent : public PhysicsComponent
{
	private:
		AnimatedSpriteComponent* _anim;
		IAControllerComponent* _ia;

		double _time;
		bool _attacking = false;
	public:
		MeleeComponent(GameComponent* obj);
		~MeleeComponent() {};
		void attack();
		void stop();

		virtual void update();
};