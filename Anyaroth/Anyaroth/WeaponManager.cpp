#include "WeaponManager.h"
#include "Game.h"
#include "BasicPistol.h"
#include "BasicRifle.h"
#include "BasicShotgun.h"
#include "ImprovedRifle.h"
#include "ImprovedShotgun.h"
#include "BounceOrbCannon.h"


WeaponManager::WeaponManager(Game* g) : _game(g)
{
}


WeaponManager::~WeaponManager()
{
	for (Gun* gun : _equippedWeapons)
	{
		if (gun != nullptr) //destruye el arma que había antes
			delete gun;
		gun = nullptr;
	}
}


Gun* WeaponManager::getWeapon(GunType type, int slotIndex)
{
	if(_equippedWeapons[slotIndex] != nullptr) //destruye el arma que había antes
		delete _equippedWeapons[slotIndex];

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

	_equippedWeapons[slotIndex] = w;
	return w;
}