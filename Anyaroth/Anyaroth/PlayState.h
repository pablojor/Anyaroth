#pragma once
#include "GameState.h"
#include "DebugDraw.h"
#include "CollisionManager.h"
#include "Player.h"
#include "BulletPool.h"
#include "Cursor.h"
#include "LevelManager.h"

class PlayState : public GameState
{
private:
	Player* _player = nullptr;
	BulletPool* _playerBulletPool = nullptr; //Balas del jugador
	Cursor* _cursor = nullptr;
	LevelManager* _levelManager = nullptr;

	CollisionManager _colManager;
	DebugDraw _debugger;

	vector <list<GameComponent*>::iterator> itemsToDelete;

public:
	PlayState(Game* g);

	virtual void render() const;
	virtual void update(double time);
	virtual bool handleEvents(SDL_Event& e);

	inline void KillObjects(const list<GameComponent*>::iterator &itList) { itemsToDelete.push_back(itList); }
	inline Cursor* getCursor() const { return _cursor; }
};