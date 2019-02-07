#pragma once

#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include "Vector2D.h"

class MovingComponent : public PhysicsComponent
{
	private:
		TransformComponent* _transform = nullptr;
		Vector2D _dir;

	public:
		MovingComponent(TransformComponent* trans, double x, double y) :
			_transform(trans), PhysicsComponent() { _dir = Vector2D(x, y); };

		double getDirX() { return _dir.getX(); }
		double getDirY() { return _dir.getY(); }
		void changeDir(double x, double y) { _dir = Vector2D(x, y); }

		virtual void update() 
		{
			Vector2D pos = _transform->getPosition();
			double x = pos.getX();
			double y = pos.getY();
			_transform->setPosition(_dir.getX() + x, _dir.getY() + y);
		}
};