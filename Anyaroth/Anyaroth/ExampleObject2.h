#pragma once
#include "GameComponent.h"

class ExampleObject2 : public GameComponent
{
public:
	ExampleObject2(Vector2D pos, Texture* texture);
	~ExampleObject2() {}

	void update();
};
