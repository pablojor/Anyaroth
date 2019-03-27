#pragma once
#include "DistanceEnemy.h"
#include "BossPanel.h"

class Boss : public DistanceEnemy
{
protected:
	bool _fase1 = true, _fase2 = false, _fase3 = false, _beetwenFase = false, move = true;
	Vector2D _bodyPos, _playerPos, _originalPos;
	int _lastFase = 0;

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

	bool inline const isbeetweenFases() { return _beetwenFase; }
	void setBossPanel(BossPanel* b);

	virtual void update(const double& deltaTime);

	virtual void subLife(int damage);
	virtual void manageLife(Life& l, bool& actualFase, int damage);

	virtual void movement(const double& deltaTime) {};

	virtual void beginCollision(GameComponent* other, b2Contact* contact);

	virtual void Fase1(const double& deltaTime) {};
	virtual void Fase2(const double& deltaTime) {};
	virtual void Fase3(const double& deltaTime) {};
	virtual void beetwenFases(const double& deltaTime) {};
	virtual void changeFase(bool& nextFase);
};

