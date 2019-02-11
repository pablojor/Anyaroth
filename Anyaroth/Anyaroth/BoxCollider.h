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
		Vector2D _scale = Vector2D (1, 1);
		Vector2D _offset = Vector2D (0, 0);

	public:
		BoxCollider(GameComponent* obj);

		void update();

		SDL_Rect getCollider() { return _collider; }
		void setScale(double x, double y) { _scale = Vector2D(x, y); }
		void setOffset(double x, double y) { _offset = Vector2D(x, y); }
};