#pragma once
#include "GameComponent.h"

class ExampleObject : public GameComponent {
public:
	ExampleObject(TextureComponent* texture, unsigned int width, unsigned int height);
	~ExampleObject();
};

