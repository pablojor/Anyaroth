#pragma once

#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include "Vector2D.h"

class MovingComponent : public PhysicsComponent
{
	private:
		TranformComponent* transform;
		Vector2D dir;

	public:
		MovingComponent(double x, double y) :
			MovingComponent::PhysicsComponent() { };

		void getDirX() {}
		void getDirY() {}
		void changeDirX() {}
		void changeDirY() {}

		virtual void update() 
		{
			transform->x(dir.getX() + transform->getX());  transform->y(dir.getY() + transform->getY());
		}
};