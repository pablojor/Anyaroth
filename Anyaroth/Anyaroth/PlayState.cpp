#include "PlayState.h"
#include "Game.h"
#include "BodyComponent.h"
#include "FollowingComponent.h"
#include "checkML.h"
#include "Coin.h"
#include "ParallaxBackGround.h"
#include "ParallaxLayer.h"
#include "PlayStateHUD.h"

PlayState::PlayState(Game* g) : GameState(g)
{
	//Tilemap

	_colLayer = new Layer("Capa de Patrones 1", g->getTexture("tileset"), TILEMAP_PATH + "level.json", g, "Suelo");
	_colLayer->addComponent<BodyComponent>();
	_stages.push_back(_colLayer);

	//----Pools de balas

	//Pools balas
	_basicBulletPool = new BulletPool<100>(g, g->getTexture("PistolBullet"), 100, 10, 1000);
	_stages.push_back(_basicBulletPool);
	_pools.push_back(_basicBulletPool);

	_basicShotgunBulletPool = new BulletPool<100>(g, g->getTexture("PistolBullet"), 100, 25, 60);
	_stages.push_back(_basicShotgunBulletPool);
	_pools.push_back(_basicShotgunBulletPool);

	_enemyPool = new BulletPool<100>(g, g->getTexture("PistolBullet"), 100, 10);
	_stages.push_back(_enemyPool);

	//cuerpo
	_player = new Player(g->getTexture("Mk"), g, this, "Player");
	_stages.push_back(_player);

	_mainCamera->fixCameraToObject(_player);

	//Enemy

	_enemy = new DistanceDynamicEnemy(_player, g, this, g->getTexture("EnemyMelee"), Vector2D(260, 60), "Enemy");
	_stages.push_back(_enemy);

	auto itFR = --(_stages.end());
	_enemy->setItList(itFR);
  
	Coin* coin = new Coin(this, g, g->getTexture("Coin"), Vector2D(100, 100), 20);
	_stages.push_back(coin);

	itFR = --(_stages.end());
	coin->setItList(itFR);	
	
	//Camera BackGound
	/*ParallaxBackGround* a = new ParallaxBackGround(_mainCamera);
	a->addLayer(new ParallaxLayer(g->getTexture("Parallax"), _mainCamera));
	_mainCamera->setBackGround(a);*/

	//HUD
	setCanvas(new PlayStateHUD(g));	
}

void PlayState::KillObject(list<GameObject*>::iterator itList)
{
	//delete *itList;
	items_ToDelete.push_back(itList);
}


void PlayState::handleEvents(SDL_Event& e)
{
	GameState::handleEvents(e);
}

void PlayState::update()
{
	GameState::update();

	int i = items_ToDelete.size() - 1;
	while (i >= 0)
	{
		delete *items_ToDelete[i];
		_stages.erase(items_ToDelete[i]);
		items_ToDelete.pop_back();
		i--;
	}
}