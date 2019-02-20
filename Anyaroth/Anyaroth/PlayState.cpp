#include "PlayState.h"
#include "Game.h"
#include "BodyComponent.h"
#include "FollowingComponent.h"
#include "checkML.h"

PlayState::PlayState(Game* g) : GameState(g)
{
	//Tilemap

	_colLayer = new Layer("Capa de Patrones 1", g->getTexture("tileset"), TILEMAP_PATH + "level.json", g);
	_colLayer->addComponent<BodyComponent>();
	_stages.push_back(_colLayer);

	//Player
	_player = new Player(g->getTexture("Mk"), g);
	_stages.push_back(_player);

	_mainCamera->fixCameraToObject(_player);

	//Enemy
	_enemy = new MeleeEnemyComponent(_player, g, g->getTexture("Mk"), Vector2D(50, 100));
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