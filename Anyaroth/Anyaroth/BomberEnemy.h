#pragma once
#include "Enemy.h"
#include "GameComponent.h"
#include "AnimatedSpriteComponent.h"
#include "HurtRenderComponent.h"
#include "Player.h"
#include "BomberGun.h"


class BomberEnemy : public Enemy
{
private:
	double _shootTime = 1000, _angle = 90, _range = 600;
	Vector2D _dir = Vector2D();

	BulletPool* _myBulletPool = nullptr;
	BomberGun* _gun = nullptr;
	//ExplosiveBulletEffect _effect = ExplosiveBulletEffect(100);
	Texture* _bulletTexture = nullptr;
	ExplosiveBulletPool* _bulletPool = nullptr;

public:
	BomberEnemy(Game* g, Player* player, Vector2D pos, BulletPool* pool);
	virtual ~BomberEnemy() {}

	void move();
	void shoot(const double& deltaTime);

	void throwBomb(const Vector2D& position);
	virtual void update(const double& deltaTime);
	virtual void subLife(int damage);
};