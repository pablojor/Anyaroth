#include "PlayState.h"
#include "Game.h"
#include "PauseState.h"
#include "ParallaxLayer.h"
#include "WeaponManager.h"
#include "GameManager.h"
#include "CutScene.h"
#include "checkML.h"
#include <json.hpp>

using namespace nlohmann;

PlayState::PlayState(Game* g) : GameState(g)
{
	GameManager::init();
	WeaponManager::init();

	//HUD
	_hud = new PlayStateHUD(g);
	setCanvas(_hud);

	//Player
	_player = new Player(g, 100, 200);
	_playerBulletPool = new BulletPool(g);
	_player->setPlayerBulletPool(_playerBulletPool);
	_player->setPlayerPanel(_hud->getPlayerPanel());

	_hud->getShop()->setPlayer(_player);
	_hud->getShop()->setVisible(false);

	//Enemy Pool
	auto enemyPool = new BulletPool(g);

	//Levels
	GameManager::getInstance()->setCurrentLevel(LevelManager::Demo);
	_level = new GameObject(g);
	_levelManager = LevelManager(g, _player, _level, _hud, enemyPool);
	_levelManager.setLevel(GameManager::getInstance()->getCurrentLevel());
	_mainCamera->setWorldBounds(_levelManager.getCurrentLevel(GameManager::getInstance()->getCurrentLevel())->getWidth(), _levelManager.getCurrentLevel(GameManager::getInstance()->getCurrentLevel())->getHeight());

	//Background
	_parallaxZone1 = new ParallaxBackGround(_mainCamera);
	_parallaxZone1->addLayer(new ParallaxLayer(g->getTexture("BgZ1L1"), _mainCamera, 0.25));
	_parallaxZone1->addLayer(new ParallaxLayer(g->getTexture("BgZ1L2"), _mainCamera, 0.5));
	_parallaxZone1->addLayer(new ParallaxLayer(g->getTexture("BgZ1L3"), _mainCamera, 0.75));

	//Cursor
	_cursor = new Cursor(g);
	SDL_ShowCursor(false);

	//Camera
	_mainCamera->fixCameraToObject(_player);
	_mainCamera->setBackGround(_parallaxZone1);

	//Collisions and debugger
	g->getWorld()->SetContactListener(&_colManager);
	g->getWorld()->SetDebugDraw(&_debugger);

	//World
	_debugger.getRenderer(g->getRenderer());
	_debugger.getTexture(g->getTexture("Box"));
	_debugger.SetFlags(b2Draw::e_shapeBit);
	_debugger.getCamera(_mainCamera);

	//Gestion de colisiones
	g->getWorld()->SetContactListener(&_colManager);
	g->getWorld()->SetDebugDraw(&_debugger);

	//Particulas
	_particles = new ParticlePull(g);
	_particleManager = ParticleManager::GetParticleManager();
	_particleManager->setParticlePull(_particles);

	//Escena de prueba
	_cutScene = new CutScene(_player);

	_cutScene->addMoveEvent(_player->getComponent<BodyComponent>(), 1, 10, 30);
	_cutScene->addFlipEvent();
	_cutScene->addCameraEvent(_mainCamera, 1000, CamEffect::ZoomOut);
	_cutScene->addCameraEvent(_mainCamera, 1000, CamEffect::ZoomIn);
	_cutScene->addCameraEvent(_mainCamera, 1000, CamEffect::FadeIn);
	_cutScene->addCameraEvent(_mainCamera, 1000, CamEffect::FadeOut);
	_cutScene->addCameraShakeEvent(_mainCamera, 1000, 10);
	_cutScene->addFlipEvent();
	_cutScene->addWaitEvent(500);
	_cutScene->addFlipEvent();
	_cutScene->addWaitEvent(500);
	_cutScene->addFlipEvent();
	_cutScene->addWaitEvent(2000);
	_cutScene->addDialogueEvent(_hud->getDialoguePanel(), g->getDialogue("Jose Maria 1"));
	_cutScene->addMoveEvent(_player->getComponent<BodyComponent>(), 1, 10, 40);
	_cutScene->addWaitEvent(1000);
	_cutScene->addShopEvent(_hud->getShop());
	_cutScene->addWaitEvent(500);
	_cutScene->addMoveEvent(_player->getComponent<BodyComponent>(), 1, 10, 50);

	//_cutScene->play();

	//----AÑADIR A LOS OBJETOS----//

	_stages.push_back(_level);
	_stages.push_back(_cursor);
	_stages.push_back(_player);
	_stages.push_back(_playerBulletPool);
	_stages.push_back(enemyPool);
    _stages.push_back(_particles);
}

PlayState::~PlayState()
{
	if (_cutScene != nullptr)
		delete _cutScene;
}

void PlayState::render() const
{
	GameState::render();
}

