#include "LevelManager.h"
#include "Game.h"
#include "GameManager.h"
#include "ParallaxBackGround.h"
#include "ParallaxLayer.h"
#include "CutScene.h"

LevelManager::LevelManager(Game* game, Player* player, GameObject* level, BulletPool* enemyPool) : _game(game), _player(player), _level(level), _enemyBulletPool(enemyPool)
{
	_camera = game->getCurrentState()->getMainCamera();
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
		_currentSafeZone = new Map(TILEMAP_PATH + "SafeZonePrueba.json", _game, _player, _game->getTexture("Tileset1"), _enemyBulletPool);
		_game->getSoundManager()->playMusic("safe_zone", -1);
		setParallaxZone1();
		break;
	case LevelManager::Level1_1:
		_currentMap = new Map(TILEMAP_PATH + "Nivel1-1.json", _game, _player, _game->getTexture("Tileset1"), _enemyBulletPool);
		_game->getSoundManager()->playMusic("zona1", -1);
		setParallaxZone1();
		break;
	case LevelManager::Safe1_2:
		_currentSafeZone = new Map(TILEMAP_PATH + "SafeZonePrueba.json", _game, _player, _game->getTexture("Tileset1"), _enemyBulletPool);
		_game->getSoundManager()->playMusic("safe_zone", -1);
		setParallaxZone1();
		break;
	case LevelManager::Level1_2:
		_currentMap = new Map(TILEMAP_PATH + "Nivel1-2.json", _game, _player, _game->getTexture("Tileset1"), _enemyBulletPool);
		_game->getSoundManager()->playMusic("zona1", -1);
		setParallaxZone1();
		break;
	case LevelManager::SafeBoss1:
		_currentSafeZone = new Map(TILEMAP_PATH + "SafeZonePrueba.json", _game, _player, _game->getTexture("Tileset1"), _enemyBulletPool);
		_game->getSoundManager()->playMusic("safe_zone", -1);
		setParallaxZone1();
		break;
	case LevelManager::Boss1:
		_currentMap = new Map(TILEMAP_PATH + "Nivel1-3.json", _game, _player, _game->getTexture("TilesetBoss1"), _enemyBulletPool);
		_game->getSoundManager()->playMusic("boss1Battle", -1);
		setBackgroundBoss("BgBoss1");
		break;
	case LevelManager::Safe2_1:
		_currentSafeZone = new Map(TILEMAP_PATH + "SafeZonePrueba.json", _game, _player, _game->getTexture("Tileset1"), _enemyBulletPool);
		_game->getSoundManager()->playMusic("safe_zone", -1);
		break;
	case LevelManager::Level2_1:
		_currentMap = new Map(TILEMAP_PATH + "Nivel2-1.json", _game, _player, _game->getTexture("Tileset2"), _enemyBulletPool);
		_game->getSoundManager()->playMusic("zona2", -1);
		break;
	case LevelManager::Safe2_2:
		_currentSafeZone = new Map(TILEMAP_PATH + "SafeZonePrueba.json", _game, _player, _game->getTexture("Tileset1"), _enemyBulletPool);
		_game->getSoundManager()->playMusic("safe_zone", -1);
		break;
	case LevelManager::Level2_2:
		_currentMap = new Map(TILEMAP_PATH + "Nivel2-2.json", _game, _player, _game->getTexture("Tileset2"), _enemyBulletPool);
		_game->getSoundManager()->playMusic("zona2", -1);
		break;
	case LevelManager::SafeBoss2:
		_currentSafeZone = new Map(TILEMAP_PATH + "SafeZonePrueba.json", _game, _player, _game->getTexture("Tileset1"), _enemyBulletPool);
		_game->getSoundManager()->playMusic("safe_zone", -1);
		break;
	case LevelManager::Boss2:
		_currentMap = new Map(TILEMAP_PATH + "Nivel2-3.json", _game, _player, _game->getTexture("TilesetBoss2"), _enemyBulletPool);
		_game->getSoundManager()->playMusic("boss2Battle", -1);
		setBackgroundBoss("BgBoss2");
		break;
	case LevelManager::Safe3_1:
		//_currentSafeZone = ...
		_game->getSoundManager()->playMusic("safe_zone", -1);
		break;
	case LevelManager::Level3_1:
		//_currentMap = ...
		_game->getSoundManager()->playMusic("zona3", -1);
		break;
	case LevelManager::Safe3_2:
		//_currentSafeZone = ...
		_game->getSoundManager()->playMusic("safe_zone", -1);
		break;
	case LevelManager::Level3_2:
		//_currentMap = ...
		_game->getSoundManager()->playMusic("zona3", -1);
		break;
	case LevelManager::SafeBoss3:
		//_currentSafeZone = ...
		_game->getSoundManager()->playMusic("safe_zone", -1);
		break;
	case LevelManager::Boss3:
		_currentMap = new Map(TILEMAP_PATH + "Nivel3-3.json", _game, _player, _game->getTexture("TilesetBoss3"), _enemyBulletPool);
		_game->getSoundManager()->playMusic("boss3Battle", -1);
		setBackgroundBoss("BgBoss3");
		break;

		//Demo Guerrilla Game Festival
	case LevelManager::SafeDemo:
		_currentSafeZone = new Map(TILEMAP_PATH + "SafeZoneDemo.json", _game, _player, _game->getTexture("Tileset1"), _enemyBulletPool);
		_game->getSoundManager()->playMusic("safe_zone", -1);
		setControlsBackground();
		break;
	case LevelManager::LevelDemo:
		_currentMap = new Map(TILEMAP_PATH + "NivelDemo.json", _game, _player, _game->getTexture("Tileset1"), _enemyBulletPool);
		_game->getSoundManager()->playMusic("zona1", -1);
		setParallaxZone1();
		break;
	case LevelManager::SafeBossDemo:
		_currentSafeZone = new Map(TILEMAP_PATH + "SafeZoneBossDemo.json", _game, _player, _game->getTexture("Tileset1"), _enemyBulletPool);
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
		_currentMap = new Map(TILEMAP_PATH + "Nivel1-3.json", _game, _player, _game->getTexture("TilesetBoss1"), _enemyBulletPool);
		_game->getSoundManager()->playMusic("boss1Battle", -1);
		setBackgroundBoss("BgBoss1");
		break;
	}

	double xBound, yBound;
	xBound = getCurrentLevel(GameManager::getInstance()->getCurrentLevel())->getWidth();
	yBound = getCurrentLevel(GameManager::getInstance()->getCurrentLevel())->getHeight();

	_camera->setWorldBounds(xBound, yBound);

	if (l % 2 == 0)
		_level->addChild(_currentMap);
	else
		_level->addChild(_currentSafeZone);

	if (l == Boss1 || l == Boss2 || l == Boss3 || l == SafeDemo || l == BossDemo)
		_camera->fitCamera({ xBound, yBound }, true);
	else
		_camera->setZoom(CAMERA_SCALE_FACTOR);

	_camera->fadeIn(3000);
}

