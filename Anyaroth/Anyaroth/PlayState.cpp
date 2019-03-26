#include "PlayState.h"
#include "Game.h"
#include "PauseState.h"
#include "PlayStateHUD.h"
#include "NPC.h"
#include "PiercingBulletPool.h"
#include "checkML.h"
#include <time.h>

PlayState::PlayState(Game* g) : GameState(g)
{
	//Cursor
	_cursor = new Cursor(g);
	_stages.push_back(_cursor);
	//SDL_ShowCursor(false);

	//Player
	_player = new Player(g, 0, 0);
	_stages.push_back(_player);

	//Pool player
	_playerBulletPool = new BulletPool(g);
	_stages.push_back(_playerBulletPool);
	/////////////////////////////////////////////////////////
	_bouncingBulletPool = new BouncingBulletPool(g);
	_stages.push_back(_bouncingBulletPool);



	///
	/*PiercingBulletPool* pPool = new PiercingBulletPool(g);*/

	//_player->setPlayerBulletPool(_bouncingBulletPool);

	_player->setPlayerBulletPool(_playerBulletPool);


	//Pool enemy
	_enemyBulletPool = new BulletPool(g);
	_stages.push_back(_enemyBulletPool);
  
	/*for (int i = 0; i < enemiesPos.size(); i++)
	{
		//_enemy = new MeleeEnemy(_player, g, this, g->getTexture("EnemyMelee"), Vector2D(enemiesPos[i].getX(), enemiesPos[i].getY() - TILES_SIZE * 2), "Enemy");
		_enemy = new MeleeEnemy(_player, g, this, g->newTexture("EnemyMelee" + to_string(i), "EnemyMelee"), Vector2D(enemiesPos[i].getX(), enemiesPos[i].getY() - TILES_SIZE * 2), "Enemy");
		_stages.push_back(_enemy);
		auto itFR = --(_stages.end());
		_enemy->setItList(itFR);
	}*/
  
	_explosivePool = new ExplosiveBulletPool(g);
	_stages.push_back(_explosivePool);

	//Levels
	_currentZone = _currentLevel = 1;
	_levelManager = LevelManager(g, this);
	_levelManager.setLevel(_currentZone, _currentLevel);
  
	/*for (int i = 0; i < marirsPos.size(); i++)
	{
		_enemy = new MartyrEnemy(_player, g, this, g->newTexture("EnemyMartyr" + to_string(i), "EnemyMartyr"), Vector2D(marirsPos[i].getX(), marirsPos[i].getY() - TILES_SIZE * 2), "Enemy");
		_stages.push_back(_enemy);
		auto itFR = --(_stages.end());
		_enemy->setItList(itFR);
	}*/
  
	//Camera
	_mainCamera->fixCameraToObject(_player);
  
  
	//Test NPC*****

	NPC* _npc = new NPC(g, 60, 380,
		{
		g->getTexture("DialogueFace"),
		"exampleVoice",
		"Jose Mar�a",
		{ "*Bzzt..Bip, bip..* Hey, �qu� tal?",
		"Aj�, con que programando... ya veo...",
		"�Pues sigue con eso, chaval! Deja de jugar tanto al Sekiro y ponte a estudiar de una maldita vez, escoria infrahumana (...) �Adew! *Bip*" },
		{0,1,2},
		{" ", " ", " ", " "}
		});

	_stages.push_back(_npc);

	//*******

	//World
	/*_debugger.getRenderer(g->getRenderer());
	_debugger.getTexture(g->getTexture("body"));
	_debugger.SetFlags(b2Draw::e_shapeBit);
	_debugger.getCamera(_mainCamera);
	*/
	//Gestion de colisiones
	g->getWorld()->SetContactListener(&_colManager);
	g->getWorld()->SetDebugDraw(&_debugger);

	//Camera BackGound
	ParallaxBackGround* a = new ParallaxBackGround(_mainCamera);
	a->addLayer(new ParallaxLayer(g->getTexture("BgZ1L1"), _mainCamera, 0.25));
	a->addLayer(new ParallaxLayer(g->getTexture("BgZ1L2"), _mainCamera, 0.5));
	a->addLayer(new ParallaxLayer(g->getTexture("BgZ1L3"), _mainCamera, 0.75));
	_mainCamera->setBackGround(a);



	//HUD
	auto b = new PlayStateHUD(g);
	setCanvas(b);

	//Asignacion de paneles a sus controladores
	_player->setPlayerPanel(b->getPlayerPanel());
	_npc->setDialoguePanel(b->getDialoguePanel());
}

void PlayState::addObject(GameComponent* n)
{
	_stages.push_back(n);
	auto itFR = --(_stages.end());
	n->setItList(itFR);
}

void PlayState::deleteObject(const list<GameObject*>::iterator &itList)
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
		_gameptr->setTimestep(0);
		_gameptr->pushState(new PauseState(_gameptr));
		handled = true;
	}
	else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_0) //Boton de prueba para reiniciar el nivel
		_levelManager.resetLevel();
	else if (e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_KP_MINUS || e.key.keysym.sym == SDLK_MINUS)) //Para probar el Zoom y sus distintan opciones
		_mainCamera->zoomOut();
	else if (e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_KP_PLUS || e.key.keysym.sym == SDLK_PLUS))
		_mainCamera->zoomIn();
	else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_n)
		_mainCamera->setZoom(_mainCamera->getZoomRatio() + 1, true);
	else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_m)
		_mainCamera->setZoom(_mainCamera->getZoomRatio() - 1, true);

	return handled;
}

void PlayState::update(double time)
{
	GameState::update(time);

	if (_player->isDead())
	{
		_player->revive();
		_levelManager.resetLevel();
	}

	int i = items_ToDelete.size() - 1;
	while (i >= 0)
	{
		delete *items_ToDelete[i];
		_stages.erase(items_ToDelete[i]);
		items_ToDelete.pop_back();
		i--;
	}
}