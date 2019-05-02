#include "LevelManager.h"
#include "Game.h"
#include "GameManager.h"
#include "ParallaxLayer.h"
#include "CutScene.h"

LevelManager::LevelManager(Game* game, Player* player, GameObject* level, BulletPool* enemyPool) : _game(game), _player(player), _level(level), _enemyBulletPool(enemyPool)
{
	_camera = game->getCurrentState()->getMainCamera();

	_tilesetZone1 = game->getTexture("Tileset1");
	_tilesetBoss1 = game->getTexture("TilesetBoss1");

	_tilesetZone2 = game->getTexture("Tileset2");
}

void LevelManager::setLevel(int l)
{
	CutScene* cutscene;

	switch (l)
	{
	case LevelManager::Tutorial:
		//_currentMap = ...
		break;
	case LevelManager::Safe1_1:
		_currentSafeZone = new Map(TILEMAP_PATH + "SafeZonePrueba.json", _game, _player, _tilesetZone1, _enemyBulletPool);
		break;
	case LevelManager::Level1_1:
		_currentMap = new Map(TILEMAP_PATH + "Nivel1-1.json", _game, _player, _tilesetZone1, _enemyBulletPool);
		break;
	case LevelManager::Safe1_2:
		_currentSafeZone = new Map(TILEMAP_PATH + "SafeZonePrueba.json", _game, _player, _tilesetZone1, _enemyBulletPool);
		break;
	case LevelManager::Level1_2:
		_currentMap = new Map(TILEMAP_PATH + "Nivel1-2.json", _game, _player, _tilesetZone1, _enemyBulletPool);
		break;
	case LevelManager::SafeBoss1:
		_currentSafeZone = new Map(TILEMAP_PATH + "SafeZonePrueba.json", _game, _player, _tilesetZone1, _enemyBulletPool);
		break;
	case LevelManager::Boss1:
		_currentMap = new Map(TILEMAP_PATH + "Nivel1-3.json", _game, _player, _tilesetBoss1, _enemyBulletPool);
		break;
	case LevelManager::Safe2_1:
		_currentSafeZone = new Map(TILEMAP_PATH + "SafeZonePrueba.json", _game, _player, _tilesetZone1, _enemyBulletPool);
		break;
	case LevelManager::Level2_1:
		_currentMap = new Map(TILEMAP_PATH + "Nivel2-1.json", _game, _player, _tilesetZone2, _enemyBulletPool);
		break;
	case LevelManager::Safe2_2:
		_currentSafeZone = new Map(TILEMAP_PATH + "SafeZonePrueba.json", _game, _player, _tilesetZone1, _enemyBulletPool);
		break;
	case LevelManager::Level2_2:
		_currentMap = new Map(TILEMAP_PATH + "Nivel2-2.json", _game, _player, _tilesetZone2, _enemyBulletPool);
		break;
	case LevelManager::SafeBoss2:
		_currentSafeZone = new Map(TILEMAP_PATH + "SafeZonePrueba.json", _game, _player, _tilesetZone1, _enemyBulletPool);
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

		//Demo Guerrilla Game Festival
	case LevelManager::SafeDemo:	
		_currentSafeZone = new Map(TILEMAP_PATH + "SafeZoneDemo.json", _game, _player, _tilesetZone1, _enemyBulletPool);
		_game->getSoundManager()->playMusic("safe_zone", -1);
		setParallaxZone1();
		break;
	case LevelManager::LevelDemo:
		_currentMap = new Map(TILEMAP_PATH + "NivelDemo.json", _game, _player, _tilesetZone1, _enemyBulletPool);
		_game->getSoundManager()->playMusic("demoLevelMusic", -1);
		setParallaxZone1();
		break;
	case LevelManager::SafeBossDemo:
		_currentSafeZone = new Map(TILEMAP_PATH + "SafeZoneBossDemo.json", _game, _player, _tilesetZone1, _enemyBulletPool);
		_game->getSoundManager()->playMusic("safe_zone", -1);
		setParallaxZone1();

		cutscene = new CutScene(_player);

		if (_player->getComponent<CustomAnimatedSpriteComponent>()->isFlipped())
			cutscene->addFlipEvent();

		cutscene->addMoveEvent(_player->getComponent<BodyComponent>(), 1, 15, (304 / 2) / M_TO_PIXEL);
		cutscene->addWaitEvent(1000);
		cutscene->addFlipEvent();
		cutscene->addWaitEvent(1000);
		cutscene->addFlipEvent();
		cutscene->addWaitEvent(1000);
		cutscene->addDialogueEvent(_game->getCurrentState()->getPlayHUD()->getDialoguePanel(), _game->getDialogue("First safezone"));
		cutscene->addWaitEvent(1000);
		cutscene->addFlipEvent();
		cutscene->addWaitEvent(1000);
		cutscene->addFlipEvent();
		cutscene->addWaitEvent(1000);
		cutscene->addMoveEvent(_player->getComponent<BodyComponent>(), 1, 15, 304 / M_TO_PIXEL);
		cutscene->addShopEvent(_game->getCurrentState()->getPlayHUD()->getShop());
		_game->getCurrentState()->addCutScene(cutscene);

		break;
	case LevelManager::BossDemo:
		_currentMap = new Map(TILEMAP_PATH + "Nivel1-3.json", _game, _player, _tilesetBoss1, _enemyBulletPool);
		_game->getSoundManager()->playMusic("boss1Battle", -1);
		setBackgroundBoss1();
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
	_enemyBulletPool->stopBullets();
	_level->destroyAllChildren();
	setLevel(l);

	_game->getCurrentState()->getMainCamera()->setWorldBounds(getCurrentLevel(GameManager::getInstance()->getCurrentLevel())->getWidth(),
		getCurrentLevel(GameManager::getInstance()->getCurrentLevel())->getHeight());

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

void LevelManager::setParallaxZone1()
{
	_parallaxZone1 = new ParallaxBackGround(_camera);
	_parallaxZone1->addLayer(new ParallaxLayer(_game->getTexture("BgZ1L1"), _camera, 0.25));
	_parallaxZone1->addLayer(new ParallaxLayer(_game->getTexture("BgZ1L2"), _camera, 0.5));
	_parallaxZone1->addLayer(new ParallaxLayer(_game->getTexture("BgZ1L3"), _camera, 0.75));
	_camera->setBackGround(_parallaxZone1);
}

void LevelManager::setBackgroundBoss1()
{
	_backgroundBoss1 = new BackGround(_game->getTexture("BgBoss1"), _camera);
	_camera->setBackGround(_backgroundBoss1);
}