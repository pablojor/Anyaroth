#include "Boss3.h"
#include "ImprovedRifle.h"

Boss3::Boss3(Game * g, Player * player, Vector2D pos, BulletPool * pool) : Boss(g, player, pos, pool, g->getTexture("EnemyMartyr")), Enemy(g, player, pos, g->getTexture("EnemyMartyr"))
{
	_life = 250; // Demo Guerrilla
	_life1 = _life2 = _life3 = _life;

	delete(_myGun);
	_myGun = new ImprovedRifle(g);
	_myGun->setMaxCadence(0);
	_myGun->setBulletSpeed(8);
	_myGun->setDamage(3);
}

Boss3::~Boss3()
{
}
