#include "PlayState.h"
#include "Game.h"


PlayState::PlayState(Game* g) : GameState(g)
{
	//Collision Manager
	_colManager->getCollisionManager();

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
};

void PlayState::handleEvents(SDL_Event& e)
{
	GameState::handleEvents(e);
}

void PlayState::update()
{
	GameState::update();
	

	for (int i = 0; i < _colLayer->getTilemap().size(); i++)
	{
		if(_colManager->checkCollision(_player, _colLayer->getTilemap()[i]))
			cout << "collided!";
	}
}