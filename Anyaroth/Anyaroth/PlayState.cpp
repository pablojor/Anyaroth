#include "PlayState.h"
#include "Game.h"
#include "PauseState.h"
#include "ParallaxLayer.h"
#include "NPC.h"
#include "PiercingBulletPool.h"
#include "checkML.h"
#include "Boss2.h"
#include "WeaponManager.h"

PlayState::PlayState(Game* g) : GameState(g)
{
	//Inicializa el manager de armas
	WeaponManager::init();

	//HUD
	_hud = new PlayStateHUD(g);
	setCanvas(_hud);

	//Player
	_player = new Player(g, 100, 300);
	_stages.push_back(_player);

	_player->setPlayerPanel(_hud->getPlayerPanel());

	_hud->getShop()->setPlayer(_player);
	_hud->getShop()->setVisible(false);

	//Pool player
	_playerBulletPool = new BulletPool(g);
	auto enemyPool = new BulletPool(g);

	_player->setPlayerBulletPool(_playerBulletPool);

	//Levels
	_currentLevel = LevelManager::Boss2;
	_levelManager = LevelManager(g, _player, &_stages, _hud, enemyPool);
	_levelManager.setLevel(_currentLevel);
	
	//Background
	_parallaxZone1 = new ParallaxBackGround(_mainCamera);
	_parallaxZone1->addLayer(new ParallaxLayer(g->getTexture("BgZ1L1"), _mainCamera, 0.25));
	_parallaxZone1->addLayer(new ParallaxLayer(g->getTexture("BgZ1L2"), _mainCamera, 0.5));
	_parallaxZone1->addLayer(new ParallaxLayer(g->getTexture("BgZ1L3"), _mainCamera, 0.75));

	//Cursor
	_cursor = new Cursor(g);
	_stages.push_back(_cursor);
	SDL_ShowCursor(false);
	//Balas se renderizan al final
	_stages.push_back(_playerBulletPool);
	_stages.push_back(enemyPool);

	//Camera
	_mainCamera->fixCameraToObject(_player);
	_mainCamera->setBackGround(_parallaxZone1);


	//Collisions and debugger
	g->getWorld()->SetContactListener(&_colManager);
	g->getWorld()->SetDebugDraw(&_debugger);

	//World
	_debugger.getRenderer(g->getRenderer());
	_debugger.getTexture(g->getTexture("Box"));
	_debugger.SetFlags(b2Draw::e_shapeBit);
	_debugger.getCamera(_mainCamera);
	
	//Gestion de colisiones
	g->getWorld()->SetContactListener(&_colManager);
	g->getWorld()->SetDebugDraw(&_debugger);

	deathText = new TextUI(_gameptr, "ANYAHILATED", _gameptr->getFont("ARIAL12"), 50, CAMERA_RESOLUTION_X / 2 - 50, CAMERA_RESOLUTION_Y / 2 - 10, { 255,0,0,1 });
	deathText->setVisible(false);
	_hud->addUIElement(deathText);
}


void PlayState::render() const
{
	GameState::render();
}

bool PlayState::handleEvent(const SDL_Event& event)
{
	GameState::handleEvent(event);

	bool handled = false;
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
	{
		_gameptr->setTimestep(0);
		_gameptr->pushState(new PauseState(_gameptr));
		handled = true;
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_0) //Boton de prueba para reiniciar el nivel
		_levelManager.resetLevel();
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_1) //Boton de prueba para reiniciar la munici�n
	{
		_player->getCurrentGun()->resetAmmo();
		_hud->getPlayerPanel()->updateAmmoViewer(_player->getCurrentGun()->getClip(), _player->getCurrentGun()->getMagazine());
	}
	else if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_KP_MINUS || event.key.keysym.sym == SDLK_MINUS)) //Para probar el Zoom y sus distintan opciones
		_mainCamera->zoomOut();
	else if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_KP_PLUS || event.key.keysym.sym == SDLK_PLUS))
		_mainCamera->zoomIn();
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_n)
		_mainCamera->setZoom(_mainCamera->getZoomRatio() + 1, true);
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_m)
		_mainCamera->setZoom(_mainCamera->getZoomRatio() - 1, true);

	return handled;
}

void PlayState::update(const double& deltaTime)
{
	if (_player->changeLevel())
	{
		_player->setChangeLevel(false);
		_player->revive();
		_currentLevel++;
		_levelManager.changeLevel(_currentLevel);
	}

	if (_player->isDead() && !_killed)
	{
		deathText->setVisible(true);
		_killed = true;
		_player->setStopped(true);
	}
	if (_killed && deathTimer > deathTime)
	{
		_playerBulletPool->stopBullets();
		_player->revive();
		_currentLevel--;
		_levelManager.changeLevel(_currentLevel);
		deathTimer = 0;
		_killed = false;
		deathText->setVisible(false);
	}
	else if (_killed)
		deathTimer += deltaTime;

	GameState::update(deltaTime);
}