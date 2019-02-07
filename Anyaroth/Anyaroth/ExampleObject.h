#pragma once
#include "GameComponent.h"
#include "BoxCollider.h"

class ExampleObject : public GameComponent 
{
	public:
		ExampleObject(Vector2D pos, Texture* texture);
		~ExampleObject() {}

		void update();
};

