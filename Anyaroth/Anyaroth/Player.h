#pragma once
#include "GameComponent.h"
#include "PlayerArm.h"
#include "Gun.h"
#include "Shooter.h"
#include "Money.h"
#include "PlayState.h"
#include "Life.h"
#include "GunType_def.h"

class PlayerArm;
class Game;

class AnimatedSpriteComponent;
class PlayerControllerComponent;
class PlayState;
class HurtRenderComponent;

class Player : public GameComponent
{
private:
	PlayState* _play = nullptr;
	Life _life = Life(100);
	int AmountOfCollision;
	uint _currentState = 0;
	PlayerArm* _weaponArm = nullptr;
	AnimatedSpriteComponent* _anim;
	PlayerControllerComponent* _controller;
	TransformComponent * _transform;
	BodyComponent * _body;
	HurtRenderComponent* _hurt;
	HurtRenderComponent* _hurtArm;

	uint32 _dashCD = 3000;
	uint32 _timer = 0;
	int _MaxDash = 2;
	Money * _money = nullptr;
	int _maxInventoryGuns = 2; //n�mero de slots en el inventario de armas 
	vector<GunType> _gunInventory; //Ej: == {Game::BasicGun} -> indica que en el inventario solo lleva la pistola b�sica
	GunType _equippedGun = BasicGun;
	vector<Texture*> _armTextures;

	bool _dead = false;

public:

	enum states { Idle, Attacking, Reloading, Dashing };

	Player(Texture* texture, Game* g, PlayState* play, string tag);
	~Player();

	void update();
	virtual void beginCollision(GameComponent* other, b2Contact* contact);
	virtual void endCollision(GameComponent* other, b2Contact* contact);

	void subLife(int damage);
	void die();

	void setArm(PlayerArm* arm) { _weaponArm = arm; };
	PlayerArm* getWeaponArm() { return _weaponArm; }
	void equipGun(int gunIndex);
	void swapGun();

	void reload();

	uint getCurrentState() { return _currentState; };
	void setCurrentState(uint n) { _currentState = n; };
};