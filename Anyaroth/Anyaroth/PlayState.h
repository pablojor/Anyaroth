#pragma once
#include "GameState.h"
#include "DebugDraw.h"
#include "LevelManager.h"
#include "CollisionManager.h"
#include "ParallaxBackGround.h"
#include "Player.h"
#include "BulletPool.h"
#include "BouncingBulletPool.h"
#include "Coin.h"
#include "ExplosiveBulletPool.h"
#include "Cursor.h"
#include "PlayStateHUD.h"

class PlayState : public GameState
{
private:
	Player* _player = nullptr;
	Cursor* _cursor = nullptr;

	//HUD
	PlayStateHUD* _hud = nullptr;

	//Bullet Pools
	BulletPool* _playerBulletPool = nullptr; //Balas del jugador
	//////////////////////////////////////////////////////////////
	BouncingBulletPool* _bouncingBulletPool = nullptr; 

	LevelManager _levelManager;
	CollisionManager _colManager;
	DebugDraw _debugger;

	ParallaxBackGround* _parallaxZone1 = nullptr;

	int _currentZone;
	int _currentLevel;

public:
	PlayState(Game* g);

	virtual void render() const;
	virtual void update(const double& deltaTime);
	virtual bool handleEvent(const SDL_Event& event);

	inline PlayStateHUD* getHUD() const { return _hud; }
	inline Cursor* getCursor() const { return _cursor; }

	inline int getCurrentZone() const { return _currentZone; }
	inline int getCurrentLevel() const { return _currentLevel; }
};