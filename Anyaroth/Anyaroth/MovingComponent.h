#pragma once

#include "PhysicsComponent.h"
#include "Bodycomponent.h"
#include "Game.h"
class GameComponent;

class MovingComponent : public PhysicsComponent
{
	private:
		BodyComponent* _body;
		b2Vec2 _dir = b2Vec2(0.0f, 0.0f);

		uint32 _dashTimer = 0, 
				_dashDur = 200;

		double _speed = 15,
				_jumpForce = 180,
				_gravScale = 3.5,
				_damping = 3.0;

		bool _dashing = false;
		

	public:
		MovingComponent(GameComponent* obj);
		~MovingComponent() {}

		virtual void update();

		double getDirX() { return _dir.x; }
		double getDirY() { return _dir.y; }
		void changeDir(double x, double y) { _dir = b2Vec2(x, y); }
		void changeDash(bool dash);
		bool isDashing() { return _dashing; }
};