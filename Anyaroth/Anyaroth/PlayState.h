#pragma once
#include "GameState.h"
#include "DebugDraw.h"
#include "LevelManager.h"
#include "CollisionManager.h"
#include "ParallaxBackGround.h"
#include "Player.h"
#include "BulletPool.h"
#include "ParticlePull.h"
#include "ParticleManager.h"
//#include "Coin.h"
//#include "ExplosiveBulletPool.h"
#include "Cursor.h"
#include "PlayStateHUD.h"
#include "Shop.h"

class PlayState : public GameState
{
private:
	Player* _player = nullptr;
	Cursor* _cursor = nullptr;

	//Bullet Pools
	BulletPool* _playerBulletPool = nullptr; //Balas del jugador

	//Paticle pool
	ParticlePull * _particles;

	PlayStateHUD* _hud = nullptr;

	LevelManager _levelManager;
	CollisionManager _colManager;
	DebugDraw _debugger;

	ParallaxBackGround* _parallaxZone1 = nullptr;

	Shop* _shop = nullptr;

	int _currentZone;
	int _currentLevel;

	ParticleManager * _particleManager;

	//vector <list<GameObject*>::iterator> items_ToDelete;
	Game* gg;
public:
	PlayState(Game* g);

	virtual void render() const;
	virtual void update(const double& deltaTime);
	virtual bool handleEvent(const SDL_Event& event);

	//inline Player* getPlayer() const { return _player; }
	//inline BulletPool* getEnemyPool() const { return _enemyBulletPool; }
	//inline ExplosiveBulletPool* getExplosivePool() const { return _explosivePool; }
	inline Cursor* getCursor() const { return _cursor; }

	inline int getCurrentZone() const { return _currentZone; }
	inline int getCurrentLevel() const { return _currentLevel; }
};