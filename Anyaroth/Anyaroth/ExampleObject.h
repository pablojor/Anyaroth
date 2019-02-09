#pragma once

#include "GameComponent.h"

class ExampleObject : public GameComponent {
public:
	ExampleObject(Texture* texture);
	~ExampleObject();

	void update();
};

