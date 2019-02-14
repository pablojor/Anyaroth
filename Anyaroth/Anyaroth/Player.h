#pragma once

#include "GameComponent.h"
#include "Arm.h"
#include "Gun.h"

class Arm;

class Player : public GameComponent {
private:
	int _life;

	Arm* _weaponArm = nullptr;

	static const int NUM_GUNS = 3; //PONER ESTO COMO CONSTANTE DE GAME
	Gun guns[NUM_GUNS] = {Gun(this, 100, 32), Gun(this, 100, 32), Gun(this, 100, 32) };
public:
	Player(Texture* texture);
	~Player();

	void update();

	void setArm(Arm* arm) { _weaponArm = arm; };
};