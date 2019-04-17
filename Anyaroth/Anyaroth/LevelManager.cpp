#include "LevelManager.h"
#include "Game.h"

LevelManager::LevelManager(Game* game, Player* player, list<GameObject*>* objects, PlayStateHUD* hud, BulletPool* enemyPool) : _game(game), _player(player), _hud(hud), _objectList(objects)
{
	_enemyBulletPool = enemyPool;

	_tilesetZone1 = game->getTexture("Tileset1");
	_tilesetZone2 = game->getTexture("Tileset2");
}

void LevelManager::setLevel(int l)
{
	switch (l)
	{
	case LevelManager::Tutorial:
		//_currentMap = ...
		break;
	case LevelManager::Safe1_1:
		_currentSafeZone = new Map(TILEMAP_PATH + "SafeZonePrueba.json", _game, _player, _tilesetZone1, _enemyBulletPool, _hud);
		break;
	case LevelManager::Level1_1:
		_currentMap = new Map(TILEMAP_PATH + "Nivel1-1.json", _game, _player, _tilesetZone1, _enemyBulletPool, _hud);
		break;
	case LevelManager::Safe1_2:
		_currentSafeZone = new Map(TILEMAP_PATH + "SafeZonePrueba.json", _game, _player, _tilesetZone1, _enemyBulletPool, _hud);
		break;
	case LevelManager::Level1_2:
		//_currentMap = ...
		break;
	case LevelManager::SafeBoss1:
		_currentSafeZone = new Map(TILEMAP_PATH + "SafeZonePrueba.json", _game, _player, _tilesetZone1, _enemyBulletPool, _hud);
		break;
	case LevelManager::Boss1:
		_currentMap = new Map(TILEMAP_PATH + "Nivel1-3.json", _game, _player, _tilesetZone1, _enemyBulletPool, _hud);
		break;
	case LevelManager::Safe2_1:
		_currentSafeZone = new Map(TILEMAP_PATH + "SafeZonePrueba.json", _game, _player, _tilesetZone1, _enemyBulletPool, _hud);
		break;
	case LevelManager::Level2_1:
		_currentMap = new Map(TILEMAP_PATH + "Nivel2-1.json", _game, _player, _tilesetZone2, _enemyBulletPool, _hud);
		break;
	case LevelManager::Safe2_2:
		_currentSafeZone = new Map(TILEMAP_PATH + "SafeZonePrueba.json", _game, _player, _tilesetZone1, _enemyBulletPool, _hud);
		break;
	case LevelManager::Level2_2:
		_currentMap = new Map(TILEMAP_PATH + "Nivel2-2.json", _game, _player, _tilesetZone2, _enemyBulletPool, _hud);
		break;
	case LevelManager::SafeBoss2:
		_currentSafeZone = new Map(TILEMAP_PATH + "SafeZonePrueba.json", _game, _player, _tilesetZone1, _enemyBulletPool, _hud);
		break;
	case LevelManager::Boss2:
		//_currentMap = ...
		break;
	case LevelManager::Safe3_1:
		//_currentSafeZone = ...
		break;
	case LevelManager::Level3_1:
		//_currentMap = ...
		break;
	case LevelManager::Safe3_2:
		//_currentSafeZone = ...
		break;
	case LevelManager::Level3_2:
		//_currentMap = ...
		break;
	case LevelManager::SafeBoss3:
		//_currentSafeZone = ...
		break;
	case LevelManager::Boss3:
		//_currentMap = ...
		break;
	default:
		break;
	}

	if (l % 2 == 0)
		_objectList->push_back(_currentMap);
	else
		_objectList->push_back(_currentSafeZone);
}

void LevelManager::changeLevel(int l)
{
	if (_currentSafeZone != nullptr)
	{
		_objectList->remove(_currentSafeZone);
		delete _currentSafeZone;
		_currentSafeZone = nullptr;
	}
	else if (_currentMap != nullptr)
	{
		_enemyBulletPool->stopBullets();
		_objectList->remove(_currentMap);
		delete _currentMap;
		_currentMap = nullptr;
	}
	setLevel(l);
}