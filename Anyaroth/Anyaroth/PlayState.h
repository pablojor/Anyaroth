#pragma once
#include "GameState.h"
#include "DebugDraw.h"
#include "LevelManager.h"
#include "CollisionManager.h"
#include "Player.h"
#include "BulletPool.h"
#include "BouncingBulletPool.h"
#include "Coin.h"
#include "ExplosiveBulletPool.h"
#include "Cursor.h"

class PlayState : public GameState
{
private:
	Player* _player = nullptr;
	Cursor* _cursor = nullptr;

	//Bullet Pools
	BulletPool* _playerBulletPool = nullptr; //Balas del jugador
	//////////////////////////////////////////////////////////////
	BouncingBulletPool* _bouncingBulletPool = nullptr; 

	BulletPool* _enemyBulletPool = nullptr; //Balas de los enemigos
	ExplosiveBulletPool* _explosivePool = nullptr;

	LevelManager _levelManager;
	CollisionManager _colManager;
	DebugDraw _debugger;

	int _currentZone;
	int _currentLevel;


	vector <list<GameObject*>::iterator> items_ToDelete;

public:
	PlayState(Game* g);

	void addObject(GameComponent* n);
	void deleteObject(const list<GameObject*>::iterator &itList);

	virtual void render() const;
	virtual void update(double time);
	virtual bool handleEvents(SDL_Event& e);

	inline Player* getPlayer() const { return _player; }
	inline BulletPool* getEnemyPool() const { return _enemyBulletPool; }
	inline ExplosiveBulletPool* getExplosivePool() const { return _explosivePool; }
	inline Cursor* getCursor() const { return _cursor; }

	inline int getCurrentZone() const { return _currentZone; }
	inline int getCurrentLevel() const { return _currentLevel; }
};