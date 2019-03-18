#pragma once
#include "GameState.h"
#include "Layer.h"
#include "Player.h"
#include "DebugDraw.h"
#include "CollisionManager.h"
#include "MeleeEnemy.h"
#include "MartyrEnemy.h"
#include "DistanceStaticEnemy.h"
#include "DistanceDynamicEnemy.h"
#include "SpawnerEnemy.h"
#include "BulletPool.h"
#include "Coin.h"
#include "Cursor.h"
#include "GunType_def.h"

class PlayState : public GameState
{
private:
	Player* _player = nullptr;
	Enemy* _enemy = nullptr;
	Coin* _coin = nullptr;
	Layer* _layer = nullptr;
	Layer* _colisionLayer = nullptr;
	Cursor* _cursor = nullptr;
	CollisionManager _colManager;
	DebugDraw _debugger;

	//PoolWrapper* _enemyPool = nullptr;

	//Bullet Pools
	BulletPool* _playerBulletPool = nullptr; //Balas del jugador
	BulletPool* _enemyBulletPool = nullptr; //Balas del jugador

	vector <list<GameObject*>::iterator> items_ToDelete;

public:
	PlayState(Game* g);

	virtual void render() const;
	virtual void update(double time);
	virtual bool handleEvents(SDL_Event& e);

	void KillObject(const list<GameObject*>::iterator &itList);
	void addObject(GameComponent* n);
	inline Cursor* getCursor() const { return _cursor; }
};