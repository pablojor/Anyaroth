#include "PlayState.h"
#include "Game.h"
#include "CollisionManager.h"
#include "BodyComponent.h"
#include "DebugDraw.h"

CollisionManager colManager;
DebugDraw debugger;
PlayState::PlayState(Game* g) : GameState(g)
{
	debugger.getRenderer(g->getRenderer());
	debugger.SetFlags(b2Draw::e_shapeBit);
	//World
	_world = new b2World(b2Vec2(0.0, 9.8));
	//Gestion de colisiones
	_world->SetContactListener(&colManager);
	_world->SetDebugDraw(&debugger);
	//Tilemap
	//_stages.push_back(new Layer("Capa de Patrones 1", g->getTexture("tileset"), TILEMAP_PATH + "P2.json", _world));
	//_stages.push_back(new Layer("Capa de patrones 2", g->getTexture("tileset"), TILEMAP_PATH + "P2.json", _world));

	_colLayer = new Layer("Capa de patrones 3", g->getTexture("tileset"), TILEMAP_PATH + "P2.json", _world);
	_colLayer->addComponent<BodyComponent>();
	_stages.push_back(_colLayer);

	//Player
	_player = new Player(g->getTexture("Mk"), _world);
	_stages.push_back(_player);
}

void PlayState::handleEvents(SDL_Event& e)
{
	GameState::handleEvents(e);
}

void PlayState::update()
{
	_world->DrawDebugData();
	_world->Step(1/20.0, 8, 3);
	GameState::update();
}