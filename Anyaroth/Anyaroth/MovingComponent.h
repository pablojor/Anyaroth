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
		double _speed = 50, _jumpForce = 200;

	public:
		MovingComponent(GameComponent* obj);
		~MovingComponent() {}

		virtual void update();

		double getDirX() { return _dir.x; }
		double getDirY() { return _dir.y; }
		void changeDir(double x, double y) { _dir = b2Vec2(x, y); }
};