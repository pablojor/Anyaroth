#pragma once

#include "PhysicsComponent.h"
#include "TransformComponent.h"

class BoxCollider : public PhysicsComponent
{
	private:
		SDL_Rect _collider;
		TransformComponent* _transform;
		Vector2D _size;

	public:
		BoxCollider(TransformComponent* trnsf, Texture* text) : _transform(trnsf) { _size = Vector2D(text->getW(), text->getH()); }
		BoxCollider() {}

		SDL_Rect getCollider() { return _collider; }

		void update();
};