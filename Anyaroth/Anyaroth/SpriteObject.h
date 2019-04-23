#pragma once
#include "GameObject.h"
#include "SpriteComponent.h"
#include "Game.h"

class SpriteObject : public GameObject
{
	public:
		SpriteObject(Game* g, Texture* texture, Vector2D iniPos);
		virtual ~SpriteObject();

		void render(Camera* c) const
		{
			GameObject::render(c);
		}
};

