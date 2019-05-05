#pragma once
#include "DistanceEnemy.h"
#include "BossPanel.h"
#include "Melee.h"

enum Fase
{
	Fase1, Fase2, Fase3, BetweenFase
};

enum State
{
	Moving, Shooting, Bombing, Meleeing, OrbAttacking, Jumping, GravAttack, PortalAttack, Dashing,Idle
};

class Boss : public DistanceEnemy
{
protected:
	//Vida
	Life _life1, _life2, _life3;

	//Panel del HUD
	BossPanel* _bossPanel = nullptr;

	//Tiempo entre acciones
	int _doSomething = 1000, _noAction = 0;
  
	Vector2D _bodyPos, _playerPos, _originalPos;
	BodyComponent* _playerBody;

	int _actualFase = Fase1, _lastFase = Fase1, _actualState = Moving;
	//Melee
	Melee* _melee = nullptr;

public:
	Boss(Game* g, Player* player, Vector2D pos, BulletPool* pool, Texture* text) : DistanceEnemy(g, player, pos, text, pool), Enemy(g, player, pos, text) {}
	virtual ~Boss() {}
  
	virtual void setBossPanel(BossPanel* b);
	void drop() {}

	bool inline const isbeetweenFases() { return _actualFase==BetweenFase; }
	int inline const getLastFase() { return _lastFase; }

	virtual void update(const double& deltaTime);

	virtual void subLife(int damage);
	virtual void manageLife(Life& l, int damage);
	void drop() {}

	virtual void movement(const double& deltaTime) {}

	virtual void fase1(const double& deltaTime) {}
	virtual void fase2(const double& deltaTime) {}
	virtual void fase3(const double& deltaTime) {}

	virtual void beetwenFases(const double& deltaTime) {}
	bool inline const isbeetweenFases() { return _actualFase == BetweenFase; }
  
	virtual void changeFase(int fase);
	int inline const getLastFase() { return _lastFase; }
};