#include "PlayState.h"
#include "Game.h"
#include "CollisionManager.h"


PlayState::PlayState(Game* g) : GameState(g)
{
	//Tilemap
	_stages.push_back(new Layer("Capa de Patrones 1", g->getTexture("tileset"), TILEMAP_PATH + "P2.json"));
	_stages.push_back(new Layer("Capa de patrones 2", g->getTexture("tileset"), TILEMAP_PATH + "P2.json"));

	_colLayer = new Layer("Capa de patrones 3", g->getTexture("tileset"), TILEMAP_PATH + "P2.json");
	_colLayer->addComponent<BoxCollider>();
	//_colLayer->
	_stages.push_back(_colLayer);

	//Player
	_player = new Player(g->getTexture("Mk"));
	_stages.push_back(_player);

	//Enemy
	_enemy = new Enemy(g->getTexture("Mk"), Vector2D(1200, 100), _player);
	_stages.push_back(_enemy);
}

void PlayState::handleEvents(SDL_Event& e)
{
	GameState::handleEvents(e);
}

void PlayState::update()
{
	GameState::update();
}