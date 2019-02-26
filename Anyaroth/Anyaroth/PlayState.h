#pragma once
#include "GameState.h"
#include "Layer.h"
#include "Player.h"
#include "DebugDraw.h"
#include "CollisionManager.h"
#include "MeleeEnemy.h"
#include "MartyrEnemy.h"
#include "BulletPool.h"

class Player;

class PlayState : public GameState
{
	private:
		Game* _game = nullptr;
		Player* _player = nullptr;
		Enemy* _enemy = nullptr;
		Layer* _layer = nullptr;
		CollisionManager _colManager;
		DebugDraw _debugger;

		PoolWrapper* _examplePool = nullptr; //TEMPORAL

		vector <list<GameObject*>::iterator> items_ToDelete;

	public:
		PlayState(Game* g);
		void KillObject(list<GameObject*>::iterator itList);
		virtual void update();
		virtual bool handleEvents(SDL_Event& e);
		PoolWrapper* getBulletPool() { return _examplePool; };
};