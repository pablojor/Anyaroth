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
	static std::map<GunType, GunInfo> _weaponInfo;

public:
	static void init();

	static Gun* getWeapon(Game* game, GunType type);
	static const GunInfo& getGunInfo(const GunType& id) { return _weaponInfo[id]; };
	static std::map<GunType, GunInfo> getAllWeaponInfo() { return _weaponInfo; }
};

