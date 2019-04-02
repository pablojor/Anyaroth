#include "WeaponManager.h"
#include "Game.h"
#include "BasicPistol.h"
#include "BasicRifle.h"
#include "BasicShotgun.h"
#include "ImprovedRifle.h"
#include "ImprovedShotgun.h"
#include "BounceOrbCannon.h"


Gun* WeaponManager::getWeapon(Game* _game, GunType type)
{
	Gun* w = nullptr;
	switch (type)
	{
	case Pistol_Weapon:
		w = new BasicPistol(_game);
		break;
	case BasicShotgun_Weapon:
		w = new BasicShotgun(_game);
		break;
	case ImprovedShotgun_Weapon:
		w = new ImprovedShotgun(_game);
		break;
	case BasicRifle_Weapon:
		w = new BasicRifle(_game);
		break;
	case ImprovedRifle_Weapon:
		w = new ImprovedRifle(_game);
		break;
	case PlasmaSniper_Weapon:
		break;
	case BounceOrbCannon_Weapon:
		w = new BounceOrbCannon(_game);
		break;
	case GravitationalBombCannon_Weapon:
		break;
	case BasicEnemyGun_Weapon:
		break;
	case BasicEnemyShotgun_Weapon:
		break;
	default:
		break;
	}
	return w;
}