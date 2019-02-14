#include "PlayState.h"
#include "Game.h"
#include "CollisionManager.h"
#include "BodyComponent.h"

CollisionManager colManager;

PlayState::PlayState(Game* g) : GameState(g)
{
	//World
	_world = new b2World(b2Vec2(0.0, 9.8));
	//Gestion de colisiones
	_world->SetContactListener(&colManager);

	//Tilemap
	//_stages.push_back(new Layer("Capa de Patrones 1", g->getTexture("tileset"), TILEMAP_PATH + "P2.json", _world));
	//_stages.push_back(new Layer("Capa de patrones 2", g->getTexture("tileset"), TILEMAP_PATH + "P2.json", _world));

	_colLayer = new Layer("Capa de patrones 3", g->getTexture("tileset"), TILEMAP_PATH + "P2.json", _world);
	_colLayer->addComponent<BodyComponent>();
	_stages.push_back(_colLayer);

	//Player
	_player = new Player(g->getTexture("Mk"), _world);
	_stages.push_back(_player);
	_world->DrawDebugData();
}

void PlayState::handleEvents(SDL_Event& e)
{
	GameState::handleEvents(e);
}

void PlayState::update()
{
	_world->Step(1/20.0, 8, 3);
	GameState::update();
}