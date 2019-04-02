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
public:
	static Gun* getWeapon(Game* game, GunType type);
};

