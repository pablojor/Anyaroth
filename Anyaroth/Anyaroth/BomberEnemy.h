#pragma once
#include "Enemy.h"
#include "GameObject.h"
#include "AnimatedSpriteComponent.h"
#include "Player.h"

class BomberEnemy : public Enemy
{
private:
	bool _spawning = false, _activated = false, _bloqueDer = false, _bloqueIzq = false, _move = false;
	double _spawnTime = 1000;
	int _range = 600, _dir = 8;

	ExplosiveBulletPool* _myBulletPool = nullptr;
	Texture* _bulletTexture = nullptr;

public:
	BomberEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag, ExplosiveBulletPool* pool);
	virtual ~BomberEnemy();

	virtual void update(const double& deltaTime);

	virtual void subLife(int damage);

	virtual void beginCollision(GameObject* other, b2Contact* contact);

	void throwBomb(const Vector2D& position, const double& angle, const string& tag);
};