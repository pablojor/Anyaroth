#include "LevelManager.h"
#include "Game.h"
#include "ParallaxLayer.h"

LevelManager::LevelManager(Game* game, PlayState* playstate) : _game(game), _playState(playstate)
{
	_player = playstate->getPlayer();
	_mainCamera = playstate->getMainCamera();
	_stages = &playstate->getObjects();

	_tilesetZone1 = game->getTexture("tileset");

	_parallaxZone1 = new ParallaxBackGround(_mainCamera);
	_parallaxZone1->addLayer(new ParallaxLayer(game->getTexture("BgZ1L1"), playstate->getMainCamera(), 0.25));
	_parallaxZone1->addLayer(new ParallaxLayer(game->getTexture("BgZ1L2"), playstate->getMainCamera(), 0.5));
	_parallaxZone1->addLayer(new ParallaxLayer(game->getTexture("BgZ1L3"), playstate->getMainCamera(), 0.75));
}

LevelManager::~LevelManager()
{

}

void LevelManager::setLevel(int zone, int level)
{
	switch (zone)
	{
	case 1:
		_mainCamera->setBackGround(_parallaxZone1);
		switch (level)
		{
		case 1:
			_currentMap = new Map(TILEMAP_PATH + "Nivel1.json", _game, _playState, _tilesetZone1, 10);
			_stages->push_back(_currentMap);
			_itMap = --_stages->end();
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
		}
		break;
	case 2:
		break;
	case 3:
		break;
	default:
		break;
	}
}

void LevelManager::changeLevel(int zone, int level)
{
	delete _currentMap;
	_stages->erase(_itMap);
	setLevel(zone, level);
}

void LevelManager::resetLevel()
{
	changeLevel(_playState->getCurrentZone(), _playState->getCurrentLevel());
}