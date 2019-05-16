#include "WeaponManager.h"
#include "Game.h"
#include "BasicPistol.h"
#include "BasicRifle.h"
#include "BasicShotgun.h"
#include "ImprovedRifle.h"
#include "ImprovedShotgun.h"
#include "BounceOrbCannon.h"
#include "GravityBombCannon.h"
#include "PlasmaSniper.h"

#include "Melee.h"
#include "Knife.h"
#include "Sword.h"
#include "PoleAxe.h"

#include <json.hpp>
#include <map>

WeaponManager WeaponManager::_instance;
bool WeaponManager::_initilized = false;
map<GunType, GunInfo> WeaponManager::_weaponInfo;
map<MeleeType, MeleeInfo> WeaponManager::_meleeInfo;

void WeaponManager::init()
{
	_initilized = true;

	ifstream file;
	nlohmann::json j;

	file.open(INFO_PATH + "weapon_info.json");
	if (file.is_open())
	{
		file >> j;

		for (nlohmann::json::iterator it = j.begin(); it != j.end(); ++it)
		{
			nlohmann::json weapon = it.value();

			for (nlohmann::json::iterator typeWeapon = weapon.begin(); typeWeapon != weapon.end(); ++typeWeapon)
			{
				if (it.key() == "Melee")
					_meleeInfo[typeWeapon.value()["id"]] = { typeWeapon.value()["zone"], typeWeapon.key(), typeWeapon.value()["icon"].get<string>(), typeWeapon.value()["frame"].get<string>() };
				else
					_weaponInfo[typeWeapon.value()["id"]] = { typeWeapon.value()["zone"], typeWeapon.key(), typeWeapon.value()["price"] ,
														typeWeapon.value()["damage"], typeWeapon.value()["cadence"], typeWeapon.value()["range"],
														typeWeapon.value()["clip"], typeWeapon.value()["icon"].get<string>(), typeWeapon.value()["frame"].get<string>() };
			}
		}
		file.close();
	}
}

WeaponManager * WeaponManager::getInstance()
{
	if (!_initilized)
		init();

	return &_instance;
}

Gun* WeaponManager::getWeapon(Game* game, GunType type)
{
	Gun* w = nullptr;
	switch (type)
	{
	case Pistol_Weapon:
		w = new BasicPistol(game);
		break;
	case BasicShotgun_Weapon:
		w = new BasicShotgun(game);
		break;
	case ImprovedShotgun_Weapon:
		w = new ImprovedShotgun(game);
		break;
	case BasicRifle_Weapon:
		w = new BasicRifle(game);
		break;
	case ImprovedRifle_Weapon:
		w = new ImprovedRifle(game);
		break;
	case PlasmaSniper_Weapon:
		w = new PlasmaSniper(game);
		break;
	case BounceOrbCannon_Weapon:
		w = new BounceOrbCannon(game);
		break;
	case BHCannon_Weapon:
		w = new GravityBombCannon(game);
		break;
	default:
		break;
	}
	return w;
}

Melee * WeaponManager::getMelee(Game * game, MeleeType type)
{
	Melee* m = nullptr;
	switch (type)
	{
	case Knife_Weapon:
		m = new Knife(game);
		break;
	case Sword_Weapon:
		m = new Sword(game);
		break;
	case PoleAxe_Weapon:
		m = new PoleAxe(game);
		break;
	default:
		break;
	}
	return m;
}
