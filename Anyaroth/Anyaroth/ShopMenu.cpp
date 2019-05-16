#include "ShopMenu.h"
#include "Game.h"
#include "Player.h"
#include "PlayStateHUD.h"
#include "GameManager.h"
#include "WeaponManager.h"
#include "SoundManager.h"
#include <json.hpp>

ShopMenu::ShopMenu(Game* game) : PanelUI(game)
{
	//----FONDO----//

	_imageBG = new AnimatedImageUI(game, game->getTexture("BgShop"));
	_imageBG->addAnim(AnimatedImageUI::Idle, 6, true);
	addChild(_imageBG);


	//----BOTONES---//

	int distanceBetweenButtons = 6,
		middleOfTheButtonPanelX = CAMERA_RESOLUTION_X,
		middleOfTheButtonPanelY = 100;

	//BOTON DE HABLAR
	_talkButton = new ButtonUI(game, game->getTexture("ShopButton"), [this](Game* game) { startTalking(game); }, { 0, 1, 1, 1, 1 }, 1);
	_talkButton->setPosition(middleOfTheButtonPanelX / 2 - _talkButton->getW() / 2,
		middleOfTheButtonPanelY - (distanceBetweenButtons / 2) - _talkButton->getH());

	_talkText = new TextUI(game, "Talk", game->getFont("ARIAL12"), 12, 0, 0, { 145, 255, 255, 255 });
	_talkText->setPosition(_talkButton->getX() + _talkButton->getW() / 2 - _talkText->getW() / 2,
		_talkButton->getY() + _talkButton->getH() / 2 - _talkText->getH() / 2);

	//BOTON DE TIENDA
	_shopButton = new ButtonUI(game, game->getTexture("ShopButton"), [this](Game* game) { openCatalogPanel(game); }, { 0, 1, 1, 1, 1 });
	_shopButton->setPosition(middleOfTheButtonPanelX / 2 - _shopButton->getW() / 2,
		_talkButton->getY() - _shopButton->getH() - distanceBetweenButtons);

	_shopText = new TextUI(game, "Shop", game->getFont("ARIAL12"), 12, 0, 0, { 145, 255, 255, 255 });
	_shopText->setPosition(_shopButton->getX() + _shopButton->getW() / 2 - _shopText->getW() / 2,
		_shopButton->getY() + _shopButton->getH() / 2 - _shopText->getH() / 2);

	//BOTON DE ALMACEN
	_depotButton = new ButtonUI(game, game->getTexture("ShopButton"), [this](Game* game) { openDepotPanel(game); }, { 0, 1, 1, 1, 1 }, 2);
	_depotButton->setPosition(middleOfTheButtonPanelX / 2 - _depotButton->getW() / 2,
		middleOfTheButtonPanelY + (distanceBetweenButtons / 2));

	_depotText = new TextUI(game, "Equipment", game->getFont("ARIAL12"), 12, 0, 0, { 145, 255, 255, 255 });
	_depotText->setPosition(_depotButton->getX() + _depotButton->getW() / 2 - _depotText->getW() / 2,
		_depotButton->getY() + _depotButton->getH() / 2 - _depotText->getH() / 2);

	//BOTON DE SALIR
	_exitButton = new ButtonUI(game, game->getTexture("ExitButton"), nullptr, { 0, 1, 1, 1 }, 3);
	_exitButton->setPosition(CAMERA_RESOLUTION_X - _exitButton->getW() - 12, 188 - 1 - _exitButton->getH());

	_exitButton->onUp([this](Game* game) { exit(game); });

	_shopButton->setNextButtons({ _exitButton, _exitButton, _talkButton, _talkButton });
	_talkButton->setNextButtons({ _shopButton, _shopButton, _depotButton, _depotButton });
	_depotButton->setNextButtons({ _talkButton, _talkButton, _exitButton, _exitButton });
	_exitButton->setNextButtons({ _depotButton, _depotButton, _shopButton, _shopButton });

	addChild(_shopButton);
	addChild(_shopText);
	addChild(_talkButton);
	addChild(_talkText);
	addChild(_depotButton);
	addChild(_depotText);
	addChild(_exitButton);

	//----DISTINTAS FUNCIONALIDADES DE LA TIENDA----//

	_catalogPanel = new CatalogPanel(game);
	_catalogPanel->setVisible(false);
	_catalogPanel->inicializeCallbacks(this);

	_depotPanel = new DepotPanel(game);
	_depotPanel->setVisible(false);
	_depotPanel->inicializeCallback(this);

	addChild(_catalogPanel);
	addChild(_depotPanel);

	loadWeaponInfo();

	_catalogPanel->setItems(&_weaponItems);
	_depotPanel->setWeaponItems(&_weaponItems);
	_depotPanel->setMeleeItems(&_meleeItems);
}

