#include "PlayState.h"
#include "PauseState.h"
#include "Game.h"
#include "BodyComponent.h"
#include "FollowingComponent.h"
#include "checkML.h"
#include "ObjectLayer.h"
#include "Coin.h"
#include "ParallaxBackGround.h"
#include "ParallaxLayer.h"
#include "PlayStateHUD.h"



PlayState::PlayState(Game* g) : GameState(g)
{
	//hide cursor
	//SDL_ShowCursor(false);

	//Tilemap
	_layer = new Layer("Mapa", g->getTexture("tileset"), TILEMAP_PATH + "Nivel1.json", g, "Mapa");
	_stages.push_back(_layer);

	_colisionLayer = new Layer("Suelo", g->getTexture("tileset"), TILEMAP_PATH + "Nivel1.json", g, "Suelo");
	_colisionLayer->addComponent<BodyComponent>();
	_stages.push_back(_colisionLayer);

	////Pool player
	_playerBulletPool = new BulletPool(g);
	_stages.push_back(_playerBulletPool);

	//_enemyPool = new BulletPool(g/*, g->getTexture("PistolBullet"), 100, 10, 1000*/);
	//_stages.push_back(_enemyPool);
	//_pools.push_back(_enemyPool);

	//Player
	_player = new Player(g, 50, 180);
	_stages.push_back(_player);
	_player->setPlayerBulletPool(_playerBulletPool);

	//Camera
	_mainCamera->fixCameraToObject(_player);

	//Enemies
	auto oL = new ObjectLayer(TILEMAP_PATH + "Nivel1.json", "Enemigos");
	vector <Vector2D> enemiesPos = oL->getObjectsPositions();
	delete oL;

	for (int i = 0; i < enemiesPos.size(); i++)
	{
		_enemy = new MeleeEnemy(_player, g, this, g->getTexture("EnemyMelee"), Vector2D(enemiesPos[i].getX(), enemiesPos[i].getY() - TILES_SIZE * 2), "Enemy");
		_stages.push_back(_enemy);
		auto itFR = --(_stages.end());
		_enemy->setItList(itFR);
	}

	oL = new ObjectLayer(TILEMAP_PATH + "Nivel1.json", "Martires");
	vector <Vector2D> marirsPos = oL->getObjectsPositions();
	delete oL;

	for (int i = 0; i < marirsPos.size(); i++)
	{
		_enemy = new MartyrEnemy(_player, g, this, g->getTexture("EnemyMartyr"), Vector2D(marirsPos[i].getX(), marirsPos[i].getY() - TILES_SIZE * 2), "Enemy");
		_stages.push_back(_enemy);
		auto itFR = --(_stages.end());
		_enemy->setItList(itFR);
	}

	oL = new ObjectLayer(TILEMAP_PATH + "Nivel1.json", "Distancia");
	vector <Vector2D> disPos = oL->getObjectsPositions();
	delete oL;

	for (int i = 0; i < disPos.size(); i++)
	{
		if(i==0 ||i==2)
			_enemy = new DistanceStaticEnemy(_player, g, this, g->getTexture("EnemyMartyr"), Vector2D(disPos[i].getX(), disPos[i].getY() - TILES_SIZE * 2), "Enemy", BasicEnemyGun);
		else
			_enemy = new DistanceStaticEnemy(_player, g, this, g->getTexture("EnemyMelee"), Vector2D(disPos[i].getX(), disPos[i].getY() - TILES_SIZE * 2), "Enemy", BasicEnemyShotgun);
		_stages.push_back(_enemy);
		auto itFR = --(_stages.end());
		_enemy->setItList(itFR);
	}

	//Coins
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

	//Camera BackGound
	ParallaxBackGround* a = new ParallaxBackGround(_mainCamera);
	a->addLayer(new ParallaxLayer(g->getTexture("BgZ1L1"), _mainCamera, 0.25));
	a->addLayer(new ParallaxLayer(g->getTexture("BgZ1L2"), _mainCamera, 0.5));
	a->addLayer(new ParallaxLayer(g->getTexture("BgZ1L3"), _mainCamera, 0.75));
	_mainCamera->setBackGround(a);

	//Cursor
	_cursor = new Cursor(g);
	_stages.push_back(_cursor);
	//_player->getWeaponArm()->setCursor(_cursor);

	//HUD
	auto b = new PlayStateHUD(g);
	setCanvas(b);

	//Asignacion de paneles a sus controladores
	_player->setPlayerPanel(b->getPlayerPanel());
}

void PlayState::KillObject(const list<GameObject*>::iterator &itList)
{
	items_ToDelete.push_back(itList);
}

void PlayState::render() const
{
	GameState::render();
}

bool PlayState::handleEvents(SDL_Event& e)
{
	GameState::handleEvents(e);

	bool handled = false;
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
	{
		_gameptr->pushState(new PauseState(_gameptr));
		handled = true;
	}
	return handled;
}

void PlayState::update(double time)
{
	GameState::update(time);

	int i = items_ToDelete.size() - 1;
	while (i >= 0)
	{
		delete *items_ToDelete[i];
		_stages.erase(items_ToDelete[i]);
		items_ToDelete.pop_back();
		i--;
	}
}