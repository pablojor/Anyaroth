#pragma once

#include "PhysicsComponent.h"
#include "Bodycomponent.h"

class GameComponent;

class MovingComponent : public PhysicsComponent
{
	private:
		BodyComponent* _body;
		b2Vec2 _dir = b2Vec2(0.0f, 0.0f);
		double _speed = 100;

	public:
		MovingComponent(GameComponent* obj);
		~MovingComponent() {}

		virtual void update();

		double getDirX() { return _dir.x; }
		double getDirY() { return _dir.y; }
		void changeDir(double x, double y) { _dir = b2Vec2(x, y); }
};