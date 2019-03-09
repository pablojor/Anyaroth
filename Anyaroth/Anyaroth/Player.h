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
	Player(Game* g, int xPos, int yPos);
	~Player();

	bool handleInput(const SDL_Event& event);
	void update();

	virtual void beginCollision(GameComponent* other, b2Contact* contact);
	virtual void endCollision(GameComponent* other, b2Contact* contact);

	void subLife(int damage);
	void die();

	//inline PlayerArm* getWeaponArm() const { return _weaponArm; }
	void swapGun();

	void move(const Vector2D& dir, const double& speed);
	void dash(const Vector2D& dir);
	void jump();

	void melee();
	void shoot();
	void reload();

	inline void setPlayerPanel(PlayerPanel* p) { _playerPanel = p; }
};