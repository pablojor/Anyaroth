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
	 auto oL= new ObjectLayer(TILEMAP_PATH + "level.json", "Capa de Objetos 1");
	 vector <Vector2D> enemiesPos = oL->getObjectsPositions();
	 delete oL;
	 for (int i = 0; i < enemiesPos.size(); i++)
	 {
		  _enemy = new MeleeEnemyComponent(g, g->getTexture("Mk"), enemiesPos[i], _player);
		 _stages.push_back(_enemy);
	 }

}

void PlayState::handleEvents(SDL_Event& e)
{
	GameState::handleEvents(e);
}

void PlayState::update()
{
	GameState::update();
}