#pragma once
#include "GameComponent.h"
#include <Box2D/Box2D.h>

class Bullet : public GameComponent
{
public:
	Bullet(Texture* texture, b2Vec2 iniPos, b2World* world);
	virtual ~Bullet();
};