bool PlayState::handleEvent(const SDL_Event& event)
{
	GameState::handleEvent(event);

	bool handled = false;
	if ((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) || (event.type == SDL_CONTROLLERBUTTONDOWN && event.cbutton.button == SDL_CONTROLLER_BUTTON_START))
	{
		_gameptr->setTimestep(0);
		_gameptr->pushState(new PauseState(_gameptr));
		handled = true;
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_0) //Boton de prueba para reiniciar el nivel
		_levelManager.resetLevel();
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_1) //Boton de prueba para reiniciar la municion
	{
		_player->getCurrentGun()->resetAmmo();
		_hud->getPlayerPanel()->updateAmmoViewer(_player->getCurrentGun()->getClip(), _player->getCurrentGun()->getMagazine());

	}
	else if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_KP_MINUS || event.key.keysym.sym == SDLK_MINUS)) //Para probar el Zoom y sus distintan opciones
		_mainCamera->zoomOut();
	else if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_KP_PLUS || event.key.keysym.sym == SDLK_PLUS))
		_mainCamera->zoomIn();
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_n)
		_mainCamera->setZoom(_mainCamera->getZoomRatio() + 1, true);
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_m)
		_mainCamera->setZoom(_mainCamera->getZoomRatio() - 1, true);
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_KP_ENTER && !event.key.repeat)
		_mainCamera->shake(10, 750);
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p && !event.key.repeat)
		_mainCamera->fadeIn(5000);
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_o && !event.key.repeat)
		_mainCamera->fadeOut(5000);

	return handled;
}

void PlayState::saveGame()
{
	ofstream output;
	output.open(SAVES_PATH + "save.json");

	if (output.is_open())
	{
		json j;
		j["level"] = GameManager::getInstance()->getCurrentLevel();
		j["Bank"] = _player->getBank();
		j["currentGun"] = _player->getCurrentGun()->getGunID();
		j["otherGun"] = _player->getOtherGun()->getGunID();

		auto items = _hud->getShop()->getItems();
		for (ShopItem* i : items)
		{
			cout << i->getItemInfo()._name << " " << i->getItemInfo()._sold;
			j[i->getItemInfo()._name] = i->getItemInfo()._sold;
		}
		output << j;
	}
}

void PlayState::loadGame()
{
	ifstream input;
	input.open(SAVES_PATH + "save.json");

	if (input.is_open())
	{
		json j;
		input >> j;
		cout << j;
		_player->setBank(j["Bank"]);
		_levelManager.changeLevel(j["level"]);
		_player->changeCurrentGun(WeaponManager::getWeapon(_gameptr, j["currentGun"]));
		_player->changeOtherGun(WeaponManager::getWeapon(_gameptr, j["otherGun"]));

		auto items = _hud->getShop()->getItems();
		for (ShopItem* i : items)
		{
			i->setItemSell(j[i->getItemInfo()._name]);
			i->setItemEquiped(false);
		}
		_hud->getShop()->setPlayer(_player);
	}
}


void PlayState::update(const double& deltaTime)
{
	if (_player->changeLevel())
	{
		GameManager* gManager = GameManager::getInstance();
		_player->setChangeLevel(false);

		if (!_player->isDead())
		{
			_player->revive();

			if ((gManager->getCurrentLevel() + 1) % 2 == 0) //Si el proximo nivel no es una safe zone guarda el juego
				saveGame();

			if (gManager->getCurrentLevel() == LevelManager::Demo)
				_levelManager.resetLevel();
			else
			{
				gManager->setCurrentLevel(gManager->getCurrentLevel() + 1);
				_levelManager.changeLevel(gManager->getCurrentLevel());
			}

			_mainCamera->setWorldBounds(_levelManager.getCurrentLevel(GameManager::getInstance()->getCurrentLevel())->getWidth(), _levelManager.getCurrentLevel(GameManager::getInstance()->getCurrentLevel())->getHeight());
			_mainCamera->setZoom(CAMERA_SCALE_FACTOR);
		}
		else
		{
			_playerBulletPool->stopBullets();
			_player->revive();

			if (gManager->getCurrentLevel() == LevelManager::Demo)
				_levelManager.resetLevel();
			else
			{
				gManager->setCurrentLevel(gManager->getCurrentLevel() - 1);
				_levelManager.changeLevel(gManager->getCurrentLevel());
			}

			_mainCamera->setWorldBounds(_levelManager.getCurrentLevel(GameManager::getInstance()->getCurrentLevel())->getWidth(), _levelManager.getCurrentLevel(GameManager::getInstance()->getCurrentLevel())->getHeight());
			_mainCamera->setZoom(CAMERA_SCALE_FACTOR);
		}
	}
	else
	{
		if (_cutScene != nullptr)
		{
			if (_cutScene->isPlaying())
				_cutScene->update(deltaTime);
			else
			{
				delete _cutScene;
				_cutScene = nullptr;
			}
		}
	}

	GameState::update(deltaTime);
    _particleManager->updateManager(deltaTime);
}