#pragma once

#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include "Vector2D.h"

class MovingComponent : public PhysicsComponent
{
	private:
		TransformComponent* _transform = nullptr;
		Vector2D _dir;

		double _velocity;

	public:
		MovingComponent(TransformComponent* trans, Vector2D dir, double velocity) :
			_transform(trans), _dir(dir), _velocity(velocity), PhysicsComponent() {};

		double getDirX() { return _dir.getX(); }
		double getDirY() { return _dir.getY(); }
		void changeDir(double x, double y) { _dir = Vector2D(x, y); }

		virtual void update();
};