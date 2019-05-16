#pragma once
#include "GameState.h"
#include "LevelManager.h"
#include "Player.h"
#include "BulletPool.h"
#include "ParticlePool.h"
#include "Cursor.h"

class PlayState : public GameState
{
private:
	Player* _player = nullptr;
	GameObject* _level = nullptr;

	BulletPool* _playerBulletPool = nullptr;
	ParticlePool* _particlePool = nullptr;

	LevelManager _levelManager;

public:
	PlayState(Game* g);
	virtual ~PlayState();

	virtual void start();
	virtual void update(double deltaTime);
	virtual bool handleEvent(const SDL_Event& event);

	void saveGame();
	void loadGame();
};