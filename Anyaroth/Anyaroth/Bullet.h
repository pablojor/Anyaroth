#pragma once
#include "GameComponent.h"
#include "Vector2D.h"

class Bullet : public GameComponent
{
public:
	Bullet(Texture* texture, Vector2D iniPos, Game* g, string tag);
	virtual ~Bullet();
};