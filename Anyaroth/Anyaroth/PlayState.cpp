#include "PlayState.h"
#include "Game.h"
#include "BodyComponent.h"
#include "FollowingComponent.h"
#include "checkML.h"
#include "ObjectLayer.h"

PlayState::PlayState(Game* g) : GameState(g)
{
	//Tilemap

	_colLayer = new Layer("Capa de Patrones 1", g->getTexture("tileset"), TILEMAP_PATH + "level.json", g);
	_colLayer->addComponent<BodyComponent>();
	_stages.push_back(_colLayer);

	//brazo de atr�s
	//auto armBack = new Arm(g->getTexture("Armback"), nullptr);
	//_stages.push_back(armBack);

	//cuerpo
	_player = new Player(g->getTexture("Mk"), g, Vector2D(50,0));
	_stages.push_back(_player);

	//Enemy
	 auto oL= new ObjectLayer<MeleeEnemyComponent,Player*>("Capa de Objetos 1", g->getTexture("Mk"), TILEMAP_PATH + "level.json", g, _player);
	 for (int i = 0; i < oL->getNumObjects(); i++)
	 {
		 _stages.push_back(oL->getObject(i));
	 }
	 delete oL;
	 _enemy = new MeleeEnemyComponent(g, g->getTexture("Mk"), Vector2D(50, 100), _player);
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