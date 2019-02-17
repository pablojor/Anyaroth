#pragma once
#include "GameComponent.h"
#include "Vector2D"

class Bullet : public GameComponent
{
public:
	Bullet(Texture* texture, Vector2D iniPos, Game* g);
	virtual ~Bullet();
};