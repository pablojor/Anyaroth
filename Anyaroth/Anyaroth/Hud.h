#pragma once
#include "GameComponent.h"
class Hud :
	public GameComponent
{
public:
	Hud(Texture* texture, Vector2D iniPos);
	virtual ~Hud();
};

