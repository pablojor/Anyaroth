#pragma once
#include "Enemy.h"
#include "GameComponent.h"
#include "AnimatedSpriteComponent.h"
#include "Player.h"
#include "HurtRenderComponent.h"
class BomberEnemy :
	public Enemy
{
private:
	bool _spawning = false, _activated = true;
	double _spawnTime = 1000;
	int _range = 600;
	BulletPool* _myBulletPool = nullptr;
	Texture* _bulletTexture = nullptr;
public:
	BomberEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag, BulletPool* pool);
	virtual ~BomberEnemy();
	virtual void update(double time);
	virtual void subLife(int damage);
	void Throw(const Vector2D& position, const double& angle, const string& tag);

};

