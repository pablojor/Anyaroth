#pragma once
#include "GameComponent.h"
#include <Box2D/Box2D.h>

class HUD : public GameComponent
{
public:
	HUD(Texture* texture, b2Vec2 iniPos);
	virtual ~HUD();
};