#pragma once

#include "PhysicsComponent.h"
#include "TransformComponent.h"

class BoxCollider : public PhysicsComponent
{
	private:
		SDL_Rect _collider;
		TransformComponent* _transform;

	public:
		BoxCollider(TransformComponent* trnsf) : _transform(trnsf) {}
		BoxCollider() {}

		void update()
		{
			_collider.x = _transform->getPosition().getX;
			_collider.y = _transform->getPosition().getY;
			_collider.w = _transform->getSize().getX * _transform->getScale().getX();
			_collider.h = _transform->getSize().getY * _transform->getScale().getY();
		}
};