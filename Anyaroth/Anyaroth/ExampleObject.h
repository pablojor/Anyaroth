#pragma once
#include "GameComponent.h"

class ExampleObject : public GameComponent 
{
	public:
		ExampleObject(Vector2D pos, Texture* texture);
		~ExampleObject() {}

		void update();
};

