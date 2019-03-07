#pragma once
#include "GameComponent.h"
#include "PlayerArm.h"
#include "Gun.h"
#include "Shooter.h"
#include "Money.h"
#include "PlayState.h"
#include "Life.h"
#include "GunType_def.h"
#include "PlayerPanel.h"

class PlayerArm;
class Game;

class AnimatedSpriteComponent;
class MovingComponent;
class PlayState;
class HurtRenderComponent;

class Player : public GameComponent
{
private:
	PlayState* _play = nullptr;
	Life _life = Life(100);
	//int AmountOfCollision;
	uint _currentState = 0;
	PlayerArm* _weaponArm = nullptr;
	AnimatedSpriteComponent* _anim;
	MovingComponent* _movement;
	TransformComponent * _transform;
	BodyComponent * _body;
	HurtRenderComponent* _hurt;
	HurtRenderComponent* _hurtArm;

	PlayerPanel* _playerPanel = nullptr;

	uint32 _dashCD = 3000;
	uint32 _timer = 0;
	int _maxDash = 2;
	int _numDash = _maxDash;
	Money * _money = nullptr;

	bool _isGrounded = false;
	bool _isDashing = false;

	int _maxInventoryGuns = 2; //n�mero de slots en el inventario de armas 
	vector<GunType> _gunInventory; //Ej: == {Game::BasicGun} -> indica que en el inventario solo lleva la pistola b�sica
	GunType _equippedGun = BasicGun;
	vector<Texture*> _armTextures;

	bool _dead = false;

	inline bool dashIsAble() const { return _numDash > 0 && _isDashing; }
	void checkMovement(const Uint8* keyboard);
	void handleAnimations();

public:

	enum states { Idle, Attacking, Walking, Reloading, Dashing, Falling, Jumping };

	Player(Texture* texture, Game* g, PlayState* play, string tag);
	~Player();

	bool handleInput(const SDL_Event& event);
	void update();

	virtual void beginCollision(GameComponent* other, b2Contact* contact);
	virtual void endCollision(GameComponent* other, b2Contact* contact);

	void subLife(int damage);
	void die();

	//inline void setArm(PlayerArm* arm) { _weaponArm = arm; };
	inline PlayerArm* getWeaponArm() const { return _weaponArm; }
	//void equipGun(int gunIndex);
	void swapGun();

	void move(const Vector2D& dir, const double& speed);
	void dash(const Vector2D& dir);
	void jump();

	void melee();
	void shoot();
	void reload();

	inline uint getCurrentState() const { return _currentState; };
	inline void setCurrentState(uint n) { _currentState = n; };

	inline void setPlayerPanel(PlayerPanel* p) { _playerPanel = p; }
};