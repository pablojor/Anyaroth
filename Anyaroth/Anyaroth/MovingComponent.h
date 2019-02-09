#pragma once

#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include "Vector2D.h"

class GameComponent;

class MovingComponent : public PhysicsComponent
{
	private:
		TransformComponent* _transform;
		Vector2D _dir = Vector2D(0, 1);;

	public:
		MovingComponent(GameComponent* obj);

		double getDirX() { return _dir.getX(); }
		double getDirY() { return _dir.getY(); }
		void changeDir(double x, double y) { _dir = Vector2D(x, y); }

		virtual void update();
};