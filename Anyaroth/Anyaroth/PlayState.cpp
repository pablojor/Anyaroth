#include "PlayState.h"
#include "Game.h"
#include "PauseState.h"
#include "ParallaxLayer.h"
#include "PlayStateHUD.h"
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
	_player->setPlayerBulletPool(_playerBulletPool);

	//Levels
	_currentZone = _currentLevel = 1;
	_levelManager = LevelManager(g, _player, &_stages);
	_levelManager.setLevel(_currentZone, _currentLevel);

	//Background
	_parallaxZone1 = new ParallaxBackGround(_mainCamera);
	_parallaxZone1->addLayer(new ParallaxLayer(g->getTexture("BgZ1L1"), _mainCamera, 0.25));
	_parallaxZone1->addLayer(new ParallaxLayer(g->getTexture("BgZ1L2"), _mainCamera, 0.5));
	_parallaxZone1->addLayer(new ParallaxLayer(g->getTexture("BgZ1L3"), _mainCamera, 0.75));

	//Camera
	_mainCamera->fixCameraToObject(_player);
	_mainCamera->setBackGround(_parallaxZone1);

	//HUD
	auto b = new PlayStateHUD(g);
	setCanvas(b);
	_player->setPlayerPanel(b->getPlayerPanel());

	//Collisions and debugger
	g->getWorld()->SetContactListener(&_colManager);
	g->getWorld()->SetDebugDraw(&_debugger);

	_debugger.getRenderer(g->getRenderer());
	_debugger.getTexture(g->getTexture("body"));
	_debugger.SetFlags(b2Draw::e_shapeBit);
	_debugger.getCamera(_mainCamera);
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
	else if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_KP_MINUS || event.key.keysym.sym == SDLK_MINUS)) //Para probar el Zoom y sus distintan opciones
		_mainCamera->zoomOut();
	else if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_KP_PLUS || event.key.keysym.sym == SDLK_PLUS))
		_mainCamera->zoomIn();
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_z)
		_mainCamera->setZoom(_mainCamera->getZoomRatio() + 1, true);
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_x)
		_mainCamera->setZoom(_mainCamera->getZoomRatio() - 1, true);

	return handled;
}

void PlayState::update(const double& deltaTime)
{
	GameState::update(deltaTime);

	if (_player->isDead())
	{
		_player->revive();
		_levelManager.resetLevel();
	}
}