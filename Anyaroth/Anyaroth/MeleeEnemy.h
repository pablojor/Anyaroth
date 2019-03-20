#pragma once
#include "Enemy.h"

class MeleeEnemy : public Enemy
{
private:
	bool _attackingR = false, _attackingL = false;
	int _realRange = 15, _stopDmg = 1000;

public:
	MeleeEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag);
	virtual ~MeleeEnemy() {}
	virtual void update(double time);
};