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
#include "Axe.h"
#include "Poleaxe.h"

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
	nlohmann::json a;

	file.open(INFO_PATH + "weapon_info.json");
	if (file.is_open())
	{
		file >> a;
		nlohmann::json j = a["Guns"];

		for (nlohmann::json::iterator it = j.begin(); it != j.end(); ++it)
		{
			nlohmann::json weapon = it.value();

			for (nlohmann::json::iterator typeWeapon = weapon.begin(); typeWeapon != weapon.end(); ++typeWeapon)
			{
				_weaponInfo[typeWeapon.value()["id"]] = { typeWeapon.value()["zone"], typeWeapon.key(), typeWeapon.value()["price"] ,
														typeWeapon.value()["damage"], typeWeapon.value()["cadence"], typeWeapon.value()["range"],
														typeWeapon.value()["clip"], typeWeapon.value()["icon"].get<string>(), typeWeapon.value()["frame"].get<string>() };
			}
		}
		j = a["Melee"];
		for (nlohmann::json::iterator typeMelee = j.begin(); typeMelee != j.end(); ++typeMelee)
		{
			_meleeInfo[typeMelee.value()["id"]] = { typeMelee.value()["zone"], typeMelee.key(), typeMelee.value()["damage"], typeMelee.value()["icon"].get<string>(), typeMelee.value()["frame"].get<string>() };
		}
		file.close();
	}
	else
		cout << "Error al cargar " << INFO_PATH << "weapon_info.json" << endl;
}

WeaponManager * WeaponManager::getInstance()
{
	if (!_initilized)
		init();

	return &_instance;
}

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
		w = new PlasmaSniper(_game);
		break;
	case BounceOrbCannon_Weapon:
		w = new BounceOrbCannon(_game);
		break;
	case BHCannon_Weapon:
		w = new GravityBombCannon(_game);
		break;
	default:
		break;
	}
	return w;
}

Melee * WeaponManager::getMelee(Game * game, MeleeType type, Player* p)
{
	Melee* m = nullptr;
	switch (type)
	{
	case Knife_Weapon:
		m = new Melee(game, { 15, 0 }, ENEMIES, 25, 10, 5, Knife_Weapon);
		break;
	case Sword_Weapon:
		m = new Axe(game, { 150, 0 }, ENEMIES, 20, 40, 40, 270);
		break;
	case Poleaxe_Weapon:
		m = new Poleaxe(game, { 50,0 }, ENEMIES, 50, 15, 5, p);
		break;
	default:
		break;
	}
	return m;
}
