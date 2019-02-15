#pragma once

#include "GameComponent.h"
#include "TransformComponent.h"
#include "Game.h"

class AnimatedSpriteComponent;
class Gun;

class Arm : public GameComponent
{
protected:
	TransformComponent* _transform;
	GameComponent* _player;
	AnimatedSpriteComponent* _anim;

	Gun* _currentGun = nullptr;
public:
	Arm(Texture* texture, GameComponent* player, Game* g, Vector2D offset = { 0,0 });
	virtual ~Arm();

	void update();

	void setPlayer(Vector2D offset, GameComponent* player);
	void setGun(Gun* gun) { _currentGun = gun; } //Establece el arma
	void shoot();	
	void reload(); 
};

