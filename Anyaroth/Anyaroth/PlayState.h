#pragma once
#include "GameState.h"
#include "DebugDraw.h"
#include "LevelManager.h"
#include "CollisionManager.h"
#include "Player.h"
#include "BulletPool.h"
#include "Cursor.h"

class PlayState : public GameState
{
private:
	Player* _player = nullptr;
	BulletPool* _playerBulletPool = nullptr; //Balas del jugador
	Cursor* _cursor = nullptr;

	LevelManager _levelManager;
	CollisionManager _colManager;
	DebugDraw _debugger;

	int _currentZone;
	int _currentLevel;

public:
	PlayState(Game* g);

	virtual void render() const;
	virtual void update(double time);
	virtual bool handleEvents(SDL_Event& e);

	inline Player* getPlayer() const { return _player; }
	inline Cursor* getCursor() const { return _cursor; }

	inline int getCurrentZone() const { return _currentZone; }
	inline int getCurrentLevel() const { return _currentLevel; }
};