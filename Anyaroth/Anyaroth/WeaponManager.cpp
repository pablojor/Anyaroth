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

#include <json.hpp>
#include <map>


map<GunType, GunInfo> WeaponManager::_weaponInfo;

void WeaponManager::init()
{
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
				_weaponInfo[typeWeapon.value()["id"]] = { typeWeapon.value()["zona"], typeWeapon.key(), typeWeapon.value()["price"] ,
														typeWeapon.value()["damage"], typeWeapon.value()["cadence"], typeWeapon.value()["range"], typeWeapon.value()["clip"], typeWeapon.value()["icon"].get<string>(), typeWeapon.value()["frame"].get<string>() };
			}
		}
		file.close();
	}
	else
		cout << "Error al cargar " << INFO_PATH << "weapon_info.json" << endl;
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
	case GravityBombCannon_Weapon:
		w = new GravityBombCannon(_game);
		break;
	default:
		break;
	}
	return w;
}