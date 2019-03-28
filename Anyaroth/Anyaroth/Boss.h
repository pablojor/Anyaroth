#pragma once
#include "DistanceEnemy.h"
#include "BossPanel.h"

enum Fase
{
	Fase1, Fase2, Fase3, BetweenFase
};

enum State
{
	Moving, Shooting, Bombing, Meleeing, OrbAttacking
};
class Boss : public DistanceEnemy
{
protected:
	Vector2D _bodyPos, _playerPos, _originalPos;
	int _actualFase = Fase1, _lastFase = Fase1, _actualState = Moving;

	BodyComponent* _playerBody;

	//Vida
	Life _life1, _life2, _life3;

	//Panel del HUD
	BossPanel* _bossPanel = nullptr;

	//Tiempo entre acciones
	int _doSomething = 1000, _noAction = 0;
public:
	Boss(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag, BulletPool* pool);
	virtual ~Boss();

	bool inline const isbeetweenFases() { return _actualFase==BetweenFase; }
	void setBossPanel(BossPanel* b);

	virtual void update(const double& deltaTime);

	virtual void subLife(int damage);
	virtual void manageLife(Life& l, int damage);

	virtual void movement(const double& deltaTime) {};

	virtual void beginCollision(GameComponent* other, b2Contact* contact);

	virtual void fase1(const double& deltaTime) {};
	virtual void fase2(const double& deltaTime) {};
	virtual void fase3(const double& deltaTime) {};
	virtual void beetwenFases(const double& deltaTime) {};
	virtual void changeFase(int fase);
};

