#pragma once
#include "Enemy.h"

class FlyingEnemy :	public Enemy
{
private: 
	double oY;
public:
	FlyingEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag);
	virtual ~FlyingEnemy();
	void update(double time);
};

