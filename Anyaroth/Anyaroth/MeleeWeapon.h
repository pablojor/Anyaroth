#pragma once
#include "GameComponent.h"
#include "MeleeBox.h"
class MeleeWeapon :	public GameComponent
{
protected:
	Vector2D  _size, _center;
	int _type;
	double _damage;
	MeleeBox* _melee= nullptr;
public:
	MeleeWeapon(Game* g, double w, double h, double damage, int type = 0);
	~MeleeWeapon();
	void MeleeAttack(int dir, double x, double y, Vector2D center);
	void update();
	void endMelee();
};

