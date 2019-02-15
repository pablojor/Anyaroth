#pragma once
#include "GameComponent.h"
#include <Box2D/Box2D.h>

class Collectable : public GameComponent
{
	public:
		Collectable(Texture* texture, b2Vec2 iniPos, Game* g);
		virtual ~Collectable() {}
};