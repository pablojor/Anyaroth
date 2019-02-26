#include "PlayState.h"
#include "PauseState.h"
#include "Game.h"
#include "BodyComponent.h"
#include "FollowingComponent.h"
#include "checkML.h"
#include "Coin.h"

PlayState::PlayState(Game* g) : GameState(g)
{
	_game = g;

	//World
	_debugger.getRenderer(g->getRenderer());
	_debugger.getTexture(g->getTexture("body"));
	_debugger.SetFlags(b2Draw::e_shapeBit);

	//Gestion de colisiones
	g->getWorld()->SetContactListener(&_colManager);
	//g->getWorld()->SetDebugDraw(&_debugger);

	//Tilemap
	_layer = new Layer("Capa de Patrones 1", g->getTexture("tileset"), TILEMAP_PATH + "Nivel1.json", g, "Suelo");
	_layer->addComponent<BodyComponent>();
	_stages.push_back(_layer);

	//Pool arma b�sica
	_examplePool = new BulletPool<100>(g, g->getTexture("PistolBullet"), 100, 10);
	_stages.push_back(_examplePool);

	//Player
	_player = new Player(g->getTexture("Mk"), g, this, "Player");
	_stages.push_back(_player);

	_mainCamera->fixCameraToObject(_player);

	//Enemy
	_enemy = new MeleeEnemy(_player, g, this, g->getTexture("EnemyMelee"), Vector2D(260, 60), "Enemy");
	_stages.push_back(_enemy);
	
	//Coin
	Coin* coin = new Coin(this, g, g->getTexture("Coin"), Vector2D(100, 75), 20);
	_stages.push_back(coin);

	auto itFR = --(_stages.end());
	coin->setItList(itFR);
	itFR = --(_stages.end());
	_enemy->setItList(itFR);
}

void PlayState::KillObject(list<GameObject*>::iterator itList)
{
	//delete *itList;
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