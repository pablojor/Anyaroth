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
	b2Fixture* _floorSensor;
	Life _life = Life(100);
	uint _currentState = 0;
	PlayerArm* _weaponArm = nullptr;
	AnimatedSpriteComponent* _anim = nullptr;
	MovingComponent* _movement = nullptr;
	TransformComponent * _transform = nullptr;
	BodyComponent * _body = nullptr;
	HurtRenderComponent* _hurt = nullptr;
	HurtRenderComponent* _hurtArm = nullptr;

	PlayerPanel* _playerPanel = nullptr;

	int _dashCD = 3000;
	int _maxDash = 2, _numDash = _maxDash;
	Money * _money = nullptr;

	bool _isDashing = false, _dead = false;
	int _floorCount = 0;

	int _maxInventoryGuns = 2; //numero de slots en el inventario de armas 
	vector<GunType> _gunInventory; //Ej: == {Game::BasicGun} -> indica que en el inventario solo lleva la pistola basica
	GunType _equippedGun = BasicGun;
	vector<Texture*> _armTextures;

	inline bool dashIsAble() const { return _numDash > 0 && _isDashing; }
	void checkMovement(const Uint8* keyboard);
	void checkMouseInput(const Uint32& mouse);

	void handleAnimations();

	void refreshCooldowns(const Uint32& deltaTime);
	void refreshDashCoolDown(const Uint32& deltaTime);
	void refreshGunCadence(const Uint32& deltaTime);
	inline const bool isGrounded() { return _floorCount; }
	inline void setGrounded(bool grounded) { _floorCount = grounded; }

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

	inline PlayerArm* getWeaponArm() const { return _weaponArm; }
	void swapGun();

	void move(const Vector2D& dir, const double& speed);
	void dash(const Vector2D& dir);
	void jump();

	void melee();
	void shoot();
	void reload();

	inline uint getCurrentState() const { return _currentState; }
	inline void setCurrentState(uint n) { _currentState = n; }
	inline void setPlayerPanel(PlayerPanel* p) { _playerPanel = p; }
};