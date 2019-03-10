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
#include "Cursor.h"
#include "GunType_def.h"


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
		Cursor* _cursor = nullptr;

		//Bullet Pools
		vector<PoolWrapper*> _pools;

		vector <list<GameObject*>::iterator> items_ToDelete;
		
		//vector con los índices de las armas que el jugador lleva en el inventario este nivel
		//Se pasa al state que corresponda al cambiar de nivel y el state lo consulta para crear las armas
		vector <GunType> _selectedGuns; 

	public:
		PlayState(Game* g);
		void KillObject(const list<GameObject*>::iterator &itList);
		virtual void render();
		virtual void update();
		virtual bool handleEvents(SDL_Event& e);
		inline PoolWrapper* getBulletPool(int index) { return _pools[index]; };
		Cursor* getCursor() { return _cursor; };
};