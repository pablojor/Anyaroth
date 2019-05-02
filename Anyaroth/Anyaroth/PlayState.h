#pragma once
#include "GameState.h"
#include "DebugDraw.h"
#include "LevelManager.h"
#include "CollisionManager.h"
#include "ParticleManager.h"
#include "Player.h"
#include "BulletPool.h"
#include "ParticlePool.h"
#include "Cursor.h"

class PlayState : public GameState
{
private:
	Player* _player = nullptr;
	GameObject* _level = nullptr;
	Cursor* _cursor = nullptr;

	BulletPool* _playerBulletPool = nullptr;
	ParticlePool * _particlePool = nullptr;

	DebugDraw _debugger;
	CollisionManager _colManager;
	LevelManager _levelManager;
	ParticleManager* _particleManager = nullptr;

public:
	PlayState(Game* g);
	virtual ~PlayState();

	virtual void start();
	virtual void update(const double& deltaTime);
	virtual bool handleEvent(const SDL_Event& event);

	void saveGame();
	void loadGame();
};