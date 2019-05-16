#include "BossSword.h"
#include "Game.h"

BossSword::BossSword(Game * game) : Sword(game)
{
	setIniAngle(270);
	setOffset({ 100, 0 });
	setCollisionFilters(PLAYER);
	setDamage(5);
	_speed = 4;
	setCollisionSize({ 50, 50 });
	_id = BossSword_Weapon;
}

BossSword::~BossSword() {}