#include "PlayState.h"
#include "Game.h"
#include "PauseState.h"
#include "GameManager.h"
#include "ParticleManager.h"
#include "WeaponManager.h"
#include "CutScene.h"
#include "checkML.h"
#include <json.hpp>

using namespace nlohmann;

PlayState::PlayState(Game* g) : GameState(g) {}

PlayState::~PlayState()
{
	if (_cutScene != nullptr)
		delete _cutScene;
}

void PlayState::start()
{
	GameManager::init();
	WeaponManager::init();

	//PlayState HUD
	_playHud = new PlayStateHUD(_gameptr);
	setCanvas(_playHud);

	//Cursor
	_cursor = new Cursor(_gameptr);
	SDL_ShowCursor(false);

	//Player
	_player = new Player(_gameptr);
	_player->setPlayerPanel(_playHud->getPlayerPanel());

	//Player Bulletpool
	_playerBulletPool = new BulletPool(_gameptr);
	_player->setPlayerBulletPool(_playerBulletPool);

	//Shop Items
	if (!_gameptr->getCurrentState()->gameLoaded())
		_playHud->getShop()->setPlayer(_player);
	_playHud->getShop()->setVisible(false);

	//Camera
	_mainCamera->fixCameraToObject(_player);

	//Enemy Pool
	BulletPool* enemyPool = new BulletPool(_gameptr);

	//Level
	GameManager::getInstance()->setCurrentLevel(LevelManager::Tutorial);

	_level = new GameObject(_gameptr);
	_levelManager = LevelManager(_gameptr, _player, _level, enemyPool);

	if (!_gameptr->getCurrentState()->gameLoaded())
		_levelManager.setLevel(GameManager::getInstance()->getCurrentLevel());

	//Particles
	_particlePool = new ParticlePool(_gameptr);
	ParticleManager::GetParticleManager()->setParticlePool(_particlePool);

	//----AÑADIR A LOS OBJETOS----//

	_stages.push_back(_level);
	_stages.push_back(_player);
	_stages.push_back(_cursor);
	_stages.push_back(_playerBulletPool);
	_stages.push_back(enemyPool);
	_stages.push_back(_particlePool);
}

bool PlayState::handleEvent(const SDL_Event& event)
{
	GameState::handleEvent(event);

	bool handled = false;
	if (((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) || (event.type == SDL_CONTROLLERBUTTONDOWN && event.cbutton.button == SDL_CONTROLLER_BUTTON_START))
		&& !GameManager::getInstance()->getOnDialogue() && !GameManager::getInstance()->getOnShop())
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
		_playHud->getPlayerPanel()->updateAmmoViewer(_player->getCurrentGun()->getClip(), _player->getCurrentGun()->getMagazine());
	}

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

		auto items = _playHud->getShop()->getItems();

		for (ShopItem* i : items)
			j[i->getItemInfo()._name] = i->getItemInfo()._sold;

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
		_player->setBank(j["Bank"]);
		_levelManager.setLevel(j["level"]);
		_player->changeCurrentGun(WeaponManager::getInstance()->getWeapon(_gameptr, j["currentGun"]));
		_player->changeOtherGun(WeaponManager::getInstance()->getWeapon(_gameptr, j["otherGun"]));

		auto items = _playHud->getShop()->getItems();
		for (ShopItem* i : items)
		{
			i->setItemSell(j[i->getItemInfo()._name]);
			i->setItemEquiped(false);
		}
		_playHud->getShop()->setPlayer(_player);
	}
}


void PlayState::update(const double& deltaTime)
{
	if (_player->changeLevel())
	{
		GameManager* gameManager = GameManager::getInstance();
		_player->setChangeLevel(false);

		if (!_player->isDead())
		{
			if ((gameManager->getCurrentLevel() + 1) % 2 == 0) //Si el proximo nivel no es una safe zone guarda el juego
				saveGame();
			else
				_player->getMoney()->storeWallet();

			_player->setInputFreezed(true);
			getMainCamera()->fadeOut(1000);
			getMainCamera()->onFadeComplete([this, gameManager](Game* game)
			{
				gameManager->nextLevel();
				_levelManager.changeLevel(gameManager->getCurrentLevel());

				_player->revive();
				_player->setInputFreezed(false);

				if (_cutScene != nullptr)
					_cutScene->play();
			});
		}
		else if (!getMainCamera()->isFading())
		{
			_player->setInputFreezed(true);
			getMainCamera()->fadeOut(1000);
			getMainCamera()->onFadeComplete([this, gameManager](Game* game)
			{
				_player->setChangeLevel(false);

				gameManager->previousLevel();
				_levelManager.changeLevel(gameManager->getCurrentLevel());

				_player->revive();
				_player->setInputFreezed(false);
			});
		}
	}
	GameState::update(deltaTime);
	ParticleManager::GetParticleManager()->updateManager(deltaTime);
}