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
	DialoguePanel* dialogue = _game->getCurrentState()->getPlayHUD()->getDialoguePanel();
	ShopMenu* shop = _game->getCurrentState()->getPlayHUD()->getShop();

	switch (l)
	{
	case LevelManager::Tutorial:
		_currentMap = new Map(TILEMAP_PATH + "Tutorial.json", _game, _player, _game->getTexture("TilesetTutorial"), _enemyBulletPool);
		setParallaxZone1();

		cutscene = new CutScene(_player);

		cutscene->addCameraBlackScreenEvent(_camera);
		//cutscene->addPlaySoundEvent(_game, ""); sonido chispas
		//cutscene->addPlaySoundEvent(_game, ""); sonido disparo
		//cutscene->addPlaySoundEvent(_game, ""); sonido gru�ido
		cutscene->addCameraEvent(_camera, 3000, FadeIn);
		cutscene->addDialogueEvent(dialogue, _game->getDialogue("Helmet 1"));
		cutscene->addWaitEvent(1000);
		cutscene->addDialogueEvent(dialogue, _game->getDialogue("Helmet 2"));
		cutscene->addWaitEvent(1000);
		//cutscene->addPlaySoundEvent(_game, ""); sonido desconexi�n
		//cutscene->addPlayMusicEvent(_game, ""); m�sica tutorial
		cutscene->addDialogueEvent(dialogue, _game->getDialogue("Helmet 3"));
		_game->getCurrentState()->addCutScene(cutscene);

		cutscene->play();
		
		break;
	case LevelManager::Safe1_1:
		_currentSafeZone = new Map(TILEMAP_PATH + "Safe1-1.json", _game, _player, _game->getTexture("TilesetTutorial"), _enemyBulletPool);
		setParallaxZone1();
		//_game->getSoundManager()->playMusic("") sonido alarma en bucle
		break;
	case LevelManager::Level1_1:
		_currentMap = new Map(TILEMAP_PATH + "Nivel1-1.json", _game, _player, _game->getTexture("Tileset1"), _enemyBulletPool);
		setParallaxZone1();
		//_game->getSoundManager()->playMusic("") m�sica zona 1
		break;
	case LevelManager::Safe1_2:
		_currentSafeZone = new Map(TILEMAP_PATH + "Safe1-2.json", _game, _player, _game->getTexture("TilesetSafe1"), _enemyBulletPool);
		setParallaxZone1();
		_game->getSoundManager()->playMusic("safe_zone", -1);

		cutscene = new CutScene(_player);

		cutscene->addWaitEvent(1000);
		cutscene->addMoveEvent(_player->getComponent<BodyComponent>(), 1, 15, 192 / M_TO_PIXEL);
		cutscene->addDialogueEvent(dialogue, _game->getDialogue("Kartya 1-2"));
		cutscene->addWaitEvent(1000);
		cutscene->addMoveEvent(_player->getComponent<BodyComponent>(), 1, 15, 416 / M_TO_PIXEL);
		cutscene->addShopEvent(shop);
		_game->getCurrentState()->addCutScene(cutscene);

		break;
	case LevelManager::Level1_2:
		_currentMap = new Map(TILEMAP_PATH + "Nivel1-2.json", _game, _player, _game->getTexture("Tileset1"), _enemyBulletPool);
		setParallaxZone1();
		//_game->getSoundManager()->playMusic("") m�sica zona 1
		break;
	case LevelManager::SafeBoss1:
		_currentSafeZone = new Map(TILEMAP_PATH + "Safe1-3.json", _game, _player, _game->getTexture("TilesetSafe1"), _enemyBulletPool);
		setParallaxZone1();
		_game->getSoundManager()->playMusic("safe_zone", -1);
		break;
	case LevelManager::Boss1:
		_currentMap = new Map(TILEMAP_PATH + "Nivel1-3.json", _game, _player, _game->getTexture("TilesetBoss1"), _enemyBulletPool);
		setBackgroundBoss1();

		cutscene = new CutScene(_player);

		cutscene->addCameraEvent(_camera, 150, ZoomIn);
		cutscene->addMoveEvent(_player->getComponent<BodyComponent>(), 1, 15, 192 / M_TO_PIXEL);
		//cutscene->addPlaySoundEvent(_game, ""); sonido vuelo
		cutscene->addCameraShakeEvent(_camera, 1500, 3);
		cutscene->addFitCameraEvent(_camera, _currentMap->getWidth(), _currentMap->getHeight());
		cutscene->addPlayMusicEvent(_game, "boss1Battle");
		_game->getCurrentState()->addCutScene(cutscene);

		break;
	case LevelManager::Safe2_1:
		_currentSafeZone = new Map(TILEMAP_PATH + "Safe2-1.json", _game, _player, _game->getTexture("TilesetSafe2"), _enemyBulletPool);
		setParallaxZone2();
		_game->getSoundManager()->playMusic("safe_zone", -1);

		cutscene = new CutScene(_player);

		cutscene->addMoveEvent(_player->getComponent<BodyComponent>(), 1, 15, 496 / M_TO_PIXEL);
		cutscene->addDialogueEvent(dialogue, _game->getDialogue("Azura 2-1"));
		_game->getCurrentState()->addCutScene(cutscene);

		break;
	case LevelManager::Level2_1:
		_currentMap = new Map(TILEMAP_PATH + "Nivel2-1.json", _game, _player, _game->getTexture("Tileset2"), _enemyBulletPool);
		setParallaxZone2();
		//_game->getSoundManager()->playMusic("") m�sica zona 2
		break;
	case LevelManager::Safe2_2:
		_currentSafeZone = new Map(TILEMAP_PATH + "Safe2-2.json", _game, _player, _game->getTexture("TilesetSafe2"), _enemyBulletPool);
		setParallaxZone2();
		_game->getSoundManager()->playMusic("safe_zone", -1);
		break;
	case LevelManager::Level2_2:
		_currentMap = new Map(TILEMAP_PATH + "Nivel2-2.json", _game, _player, _game->getTexture("Tileset2"), _enemyBulletPool);
		setParallaxZone2();
		//_game->getSoundManager()->playMusic("") m�sica zona 2
		break;
	case LevelManager::SafeBoss2:
		_currentSafeZone = new Map(TILEMAP_PATH + "Safe2-3.json", _game, _player, _game->getTexture("TilesetSafe2"), _enemyBulletPool);
		setParallaxZone2();
		_game->getSoundManager()->playMusic("safe_zone", -1);
		break;
	case LevelManager::Boss2:
		_currentMap = new Map(TILEMAP_PATH + "Nivel2-3.json", _game, _player, _game->getTexture("TilesetBoss2"), _enemyBulletPool);
		setParallaxZone2();

		cutscene = new CutScene(_player);

		cutscene->addCameraEvent(_camera, 150, ZoomIn);
		cutscene->addMoveEvent(_player->getComponent<BodyComponent>(), 1, 15, 192 / M_TO_PIXEL);
		//cutscene->addPlaySoundEvent(_game, ""); sonido gruñido
		cutscene->addCameraShakeEvent(_camera, 1500, 3);
		cutscene->addFitCameraEvent(_camera, _currentMap->getWidth(), _currentMap->getHeight());
		cutscene->addDialogueEvent(dialogue, _game->getDialogue("Azura Manyu 1"));
		//cutscene->addPlaySoundEvent(_game, ""); sonido rugido
		cutscene->addCameraShakeEvent(_camera, 1500, 3);
		//cutscene->addPlayMusicEvent(_game, ""); música boss 2
		_game->getCurrentState()->addCutScene(cutscene);

		break;
	case LevelManager::Safe3_1:
		//_currentSafeZone = ...
		setParallaxZone3();
		_game->getSoundManager()->playMusic("safe_zone", -1);

		cutscene = new CutScene(_player);

		cutscene->addMoveEvent(_player->getComponent<BodyComponent>(), 1, 15, 10 / M_TO_PIXEL /* posicion de Kheismani*/);
		cutscene->addDialogueEvent(dialogue, _game->getDialogue("Azura 2-1"));
		_game->getCurrentState()->addCutScene(cutscene);

		break;
	case LevelManager::Level3_1:
		//_currentMap = ...
		setParallaxZone3();
		//_game->getSoundManager()->playMusic("") m�sica zona 3
		break;
	case LevelManager::Safe3_2:
		//_currentSafeZone = ...
		setParallaxZone3();
		_game->getSoundManager()->playMusic("safe_zone", -1);
		break;
	case LevelManager::Level3_2:
		//_currentMap = ...
		setParallaxZone3();
		//_game->getSoundManager()->playMusic("") m�sica zona 3
		break;
	case LevelManager::SafeBoss3:
		//_currentSafeZone = ...
		setParallaxZone3();
		_game->getSoundManager()->playMusic("safe_zone", -1);
		break;
	case LevelManager::Boss3:
		_currentMap = new Map(TILEMAP_PATH + "Nivel3-3.json", _game, _player, _game->getTexture("TilesetBoss3"), _enemyBulletPool);
		setParallaxZone3();
		//_game->getSoundManager()->playMusic("") m�sica boss 3

		cutscene = new CutScene(_player);

		cutscene->addCameraEvent(_camera, 150, ZoomIn);
		cutscene->addMoveEvent(_player->getComponent<BodyComponent>(), 1, 15, 192 / M_TO_PIXEL);
		cutscene->addCameraShakeEvent(_camera, 1500, 3);
		cutscene->addFitCameraEvent(_camera, _currentMap->getWidth(), _currentMap->getHeight());
		cutscene->addDialogueEvent(dialogue, _game->getDialogue("Angra Manyu 1"));
		//cutscene->addPlayMusicEvent(_game, ""); música boss 3
		_game->getCurrentState()->addCutScene(cutscene);

		break;
	case LevelManager::End:
		//_currentMap = ...
		setParallaxZone3();

		cutscene = new CutScene(_player);

		cutscene->addDialogueEvent(dialogue, _game->getDialogue("Kartya Boss 1"));
		cutscene->addDialogueEvent(dialogue, _game->getDialogue("Kheismani Boss 1"));
		cutscene->addDialogueEvent(dialogue, _game->getDialogue("Kartya Boss 2"));
		cutscene->addDialogueEvent(dialogue, _game->getDialogue("Kheismani Boss 2"));
		cutscene->addDialogueEvent(dialogue, _game->getDialogue("Kartya Boss 3"));
		cutscene->addDialogueEvent(dialogue, _game->getDialogue("Kheismani Boss 3"));
		cutscene->addDialogueEvent(dialogue, _game->getDialogue("Kartya Boss 4"));
		cutscene->addDialogueEvent(dialogue, _game->getDialogue("Kheismani Boss 4"));
		cutscene->addDialogueEvent(dialogue, _game->getDialogue("Kartya Boss 5"));
		_game->getCurrentState()->addCutScene(cutscene);

		cutscene->play();

		break;

		//Demo Guerrilla Game Festival
	case LevelManager::SafeDemo:
		_currentSafeZone = new Map(TILEMAP_PATH + "SafeZoneDemo.json", _game, _player, _game->getTexture("Tileset1"), _enemyBulletPool);
		setControlsBackground();
		_game->getSoundManager()->playMusic("safe_zone", -1);
		break;
	case LevelManager::LevelDemo:
		_currentMap = new Map(TILEMAP_PATH + "NivelDemo.json", _game, _player, _game->getTexture("Tileset1"), _enemyBulletPool);
		setParallaxZone1();
		_game->getSoundManager()->playMusic("demoLevelMusic", -1);
		break;
	case LevelManager::SafeBossDemo:
		_currentSafeZone = new Map(TILEMAP_PATH + "SafeZoneBossDemo.json", _game, _player, _game->getTexture("Tileset1"), _enemyBulletPool);
		setParallaxZone1();
		_game->getSoundManager()->playMusic("safe_zone", -1);

		cutscene = new CutScene(_player);

		cutscene->addMoveEvent(_player->getComponent<BodyComponent>(), 1, 15, (304 / 2) / M_TO_PIXEL);
		cutscene->addWaitEvent(1000);
		cutscene->addFlipEvent();
		cutscene->addWaitEvent(1000);
		cutscene->addFlipEvent();
		cutscene->addWaitEvent(1000);
		cutscene->addDialogueEvent(dialogue, _game->getDialogue("Demo"));
		cutscene->addWaitEvent(1000);
		cutscene->addFlipEvent();
		cutscene->addWaitEvent(1000);
		cutscene->addFlipEvent();
		cutscene->addWaitEvent(1000);
		cutscene->addMoveEvent(_player->getComponent<BodyComponent>(), 1, 15, 304 / M_TO_PIXEL);
		cutscene->addShopEvent(shop);
		_game->getCurrentState()->addCutScene(cutscene);

		break;
	case LevelManager::BossDemo:
		_currentMap = new Map(TILEMAP_PATH + "Nivel1-3.json", _game, _player, _game->getTexture("TilesetBoss1"), _enemyBulletPool);
		setBackgroundBoss1();
		_game->getSoundManager()->playMusic("boss1Battle", -1);

		cutscene = new CutScene(_player);

		cutscene->addCameraEvent(_camera, 150, ZoomIn);
		cutscene->addMoveEvent(_player->getComponent<BodyComponent>(), 1, 15, 192 / M_TO_PIXEL);
		//cutscene->addPlaySoundEvent(_game, ""); sonido vuelo
		cutscene->addCameraShakeEvent(_camera, 1500, 3);
		cutscene->addFitCameraEvent(_camera, _currentMap->getWidth(), _currentMap->getHeight());
		cutscene->addPlayMusicEvent(_game, "boss1Battle");
		_game->getCurrentState()->addCutScene(cutscene);

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

	if (l == SafeDemo || l == End)
		_camera->fitCamera({ xBound, yBound }, true);
	else
		_camera->setZoom(CAMERA_SCALE_FACTOR);

	if (l != Tutorial)
		_camera->fadeIn(3000);
}

