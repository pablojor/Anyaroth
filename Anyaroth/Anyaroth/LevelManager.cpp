#include "LevelManager.h"
#include "Game.h"

LevelManager::LevelManager(Game* game, Player* player, list<GameObject*>* objects, PlayStateHUD* hud) : _game(game), _player(player), _hud(hud), _objectList(objects)
{
	_enemyBulletPool = new BulletPool(game);
	_objectList->push_back(_enemyBulletPool);

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
		//_currentSafeZone = ...
		break;
	case LevelManager::Level1_1:
		_currentMap = new Map(TILEMAP_PATH + "Nivel1-1.json", _game, _player, _tilesetZone1, _enemyBulletPool, _hud, 10);
		break;
	case LevelManager::Safe1_2:
		//_currentSafeZone = ...
		break;
	case LevelManager::Level1_2:
		//_currentMap = ...
		break;
	case LevelManager::SafeBoss1:
		//_currentSafeZone = ...
		break;
	case LevelManager::Boss1:
		_currentMap = new Map(TILEMAP_PATH + "Nivel1-3.json", _game, _player, _tilesetZone1, _enemyBulletPool, _hud, 10);
		break;
	case LevelManager::Safe2_1:
		//_currentSafeZone = ...
		break;
	case LevelManager::Level2_1:
		_currentMap = new Map(TILEMAP_PATH + "Nivel2-1.json", _game, _player, _tilesetZone2, _enemyBulletPool, _hud, 10);
		break;
	case LevelManager::Safe2_2:
		//_currentSafeZone = ...
		break;
	case LevelManager::Level2_2:
		_currentMap = new Map(TILEMAP_PATH + "Nivel2-2.json", _game, _player, _tilesetZone2, _enemyBulletPool, _hud, 10);
		break;
	case LevelManager::SafeBoss2:
		//_currentSafeZone = ...
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

void LevelManager::nextLevel(int l)
{
	if (_currentMap != nullptr)
	{
		_objectList->remove(_currentMap);
		delete _currentMap;
		_currentMap = nullptr;

		if (_currentSafeZone != nullptr && !_currentSafeZone->isActive())
		{
			_objectList->remove(_currentSafeZone);
			delete _currentSafeZone;
			_currentSafeZone = nullptr;
		}

		setLevel(l);
	}
	else if (_currentSafeZone != nullptr)
	{
		_currentSafeZone->setActive(false);

		if (_currentMap == nullptr)
			setLevel(l);
		else
			_currentMap->setActive(true);
	}
}

void LevelManager::previousLevel(int l)
{
	resetLevel();
	_currentMap->setActive(false);
	_currentSafeZone->setActive(true);
}