void LevelManager::changeLevel(int l)
{
	if (_game->getCurrentState()->getPlayHUD() != nullptr)
		_game->getCurrentState()->getPlayHUD()->reset();
	_enemyBulletPool->stopBullets();
	_level->destroyAllChildren();
	setLevel(l);
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

void LevelManager::setControlsBackground()
{
	ParallaxBackGround* parallaxZone1 = new ParallaxBackGround(_camera);

	parallaxZone1->addLayer(new ParallaxLayer(_game->getTexture("BgZ1L1"), _camera, 0.25));
	parallaxZone1->addLayer(new ParallaxLayer(_game->getTexture("BgZ1L2"), _camera, 0.5));
	parallaxZone1->addLayer(new ParallaxLayer(_game->getTexture("BgZ1L3"), _camera, 0.75));
	parallaxZone1->addLayer(new ParallaxLayer(_game->getTexture("BgControls"), _camera, 0));

	_camera->setBackGround(parallaxZone1);
}

void LevelManager::setParallaxZone1()
{
	ParallaxBackGround* parallaxZone1 = new ParallaxBackGround(_camera);

	parallaxZone1->addLayer(new ParallaxLayer(_game->getTexture("BgZ1L1"), _camera, 0.25));
	parallaxZone1->addLayer(new ParallaxLayer(_game->getTexture("BgZ1L2"), _camera, 0.5));
	parallaxZone1->addLayer(new ParallaxLayer(_game->getTexture("BgZ1L3"), _camera, 0.75));

	_camera->setBackGround(parallaxZone1);
}

void LevelManager::setBackgroundBoss(string txt)
{
	BackGround* backgroundBoss = new BackGround(_game->getTexture(txt), _camera);
	_camera->setBackGround(backgroundBoss);
}