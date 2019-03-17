#include "PlayState.h"
#include "PauseState.h"
#include "Game.h"
#include "PlayStateHUD.h"
#include "checkML.h"

PlayState::PlayState(Game* g) : GameState(g)
{
	//Cursor
	_cursor = new Cursor(g->getTexture("GunCursor"), g, this);
	_stages.push_back(_cursor);
	//SDL_ShowCursor(false);

	//Player
	_player = new Player(g, 0, 0);
	_stages.push_back(_player);

	////Pool player
	_playerBulletPool = new BulletPool(g);
	_stages.push_back(_playerBulletPool);
	_player->setPlayerBulletPool(_playerBulletPool);

	//Levels
	_levelManager = new LevelManager(g, this, _player, _stages);
	_stages.push_back(_levelManager);
	_levelManager->setLevel(1, 1);

	//Camera
	_mainCamera->fixCameraToObject(_player);

	//HUD
	auto b = new PlayStateHUD(g);
	setCanvas(b);
	_player->setPlayerPanel(b->getPlayerPanel());

	//World, collisions and debugger
	g->getWorld()->Step(1 / 60.0, 8, 3);

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
		_gameptr->getWorld()->Step(0, 8, 3);
		_gameptr->pushState(new PauseState(_gameptr));
		handled = true;
	}
	return handled;
}

void PlayState::update(double time)
{
	GameState::update(time);

	int i = itemsToDelete.size() - 1;
	while (i >= 0)
	{
		_levelManager->getCurrentMap()->delChild(itemsToDelete[i]);
		itemsToDelete.pop_back();
		i--;
	}
}