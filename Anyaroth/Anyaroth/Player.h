#pragma once
#include "GameObject.h"
#include "TransformComponent.h"
#include "BodyComponent.h"
#include "CustomAnimatedSpriteComponent.h"
#include "PlayerPanel.h"
#include "Life.h"
#include "Money.h"
#include "Melee.h"
#include "PlayerArm.h"
#include "Gun.h"
#include "PoolWrapper.h"

class Game;

class Player : public GameObject
{
private:
	//Components
	TransformComponent* _transform = nullptr;
	BodyComponent* _body = nullptr;
	CustomAnimatedSpriteComponent* _anim = nullptr;
	Melee* _melee = nullptr;

	//Child
	PlayerArm* _playerArm = nullptr;

	//Properties
	Life _life = Life(100);
	Money* _money = nullptr;
	PlayerPanel* _playerPanel = nullptr;

	string _dustParticle = "Dust1";

	double _speed = 15, _gravScale = 8, _damping = 3;

	int _meleeAnim = AnimatedSpriteComponent::MeleeKnife;

	//Jump
	int _floorCount = 0;
	double _jumpForce = 480;
	float _timeToJump = 100.f;

	//Dash
	int _dashTime = 250, _dashCD = 1000 + _dashTime;
	bool _isDashing = false, _onDash = false, _dashDown = false, _dashEnabled = true;

	//Death
	int _deathCD = 3000;

	//Controller
	double _jPosX, _jPosY, _prevAxisX = 0, _prevAxisY = 0, _jAngle = 0;
	bool _jJump = false, _jShoot = false, _jMoveLeft = false, _jMoveDown = false, _jMoveRight = false, _jReleased = false;

	//Particles
	float _runningSpawnParticle = 40.0f, _dashParticleTime = 40.0f;
	bool _spawnParticles = false;

	//Actions
	bool _hasToReload = false, _isShooting = false, _isMeleeing = false, _stunned =false;
	double _stunTime = 1000;

	//Others
	bool _inputFreezed = false, _noDamage = false;

	//Guns
	Gun* _currentGun = nullptr;
	Gun* _otherGun = nullptr;
	BulletPool* _playerBulletPool = nullptr;
	
	b2Vec2 _contactPoint = b2Vec2_zero;

	void checkMovement(const Uint8* keyboard);
	inline void setGrounded(bool grounded) { grounded ? _timeToJump = 100.f : _floorCount = grounded; }

	void handleAnimations();

	void refreshCooldowns(double deltaTime);
	void refreshDashCoolDown(double deltaTime);

	void dashTimer(double deltaTime);

	void refreshGunCadence(double deltaTime);
	bool canReload();

	void checkMelee();

public:
	Player(Game* g);
	~Player();

	bool handleEvent(const SDL_Event& event);
	void update(double deltaTime);

	virtual void beginCollision(GameObject* other, b2Contact* contact);
	virtual void endCollision(GameObject* other, b2Contact* contact);

	void die();
	void revive();

	void subLife(int damage);
	inline void setNoDamage(bool b) { _noDamage = b; }
	inline bool isDead() const { return GameObject::isDead(); }

	inline int getMaxLife() const { return _life.getMaxLife(); }
	inline void setMaxLife(int amount) { _life.setMaxLife(amount); }

	void clearAmmo();
	void swapGun();

	void changeCurrentGun(Gun* gun);
	void changeOtherGun(Gun* gun);
	void changeMelee(Melee* newMelee, int anim);

	inline Melee* getMelee() const { return _melee; }
	inline int getMeleeAnim() const { return _meleeAnim; }

	inline Gun* getCurrentGun() const { return _currentGun; }
	inline Gun* getOtherGun() const { return _otherGun; }

	inline bool spendMoney(int n) { return _money->spend(n); }
	inline Money* getMoney() const { return _money; }

	inline int getBank() const { return _money->getBank(); }
	inline void setBank(int amount) { _money->setBank(amount); }

	void move(const Vector2D& dir, double speed);
	void dash(const Vector2D& dir);

	void dashOff();
	void jump();
	void cancelJump();
	void stunPlayer();
	void refreshStunTime(double deltaTime);
	inline bool isGrounded() const { return _floorCount; }

	void melee();
	void shoot();
	void reload();

	void setPlayerPanel(PlayerPanel* p);
	inline PlayerPanel* getPlayerPanel() const { return _playerPanel; };

	inline void setPlayerPosition(Vector2D pos) {_body->getBody()->SetTransform(b2Vec2(pos.getX(), pos.getY()), 0);}
	inline void setPlayerBulletPool(BulletPool* pool) { _playerBulletPool = pool; }
	void resetDustParticle();

	void stopPlayer();
	inline void setInputFreezed(bool b) { _inputFreezed = b; if (b) stopPlayer(); }
	inline bool isInputFreezed() { return _inputFreezed; }

	inline bool isDashing() const { return _onDash; }
	inline bool isReloading() const { return _playerArm->isReloading(); }
	inline void setIsReloading(bool b) { _hasToReload = b; }
	inline bool isMeleeing() const { return (_anim->getCurrentAnim() == AnimatedSpriteComponent::MeleeKnife || _anim->getCurrentAnim() == AnimatedSpriteComponent::MeleeSword || _anim->getCurrentAnim() == AnimatedSpriteComponent::MeleeHalberd) && !_anim->animationFinished(); }
	inline bool isJumping() const { return (_anim->getCurrentAnim() == AnimatedSpriteComponent::BeforeJump || _anim->getCurrentAnim() == AnimatedSpriteComponent::Jump) && !_anim->animationFinished(); }
	inline bool isFalling() const { return (_anim->getCurrentAnim() == AnimatedSpriteComponent::Falling || _anim->getCurrentAnim() == AnimatedSpriteComponent::StartFalling) && !_anim->animationFinished(); }
};