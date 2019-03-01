#include "PlayState.h"
#include "PauseState.h"
#include "Game.h"
#include "BodyComponent.h"
#include "FollowingComponent.h"
#include "checkML.h"
#include "ObjectLayer.h"

PlayState::PlayState(Game* g) : GameState(g)
{
	_game = g;

	//Tilemap
	_layer = new Layer("Mapa", g->getTexture("tileset"), TILEMAP_PATH + "Nivel1.json", g, "Mapa");
	_stages.push_back(_layer);
	_colisionLayer = new Layer("Suelo", g->getTexture("tileset"), TILEMAP_PATH + "Nivel1.json", g, "Suelo");
	_colisionLayer->addComponent<BodyComponent>();
	_stages.push_back(_colisionLayer);

	//Pool arma b�sica
	_examplePool = new BulletPool<100>(g, g->getTexture("PistolBullet"), 100, 10);
	_stages.push_back(_examplePool);

	//Player
	_player = new Player(g->getTexture("Mk"), g, this, "Player");
	_stages.push_back(_player);

	//Camera
	_mainCamera->fixCameraToObject(_player);
	
	 auto oL= new ObjectLayer(TILEMAP_PATH + "Nivel1.json", "Enemigos");
	 vector <Vector2D> enemiesPos = oL->getObjectsPositions();
	 delete oL;

	 for (int i = 0; i < enemiesPos.size(); i++)
	 {
		 _enemy = new MeleeEnemy(_player, g, this, g->getTexture("EnemyMelee"), Vector2D(enemiesPos[i].getX(), enemiesPos[i].getY() - TILES_SIZE * 2), "Enemy");
		_stages.push_back(_enemy);
		auto itFR = --(_stages.end());
		_enemy->setItList(itFR);
	 }


	 oL = new ObjectLayer(TILEMAP_PATH + "Nivel1.json", "Monedas");
	 vector <Vector2D> coinsPos = oL->getObjectsPositions();
	 delete oL;
	 for (int i = 0; i < coinsPos.size(); i++)
	 {
		 _coin = new Coin(this, g, g->getTexture("Coin"), Vector2D(coinsPos[i].getX(), coinsPos[i].getY() - TILES_SIZE), 20);
		 _stages.push_back(_coin);

		 auto itFR = --(_stages.end());
		 _coin->setItList(itFR);
	 }

	 //World
	 _debugger.getRenderer(g->getRenderer());
	 _debugger.getTexture(g->getTexture("body"));
	 _debugger.SetFlags(b2Draw::e_shapeBit);
	 _debugger.getCamera(_mainCamera);

	 //Gestion de colisiones
	 g->getWorld()->SetContactListener(&_colManager);
	 g->getWorld()->SetDebugDraw(&_debugger);
}

void PlayState::KillObject(list<GameObject*>::iterator itList)
{
	items_ToDelete.push_back(itList);
}

bool PlayState::handleEvents(SDL_Event& e)
{
	GameState::handleEvents(e);

	bool handled = false;
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) 
	{
		_game->pushState(new PauseState(_game));
		handled = true;
	}
	return handled;
}

void PlayState::update()
{
	GameState::update();

	int i = items_ToDelete.size() - 1;
	while (i >= 0)
	{
		delete *items_ToDelete[i];
		_stages.erase(items_ToDelete[i]);
		items_ToDelete.pop_back();
		i--;
	}
}