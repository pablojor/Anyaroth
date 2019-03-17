#include "LevelManager.h"
#include "Game.h"
#include "PlayState.h"
#include "ParallaxLayer.h"

LevelManager::LevelManager(Game* g, PlayState* playstate, Player* player, list<GameObject*>& list) : _game(g), _playState(playstate), _player(player)
{
	_stages = &list;

	_mainCamera = _playState->getMainCamera();

	_tilesetZone1 = g->getTexture("tileset");

	_parallaxZone1 = new ParallaxBackGround(_mainCamera);
	_parallaxZone1->addLayer(new ParallaxLayer(g->getTexture("BgZ1L1"), playstate->getMainCamera(), 0.25));
	_parallaxZone1->addLayer(new ParallaxLayer(g->getTexture("BgZ1L2"), playstate->getMainCamera(), 0.5));
	_parallaxZone1->addLayer(new ParallaxLayer(g->getTexture("BgZ1L3"), playstate->getMainCamera(), 0.75));
}

LevelManager::~LevelManager()
{

}

void LevelManager::setLevel(int zone, int level)
{
	switch (zone)
	{
	case 1:
		_currentMap = new Map(TILEMAP_PATH + "Nivel1-" + to_string(level) + ".json", _tilesetZone1, _game, _playState, _player);
		_stages->push_back(_currentMap);
		_it = --_stages->end();

		_mainCamera->setBackGround(_parallaxZone1);
	default:
		break;
	}
}

void LevelManager::changeLevel(int zone, int level)
{
	delete _currentMap;
	_stages->erase(_it);
	setLevel(zone, level);
}