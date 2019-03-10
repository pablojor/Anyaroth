#include "MeleeWeapon.h"



MeleeWeapon::MeleeWeapon(Game* g) : GameComponent(g){}


MeleeWeapon::~MeleeWeapon()
{
	if (_melee != nullptr)
		endMelee();
}

void MeleeWeapon::MeleeAttack(double x, double y, double w, double h, double damage, Vector2D center, int dir, int type)
{
	_melee = new MeleeBox(getGame(), x, y, w, h, damage, center, dir, type);
}

void MeleeWeapon::update()
{
	if (_melee != nullptr)
	{
		_melee->update();
	}
}

void MeleeWeapon::endMelee()
{
	delete _melee;
	_melee = nullptr;
}


