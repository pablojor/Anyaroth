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

class WeaponManager
{
private:
	static WeaponManager _instance;
	static bool _initilized;

	WeaponManager(WeaponManager&) = delete;
	WeaponManager& operator=(const WeaponManager&) = delete;

	static std::map<GunType, GunInfo> _weaponInfo;

	WeaponManager() {}

public:
	~WeaponManager() {};

	static void init();
	static WeaponManager* getInstance();

	static Gun* getWeapon(Game* game, GunType type);
	static const GunInfo& getGunInfo(const GunType& id) { return _weaponInfo[id]; };
	static std::map<GunType, GunInfo> getAllWeaponInfo() { return _weaponInfo; }
};

