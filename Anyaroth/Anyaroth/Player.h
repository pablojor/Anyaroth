#pragma once
#include "GameComponent.h"
#include "Arm.h"
#include "Gun.h"
#include "Shooter.h"
#include "PlayState.h"

class Arm;
class Game;

class AnimatedSpriteComponent;
class PlayerControllerComponent;
class PlayState;

class Player : public GameComponent
{
private:
	int _life;
	PlayState* _play = nullptr;

public:
  	enum states { Idle, Attacking, Reloading };
  	uint _currentState = 0;
	Arm* _weaponArm = nullptr;
	AnimatedSpriteComponent* _anim;
	PlayerControllerComponent* _controller;
  
	Player(Texture* texture, Game* g, PlayState* play);
  	~Player();

	void update();
	virtual void beginCollision(GameComponent* other);
  
	void setArm(Arm* arm) { _weaponArm = arm; };
	void equipGun(int gunIndex, int bulletPoolIndex = 0);
  
	void reload();

	uint getCurrentState() { return _currentState; };
	void setCurrentState(uint n) { _currentState = n; };
};