ShopMenu::~ShopMenu()
{
	_depotPanel->removeWeaponItems();
	_depotPanel->removeMeleeItems();

	_catalogPanel->removeItems();
	if (_dialoguePanel != nullptr) removeChild(_dialoguePanel);

	for (auto it = _weaponItems.begin(); it != _weaponItems.end(); it++)
		delete *it;
	for (auto it = _meleeItems.begin(); it != _meleeItems.end(); it++)
		delete *it;
}


void ShopMenu::update(double deltaTime)
{
	PanelUI::update(deltaTime);

	if (_talking && _dialoguePanel->conversationEnd())
	{
		_talking = false;
		stopTalking();
	}
}

bool ShopMenu::handleEvent(const SDL_Event& event)
{
	bool handled = false;
	if (_visible)
	{
		if (_mainMenuAbled)
		{
			PanelUI::checkControlMode(event);
			if (event.type == SDL_CONTROLLERBUTTONDOWN)
			{
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B)
				{
					exit(_game);
					return true;
				}
			}
		}
		
		auto it = _children.begin();

		while (!handled && it != _children.end())
		{
			if ((*it) != _dialoguePanel && (*it)->handleEvent(event))
				handled = true;
			else
				it++;
		}
	}
	
	return handled;
}

void ShopMenu::loadWeaponInfo()
{
	//Armas de fuego
	auto weaponInfo = WeaponManager::getInstance()->getAllWeaponInfo();
	for (auto it = weaponInfo.begin(); it != weaponInfo.end(); it++)
	{
		auto item = new ShopItem(_game, _game->getTexture((*it).second._iconName), 0, 0);

		bool sold = false;
		bool equiped = false;

		if ((*it).second._zone == -1)
		{
			equiped = true;
			sold = true;
		}
		
		item->setItemInfo({ (*it).second._zone, (*it).second._name, (*it).second._price ,(*it).second._damage, (*it).second._cadence, (*it).second._clip, (uint)(*it).first, (*it).second._iconName, (*it).second._rarityFrame, sold, equiped, false });
		_weaponItems.push_back(item);
	}

	//Armas melee
	auto meleeInfo = WeaponManager::getInstance()->getAllMeleeInfo();
	for (auto it = meleeInfo.begin(); it != meleeInfo.end(); it++)
	{
		auto item = new ShopItem(_game, _game->getTexture((*it).second._iconName), 0, 0);

		bool sold = false;
		bool equiped = false;

		if ((*it).second._zone == -1)
		{
			equiped = true;
			sold = true;
		}

		item->setItemInfo({ (*it).second._zone, (*it).second._name, 0, 0, 0, 0, (uint)(*it).first, (*it).second._iconName, (*it).second._rarityFrame, sold, equiped, true });
		_meleeItems.push_back(item);
	}
}

void ShopMenu::setPlayer(Player* ply)
{
	_player = ply;

	_catalogPanel->setPlayer(_player);
	_depotPanel->setPlayer(_player);
}

