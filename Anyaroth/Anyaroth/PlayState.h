#pragma once
#include "GameState.h"
#include "DebugDraw.h"
#include "LevelManager.h"
#include "CollisionManager.h"
#include "ParallaxBackGround.h"
#include "Player.h"
#include "BulletPool.h"
#include "Cursor.h"

class PlayState : public GameState
{
private:
	Player* _player = nullptr;
	Cursor* _cursor = nullptr;

	//Bullet Pools
	BulletPool* _playerBulletPool = nullptr; //Balas del jugador

	LevelManager _levelManager;
	CollisionManager _colManager;
	DebugDraw _debugger;

	ParallaxBackGround* _parallaxZone1 = nullptr;

	int _currentLevel;

	double deathTime = 3000, deathTimer = 0;
	bool _killed = false;
	TextUI* deathText;

public:
	PlayState(Game* g);

	virtual void render() const;
	virtual void update(const double& deltaTime);
	virtual bool handleEvent(const SDL_Event& event);

	inline Cursor* getCursor() const { return _cursor; }
	inline int getCurrentLevel() const { return _currentLevel; }
};