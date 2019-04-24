#include "LevelManager.h"
#include "Game.h"
#include "GameManager.h"

LevelManager::LevelManager(Game* game, Player* player, GameObject* level, PlayStateHUD* hud, BulletPool* enemyPool) : _game(game), _player(player), _level(level), _hud(hud)
{
	_enemyBulletPool = enemyPool;

	_tilesetZone1 = game->getTexture("Tileset1");
	_tilesetBoss1 = game->getTexture("TilesetBoss1");
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
		_currentMap = new Map(TILEMAP_PATH + "Nivel1-2.json", _game, _player, _tilesetZone1, _enemyBulletPool, _hud);
		break;
	case LevelManager::SafeBoss1:
		_currentSafeZone = new Map(TILEMAP_PATH + "SafeZonePrueba.json", _game, _player, _tilesetZone1, _enemyBulletPool, _hud);
		break;
	case LevelManager::Boss1:
		_currentMap = new Map(TILEMAP_PATH + "Nivel1-3.json", _game, _player, _tilesetBoss1, _enemyBulletPool, _hud);
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
	case LevelManager::Demo:
		_currentMap = new Map(TILEMAP_PATH + "NivelDemo.json", _game, _player, _tilesetZone1, _enemyBulletPool, _hud);
		break;
	default:
		break;
	}

	if (l % 2 == 0)
		_level->addChild(_currentMap);
	else
		_level->addChild(_currentSafeZone);
	_game->getCurrentState()->getMainCamera()->fadeIn(3000);
}

void LevelManager::changeLevel(int l)
{
	if (_currentSafeZone != nullptr)
	{
		_enemyBulletPool->stopBullets();
		_level->destroyAllChildren();
	}
	else if (_currentMap != nullptr)
	{
		_enemyBulletPool->stopBullets();
		_level->destroyAllChildren();
	}
	setLevel(l);

	_game->getCurrentState()->getMainCamera()->setWorldBounds(getCurrentLevel(GameManager::getInstance()->getCurrentLevel())->getWidth(), getCurrentLevel(GameManager::getInstance()->getCurrentLevel())->getHeight());
	_game->getCurrentState()->getMainCamera()->setZoom(CAMERA_SCALE_FACTOR);
}

Map * LevelManager::getCurrentLevel(int l) const
{
	if (l % 2 == 0)
		return _currentMap;
	else
		return _currentSafeZone;
}

void LevelManager::resetLevel()
{
	_currentMap->restartLevel(); 
	_enemyBulletPool->stopBullets(); 
	_game->getCurrentState()->getMainCamera()->fadeIn(3000);
}
