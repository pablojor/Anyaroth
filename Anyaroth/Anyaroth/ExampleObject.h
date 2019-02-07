#pragma once
#include "GameComponent.h"

class ExampleObject : public GameComponent {
public:
	ExampleObject(TextureComponent* texture);
	~ExampleObject();

	void update();
};

