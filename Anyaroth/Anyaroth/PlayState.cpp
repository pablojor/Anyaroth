#include "PlayState.h"
#include "PauseState.h"
#include "Game.h"
#include "ParallaxBackGround.h"
#include "ParallaxLayer.h"
#include "PlayStateHUD.h"
#include "checkML.h"

PlayState::PlayState(Game* g) : GameState(g)
{
	//hide cursor
	//SDL_ShowCursor(false);

	////Pool player
	_playerBulletPool = new BulletPool(g);
	_stages.push_back(_playerBulletPool);

	//Player
	_player = new Player(g, 50, 180);
	_stages.push_back(_player);
	_player->setPlayerBulletPool(_playerBulletPool);

	//Camera
	_mainCamera->fixCameraToObject(_player);

	//Level1
	_level1 = new Map(TILEMAP_PATH + "Nivel1.json", g->getTexture("tileset"), g, this, _player, _stages);
	delete _level1;

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
	_cursor = new Cursor(g->getTexture("GunCursor"), g, this);
	_stages.push_back(_cursor);

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
		_gameptr->setTimestep(0);
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