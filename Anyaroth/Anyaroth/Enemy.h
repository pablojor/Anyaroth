#pragma once
#include "GameComponent.h"
class Enemy : public GameComponent
{
private:
	int life;
public:
	Enemy(Texture* texture,Vector2D posIni);
	virtual ~Enemy();

	void update();
};