void LevelManager::changeLevel(int l)
{
	if (_game->getCurrentState()->getPlayHUD() != nullptr)
		_game->getCurrentState()->getPlayHUD()->reset();
	_enemyBulletPool->stopBullets();
	_level->destroyAllChildren();
	_game->getSoundManager()->stopMusic();
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

void LevelManager::setParallaxZone2()
{
	ParallaxBackGround* parallaxZone1 = new ParallaxBackGround(_camera);

	parallaxZone1->addLayer(new ParallaxLayer(_game->getTexture("BgZ2L1"), _camera, 0.25));
	parallaxZone1->addLayer(new ParallaxLayer(_game->getTexture("BgZ2L2"), _camera, 0.5));
	parallaxZone1->addLayer(new ParallaxLayer(_game->getTexture("BgZ2L3"), _camera, 0.75));

	_camera->setBackGround(parallaxZone1);
}

void LevelManager::setParallaxZone3()
{
	ParallaxBackGround* parallaxZone1 = new ParallaxBackGround(_camera);

	parallaxZone1->addLayer(new ParallaxLayer(_game->getTexture("BgZ3L1"), _camera, 0.25));
	parallaxZone1->addLayer(new ParallaxLayer(_game->getTexture("BgZ3L2"), _camera, 0.5));
	parallaxZone1->addLayer(new ParallaxLayer(_game->getTexture("BgZ3L3"), _camera, 0.75));

	_camera->setBackGround(parallaxZone1);
}

void LevelManager::setBackgroundBoss1()
{
	BackGround* backgroundBoss1 = new BackGround(_game->getTexture("BgBoss1"), _camera);
	_camera->setBackGround(backgroundBoss1);
}