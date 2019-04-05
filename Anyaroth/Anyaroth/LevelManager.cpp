#include "LevelManager.h"
#include "Game.h"

LevelManager::LevelManager(Game* game, Player* player, list<GameObject*>* objects, PlayStateHUD* hud) : _game(game), _player(player), _hud(hud), _objectList(objects)
{
	_enemyBulletPool = new BulletPool(game);
	_objectList->push_back(_enemyBulletPool);

	_tilesetZone1 = game->getTexture("tilesetZona1");
}

void LevelManager::setLevel(int zone, int level)
{
	switch (zone)
	{
	case 1:
		switch (level)
		{
		case 1:
			_currentMap = new Map(TILEMAP_PATH + "Nivel1.json", _game, _player, _tilesetZone1, _enemyBulletPool, _hud, 10);
			_objectList->push_back(_currentMap);
			break;
		case 2:
			_currentMap = new Map(TILEMAP_PATH + "ArenaBoss1.json", _game, _player, _tilesetZone1, _enemyBulletPool, _hud, 10);
			_objectList->push_back(_currentMap);
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
	_objectList->remove(_currentMap);
	delete _currentMap;
	setLevel(zone, level);
}