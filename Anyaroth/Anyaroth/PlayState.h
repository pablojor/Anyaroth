#pragma once
#include "GameState.h"
#include "Layer.h"
#include "Player.h"
#include "DebugDraw.h"
#include "CollisionManager.h"
#include "MeleeEnemy.h"
#include "MartyrEnemy.h"
#include "DistanceStaticEnemy.h"
#include "DistanceDynamicEnemy.h"
#include "BulletPool.h"
#include "Coin.h"


class PlayState : public GameState
{
	private:
		Game* _game = nullptr;
		Player* _player = nullptr;
		Enemy* _enemy = nullptr;
		Coin* _coin = nullptr;
		Layer* _layer = nullptr;
		Layer* _colisionLayer = nullptr;
		b2World* _world;
		CollisionManager _colManager;
		DebugDraw _debugger;

		PoolWrapper* _enemyPool = nullptr; //TEMPORAL
		//Bullet Pools
		PoolWrapper* _basicBulletPool = nullptr; //balas b�sicas
		PoolWrapper* _basicShotgunBulletPool = nullptr; //balas de escopeta
		vector<PoolWrapper*> _pools;

		vector <list<GameObject*>::iterator> items_ToDelete;

	public:
		PlayState(Game* g);
		void KillObject(list<GameObject*>::iterator itList);
		virtual void render();
		virtual void update();
		virtual bool handleEvents(SDL_Event& e);
		inline PoolWrapper* getBulletPool(int index) { return _pools[index]; };
};