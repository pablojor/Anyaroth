#pragma once
#include "GameState.h"
#include "Layer.h"
#include "Player.h"
#include "MeleeEnemy.h"
#include "MartyrEnemy.h"
#include "DistanceStaticEnemy.h"
#include "BulletPool.h"

class Player;

class PlayState : public GameState
{
	private:
		Player* _player = nullptr;
		Layer* _colLayer = nullptr;
		Enemy* _enemy = nullptr;

		PoolWrapper* _enemyPool = nullptr; //TEMPORAL
		//Bullet Pools
		PoolWrapper* _basicBulletPool = nullptr; //balas b�sicas
		PoolWrapper* _basicShotgunBulletPool = nullptr; //balas de escopeta
		vector<PoolWrapper*> _pools;

		vector <list<GameObject*>::iterator> items_ToDelete;

	public:
		PlayState(Game* g);
		void KillObject(list<GameObject*>::iterator itList);
		virtual void update();
		virtual void handleEvents(SDL_Event& e);
		PoolWrapper* getBulletPool(int index) { return _pools[index]; };
};