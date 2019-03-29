#pragma once

#include <vector>
#include "GunType_def.h"
#include "Gun.h"

class Game;

using namespace std;

/*****************************************************************************************/
// Esta clase se encarga de crear las armas que el jugador adquiere
/************************************************************************************/

class WeaponManager
{
private:
	//vector con las armas equipadas
	// 0-Slot Arma 1
	// 1-Slot Arma 2
	vector<Gun*> _equippedWeapons = {nullptr, nullptr};
	Game* _game = nullptr;

public:
	WeaponManager(Game* g);
	virtual ~WeaponManager();

	Gun* getWeapon(GunType type, int slotIndex);
};

