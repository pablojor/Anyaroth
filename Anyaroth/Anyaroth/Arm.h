#pragma once

#include "GameComponent.h"
#include "TransformComponent.h"
#include "Game.h"
#include "checkML.h"

class AnimatedSpriteComponent;
class Gun;
class Player;
class ArmControllerComponent;
class FollowingComponent;

class Arm : public GameComponent
{
protected:
	TransformComponent* _transform;
	GameComponent* _player;
	AnimatedSpriteComponent* _anim;
	FollowingComponent* _followC;
	ArmControllerComponent* _controller;

	double _minAimDistance = 32;
	double _magicNumber = 64;


	Gun* _currentGun = nullptr;
public:
	Arm(Texture* texture, GameComponent* player, Game* g, Vector2D offset = { 0,0 });
	virtual ~Arm();

	void update();

	void setPlayer(Vector2D offset, GameComponent* player);
	void setGun(Gun* gun); //Establece el arma
	void shoot();	
	bool reload(); 
};

