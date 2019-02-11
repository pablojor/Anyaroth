#pragma once

#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include "Texture.h"
#include "SDL.h"

class GameComponent;

class BoxCollider : public PhysicsComponent
{
	private:
		SDL_Rect _collider;

		TransformComponent* _transform = nullptr;

		Vector2D _size;
		Vector2D _offset;

	public:
		BoxCollider(GameComponent* obj);

		SDL_Rect getCollider() { return _collider; }
		void setOffset();

		void update();
};