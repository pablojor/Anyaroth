#include "PlayState.h"
#include "Game.h"
#include "CollisionManager.h"
#include "FollowingComponent.h"

#include "checkML.h"

PlayState::PlayState(Game* g) : GameState(g)
{


	//Tilemap
	_stages.push_back(new Layer("Capa de Patrones 1", g->getTexture("tileset"), TILEMAP_PATH + "P2.json"));
	_stages.push_back(new Layer("Capa de patrones 2", g->getTexture("tileset"), TILEMAP_PATH + "P2.json"));

	_colLayer = new Layer("Capa de patrones 3", g->getTexture("tileset"), TILEMAP_PATH + "P2.json");
	_colLayer->addComponent<BoxCollider>();
	_stages.push_back(_colLayer);



	//Player

	//brazo de atrás
	//auto armBack = new Arm(g->getTexture("Armback"), nullptr);
	//_stages.push_back(armBack);

	//cuerpo
	_player = new Player(g->getTexture("Mk"), g);
	_stages.push_back(_player);

}

void PlayState::handleEvents(SDL_Event& e)
{
	GameState::handleEvents(e);
}

void PlayState::update()
{
	GameState::update();


	for (int i = 0; i < _colLayer->getTilemap().size(); i++)
	{
		if (CollisionManager::checkCollision(_player, _colLayer->getTilemap()[i]))
			cout << "collided!";
	}
}