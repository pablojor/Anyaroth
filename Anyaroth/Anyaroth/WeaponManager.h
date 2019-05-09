#pragma once

#include <vector>
#include "GunType_def.h"
#include "Gun.h"
#include <map>

class Game;

using namespace std;

/*****************************************************************************************/
// Esta clase se encarga de crear las armas que el jugador adquiere
/************************************************************************************/

struct GunInfo {
	int _zone;

	string _name;
	int _price;

	int _damage;
	int _cadence;
	int _distance;
	int _clip;

	string _iconName;
	string _rarityFrame;
};

struct MeleeInfo {
	int _zone;

	string _name;

	string _iconName;
	string _rarityFrame;
};

class WeaponManager
{
private:
	static WeaponManager _instance;
	static bool _initilized;

	WeaponManager(WeaponManager&) = delete;
	WeaponManager& operator=(const WeaponManager&) = delete;

	static std::map<GunType, GunInfo> _weaponInfo;
	static std::map<MeleeType, MeleeInfo> _meleeInfo;

	WeaponManager() {}

public:
	~WeaponManager() {};

	static void init();
	static WeaponManager* getInstance();

	Gun* getWeapon(Game* game, GunType type);
	const GunInfo& getGunInfo(const GunType& id) { return _weaponInfo[id]; };
	std::map<GunType, GunInfo> getAllWeaponInfo() { return _weaponInfo; }

	Melee* getMelee(Game* game, MeleeType type);
	const MeleeInfo& getMeleeInfo(const MeleeType& id) { return _meleeInfo[id]; };
	std::map<MeleeType, MeleeInfo> getAllMeleeInfo() { return _meleeInfo; }
};

