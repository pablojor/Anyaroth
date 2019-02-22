#include "PlayState.h"
#include "Game.h"
#include "BodyComponent.h"
#include "FollowingComponent.h"
#include "checkML.h"

PlayState::PlayState(Game* g) : GameState(g)
{
	//Tilemap
	//_stages.push_back(new Layer("Capa de Patrones 1", g->getTexture("tileset"), TILEMAP_PATH + "P2.json", g));
	//_stages.push_back(new Layer("Capa de patrones 2", g->getTexture("tileset"), TILEMAP_PATH + "P2.json", g));

	_colLayer = new Layer("Capa de patrones 3", g->getTexture("tileset"), TILEMAP_PATH + "P2.json", g);
	_colLayer->addComponent<BodyComponent>();
	_stages.push_back(_colLayer);

	//----Pools de balas

	//Pool arma básica
	_examplePool = new BulletPool<100>(g, g->getTexture("example1"), 10, 10);
	_stages.push_back(_examplePool);

	//cuerpo
	_player = new Player(g->getTexture("Mk"), g, this);
	_stages.push_back(_player);

	//Enemy 
	_enemy = new MartyrEnemy(_player, g,this, g->getTexture("Mk"), Vector2D(50, 100));
	_stages.push_back(_enemy);

	auto itFR = --(_stages.end());
	_enemy->setItList(itFR);
}

void PlayState::KillObject(list<GameObject*>::iterator itList)
{
	delete *itList;
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
		_stages.erase(items_ToDelete[i]);
		items_ToDelete.pop_back();
		i--;
	}
}