void ShopMenu::openShop()
{
	_player->setInputFreezed(true);
	GameManager::getInstance()->setOnShop(true);
	_player->getPlayerPanel()->updateCoinsCounter(_player->getMoney()->getWallet());
	_game->getCurrentState()->getMainCamera()->fadeIn(500);
	SDL_ShowCursor(true);
	_zone = GameManager::getInstance()->getCurrentLevel();
	_visible = true;
	_closed = false;
	_player->setActive(false);

	_game->getSoundManager()->playSFX("doorOpen");
	_game->getSoundManager()->playMusic("shop", true);

	_dialoguePanel->stopAtLastLineShown(true);
	_dialoguePanel->startDialogue(_game->getDialogue("Shop 1 " + to_string(GameManager::getInstance()->getCurrentLevel())));

	ableMainMenu(_game);
}

void ShopMenu::closeShop()
{
	_player->setInputFreezed(false);
	GameManager::getInstance()->setOnShop(false);
	_closed = true;
	_dialoguePanel->endDialogue();
	_game->getSoundManager()->stopMusic();
	_player->setActive(true);
	SDL_ShowCursor(false);

	if (_game->usingJoystick())
		_selectedButton->setSelected(false);

	_game->getSoundManager()->playSFX("doorClose");
	_game->getSoundManager()->playMusic("safe_zone", -1);
}

void ShopMenu::setDialoguePanel(DialoguePanel* dialoguePanel)
{
	_dialoguePanel = dialoguePanel;
	addChild(_dialoguePanel);
}

void ShopMenu::ableMainMenu(Game * game)
{
	_shopButton->setVisible(true);
	_shopText->setVisible(true);
	_talkButton->setVisible(true);
	_talkText->setVisible(true);
	_depotButton->setVisible(true);
	_depotText->setVisible(true);
	_exitButton->setVisible(true);

	if (_game->usingJoystick())
	{
		SDL_WarpMouseGlobal(0, 0);
		_shopButton->setSelected(false);
		_talkButton->setSelected(false);
		_depotButton->setSelected(false);
		_exitButton->setSelected(false);

		_selectedButton = _shopButton;
		_selectedButton->setSelected(true);
		SDL_ShowCursor(false);
	}

	_dialoguePanel->startDialogue(_game->getDialogue("Shop 2 " + to_string(GameManager::getInstance()->getCurrentLevel())));
	_mainMenuAbled = true;
}

void ShopMenu::disableMainMenu(Game * game)
{
	_shopButton->setVisible(false);
	_shopText->setVisible(false);
	_talkButton->setVisible(false);
	_talkText->setVisible(false);
	_depotButton->setVisible(false);
	_depotText->setVisible(false);
	_exitButton->setVisible(false);

	_dialoguePanel->endDialogue();
	_mainMenuAbled = false;
}

void ShopMenu::openCatalogPanel(Game* game)
{
	disableMainMenu(game);

	_catalogPanel->openCatalog();
	_dialoguePanel->startDialogue(_game->getDialogue("Shop Catalog " + to_string(GameManager::getInstance()->getCurrentLevel())));
}

void ShopMenu::closeCatalogPanel(Game * game)
{
	_catalogPanel->closeCatalog();
	_dialoguePanel->endDialogue();

	ableMainMenu(game);
}

void ShopMenu::startTalking(Game* game)
{
	disableMainMenu(game);

	_talking = true;
	_dialoguePanel->startDialogue(_game->getDialogue("Shop Talk " + to_string(GameManager::getInstance()->getCurrentLevel())));
}

void ShopMenu::stopTalking()
{
	ableMainMenu(_game);
}

void ShopMenu::openDepotPanel(Game* game)
{
	disableMainMenu(game);

	_depotPanel->openDepotPanel();
	_dialoguePanel->startDialogue(_game->getDialogue("Shop Depot " + to_string(GameManager::getInstance()->getCurrentLevel())));
}

void ShopMenu::closeDepotPanel(Game * game)
{
	_depotPanel->closeDepotPanel();
	_dialoguePanel->endDialogue();

	ableMainMenu(game);
}

void ShopMenu::exit(Game* game)
{
	_exitButton->setVisible(false);
	_game->getCurrentState()->getMainCamera()->fadeOut(500);

	_game->getCurrentState()->getMainCamera()->onFadeComplete([this](Game* game)
	{
		closeShop();
		setVisible(false); 

		_game->getCurrentState()->getMainCamera()->fadeIn(500);
	});
}