#pragma once
#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include "BodyComponent.h"
#include "Texture.h"
#include "SDL.h"


class GameComponent;

class BoxCollider : public PhysicsComponent
{
	private:
		SDL_Rect _collider;
		TransformComponent* _transform;
		BodyComponent* _body;
		Texture* _text;
		Vector2D _size;

	public:
		BoxCollider(GameComponent* obj);

		SDL_Rect getCollider() { return _collider; }

		void update();
};