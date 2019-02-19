#include "PlayState.h"
#include "Game.h"
#include "BodyComponent.h"
#include "FollowingComponent.h"
#include "checkML.h"

PlayState::PlayState(Game* g) : GameState(g)
{
	initializeCamera();
	//Tilemap
	//_stages.push_back(new Layer("Capa de Patrones 1", g->getTexture("tileset"), TILEMAP_PATH + "P2.json", g));
	//_stages.push_back(new Layer("Capa de patrones 2", g->getTexture("tileset"), TILEMAP_PATH + "P2.json", g));

	_colLayer = new Layer("Capa de patrones 3", g->getTexture("tileset"), TILEMAP_PATH + "P2.json", g);
	_colLayer->addComponent<BodyComponent>();
	_stages.push_back(_colLayer);

	//brazo de atr�s
	//auto armBack = new Arm(g->getTexture("Armback"), nullptr);
	//_stages.push_back(armBack);

	//cuerpo
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