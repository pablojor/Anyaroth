#include "MeleeWeapon.h"



MeleeWeapon::MeleeWeapon(Game* g, double w, double h, double damage, int type) : _damage(damage), _type(type), GameComponent(g)
{
	_size = Vector2D(w, h);
}


MeleeWeapon::~MeleeWeapon()
{
	if (_melee != nullptr)
		delete _melee;
}

void MeleeWeapon::MeleeAttack(int dir, double x, double y, Vector2D center)
{
	_melee = new MeleeBox(getGame(), x, y, _size.getX(), _size.getY(), _damage, center, dir, _type);
}

void MeleeWeapon::update()
{
	if (_melee != nullptr)
		_melee->update();
}

void MeleeWeapon::endMelee()
{
	delete _melee;
	_melee = nullptr;
}


