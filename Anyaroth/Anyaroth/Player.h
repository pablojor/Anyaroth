#pragma once
#include "GameComponent.h"
#include "PlayerArm.h"
#include "Gun.h"
#include "Shooter.h"
#include "Money.h"
#include "Life.h"
#include "GunType_def.h"
#include "PlayerPanel.h"

class Player : public GameComponent
{
private:
	//Componentes
	TransformComponent* _transform = nullptr;
	AnimatedSpriteComponent* _anim = nullptr;
	BodyComponent* _body = nullptr;
	//HurtRenderComponent* _hurt = nullptr;

	//Propiedades
	Life _life = Life(100);
	Money * _money = nullptr;
	PlayerPanel* _playerPanel = nullptr;

	//Hijos
	PlayerArm* _playerArm = nullptr;

	//Variable auxiliares
	int _dashCD = 3000, _maxDash = 2, _numDash = _maxDash;
	bool _isDashing = false, _isReloading = false, _isShooting = false, _isMeleeing = false, _dead = false;
	int _floorCount = 0;

	Gun* _currentGun = nullptr;
	Gun* _otherGun = nullptr;

	inline bool dashIsAble() const { return _numDash > 0 && _isDashing; }
	void checkMovement(const Uint8* keyboard);
	void checkMouseInput(const Uint32& mouse);

	void handleAnimations();

	void refreshCooldowns(const Uint32& deltaTime);
	void refreshDashCoolDown(const Uint32& deltaTime);
	void refreshGunCadence(const Uint32& deltaTime);
	inline void setGrounded(bool grounded) { _floorCount = grounded; }

	bool canReload();

public:
	Player(Game* g, int xPos, int yPos);
	~Player();

	bool handleInput(const SDL_Event& event);
	void update();

	virtual void beginCollision(GameComponent* other, b2Contact* contact);
	virtual void endCollision(GameComponent* other, b2Contact* contact);

	void subLife(int damage);
	void die();

	void swapGun();
	inline void changeCurrentGun(Gun* gun) { _currentGun = gun; }
	inline void changeOtherGun(Gun* gun) { _otherGun = gun; }
	inline Gun* getCurrentGun() const { return _currentGun; }
	inline Gun* getOtherGun() const { return _otherGun; }

	void move(const Vector2D& dir, const double& speed);
	void dash(const Vector2D& dir);
	void jump();

	void melee();
	void shoot();
	void reload();

	void setPlayerPanel(PlayerPanel* p);

	inline bool isGrounded() const { return _floorCount; }
	bool isDashing() const;
	bool isMeleeing() const;
	bool isReloading() const;
};