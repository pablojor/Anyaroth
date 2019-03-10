#pragma once
#include "GameComponent.h"
#include "MeleeBox.h"
class MeleeWeapon :	public GameComponent
{
protected:
	MeleeBox* _melee= nullptr;
public:
	MeleeWeapon(Game* g);
	~MeleeWeapon();
	void MeleeAttack (double x, double y, double w, double h, double damage, Vector2D center, int dir, int type);
	void update();
	void endMelee();
};

