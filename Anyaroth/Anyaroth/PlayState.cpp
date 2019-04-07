#include "PlayState.h"
#include "Game.h"
#include "PauseState.h"
#include "ParallaxLayer.h"
#include "NPC.h"
#include "PiercingBulletPool.h"
#include "checkML.h"

PlayState::PlayState(Game* g) : GameState(g)
{
	//HUD
	_hud = new PlayStateHUD(g);
	setCanvas(_hud);

	//Cursor
	_cursor = new Cursor(g);
	_stages.push_back(_cursor);
	//SDL_ShowCursor(false);

	//Player
	_player = new Player(g, 100, 500);
	_stages.push_back(_player);

	//Pool player
	_playerBulletPool = new BulletPool(g);
	_stages.push_back(_playerBulletPool);

	_player->setPlayerBulletPool(_playerBulletPool);
	_player->setPlayerPanel(_hud->getPlayerPanel());

	//Levels
	_currentLevel = LevelManager::Level2_1;
	_levelManager = LevelManager(g, _player, &_stages, _hud);
	_levelManager.setLevel(_currentLevel);

	//Background
	_parallaxZone1 = new ParallaxBackGround(_mainCamera);
	_parallaxZone1->addLayer(new ParallaxLayer(g->getTexture("BgZ1L1"), _mainCamera, 0.25));
	_parallaxZone1->addLayer(new ParallaxLayer(g->getTexture("BgZ1L2"), _mainCamera, 0.5));
	_parallaxZone1->addLayer(new ParallaxLayer(g->getTexture("BgZ1L3"), _mainCamera, 0.75));

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
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_1) //Boton de prueba para reiniciar la munición
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
		_currentLevel++;
		_levelManager.changeLevel(_currentLevel);
	}

	if (_player->isDead())
	{
		cout << "player is dead\n";
		_playerBulletPool->stopBullets();
		_player->revive();
		_currentLevel--;
		_levelManager.changeLevel(_currentLevel);
	}

	GameState::update(deltaTime);
}