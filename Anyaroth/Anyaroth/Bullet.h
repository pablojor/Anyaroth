#pragma once

#include "GameComponent.h"

class Bullet : public GameComponent
{
public:
	Bullet(Texture* texture, Vector2D iniPos);
	virtual ~Bullet();

	
};

