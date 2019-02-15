#pragma once

#include "GameComponent.h"
#include "Arm.h"
#include "Gun.h"
#include "Shooter.h"

class Arm;
class Game;

class Player : public GameComponent {
private:
	int _life;

	Arm* _weaponArm = nullptr;

public:
	Player(Texture* texture, Game* g);
	~Player();

	void update();

	void setArm(Arm* arm) { _weaponArm = arm; };
	void equipGun(int gunIndex);
	
};