#pragma once
#include "Enemy.h"
#include "GameObject.h"
#include "AnimatedSpriteComponent.h"
#include "Player.h"
#include "BomberGun.h"

class BomberEnemy : public Enemy
{
private:
	double _shootTime = 1000, _angle = 90, _range = 600;
	Vector2D _dir = Vector2D();

	BulletPool* _myBulletPool = nullptr;
	BomberGun* _gun = nullptr;
	Texture* _bulletTexture = nullptr;

public:
	BomberEnemy(Game* g, Player* player, Vector2D pos, BulletPool* pool);
	virtual ~BomberEnemy();

	void move();
	void shoot(double deltaTime);

	void throwBomb(const Vector2D& position);
	virtual void update(double deltaTime);
	virtual void subLife(int damage);
};