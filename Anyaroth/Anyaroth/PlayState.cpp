#include "PlayState.h"
#include "Game.h"
#include "PauseState.h"
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

	//Pool enemy
	_enemyBulletPool = new BulletPool(g);
	_stages.push_back(_enemyBulletPool);

	_explosivePool = new ExplosiveBulletPool(g);
	_stages.push_back(_explosivePool);

	//Levels
	_currentZone = _currentLevel = 1;
	_levelManager = LevelManager(g, this);
	_levelManager.setLevel(_currentZone, _currentLevel);

	//Camera
	_mainCamera->fixCameraToObject(_player);

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
	else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_z)
		_mainCamera->setZoom(_mainCamera->getZoomRatio() + 1, true);
	else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_x)
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
}