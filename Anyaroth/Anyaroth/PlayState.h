#pragma once
#include "GameState.h"
#include "Player.h"
#include "DebugDraw.h"
#include "CollisionManager.h"
#include "BulletPool.h"
#include "Cursor.h"
#include "Map.h"

class PlayState : public GameState
{
private:
	Player* _player = nullptr;
	Cursor* _cursor = nullptr;
	Map* _level1 = nullptr;
	CollisionManager _colManager;
	DebugDraw _debugger;

	//Bullet Pools
	BulletPool* _playerBulletPool = nullptr; //Balas del jugador

	vector <list<GameObject*>::iterator> items_ToDelete;

public:
	PlayState(Game* g);

	virtual void render() const;
	virtual void update(double time);
	virtual bool handleEvents(SDL_Event& e);

	void KillObject(const list<GameObject*>::iterator &itList);
	inline Cursor* getCursor() const { return _cursor; }
};