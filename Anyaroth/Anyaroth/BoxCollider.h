#pragma once

#include "PhysicsComponent.h"
#include "TransformComponent.h"

class BoxCollider : public PhysicsComponent
{
	private:
		SDL_Rect collider;
		TransformComponent* transform;

	public:
		BoxCollider(TransformComponent* trnsf) : transform(trnsf) {}
		BoxCollider() {}

		void update()
		{
			collider.x = transform->getPosition().getX;
		}
};