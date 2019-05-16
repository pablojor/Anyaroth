#pragma once
#include "StaticFlyingEnemy.h"
#include "EnemyLifePanel.h"

class Boss3;

class FloatingHead : public StaticFlyingEnemy
{
private:
	Boss3 * _boss = nullptr;
	EnemyLifePanel * _lifePanel;

	bool _invincibility = true, _changeAngle = false, _shooting = false;
	double _timeBetweenShoots = 1000, _currentTimer = 500, _timeShooting = 0;
	int _numOfShoots = 15;

public:
	FloatingHead(Game* g, Player* player, Vector2D pos, BulletPool* pool, Boss3 * boss);
	virtual ~FloatingHead() {}

	virtual void update(double deltaTime);
	virtual void die();

	void shooting(double deltaTime);

	void setLifePanel(EnemyLifePanel* lifePanel);
	void subLife(int damage);

	void turnInvincibilityOff();
	bool isInvincible();
};