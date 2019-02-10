#pragma once
#include "GameComponent.h"
class Collectable : public GameComponent
{
	public:
		Collectable(Texture* texture, Vector2D iniPos);
		virtual ~Collectable();
};

