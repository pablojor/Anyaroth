#pragma once
#include "GameComponent.h"
#include <Box2D/Box2D.h>

class Enemy : public GameComponent
{
private:
	int life;
public:
	Enemy(Texture* texture, b2Vec2 posIni);
	virtual ~Enemy();

	void update();
};