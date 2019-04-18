#include "ShopMenu.h"
#include "Game.h"
#include "Player.h"
#include "PlayStateHUD.h"
#include <json.hpp>
#include "WeaponManager.h"
#include "SoundManager.h"

ShopMenu::ShopMenu(Game* game) : PanelUI(game)
{
	//----FONDO----//

	_imageBG = new AnimatedImageUI(game, game->getTexture("ShopBackground"));
	_imageBG->addAnim(AnimatedImageUI::Idle, 6, true);
	addChild(_imageBG);


	//----BOTONES---//

	int distanceBetweenButtons = 6,
		middleOfTheButtonPanelX = CAMERA_RESOLUTION_X,
		middleOfTheButtonPanelY = 100;

	//BOTON DE HABLAR
	_talkButton = new ButtonUI(game, game->getTexture("ShopButton"), [this](Game* game) { startTalking(game); }, { 0, 1, 1, 1, 1 });
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
	_depotButton = new ButtonUI(game, game->getTexture("ShopButton"), [this](Game* game) { openDepotPanel(game); }, { 0, 1, 1, 1, 1 });
	_depotButton->setPosition(middleOfTheButtonPanelX / 2 - _depotButton->getW() / 2,
		middleOfTheButtonPanelY + (distanceBetweenButtons / 2));

	_depotText = new TextUI(game, "Depot", game->getFont("ARIAL12"), 12, 0, 0, { 145, 255, 255, 255 });
	_depotText->setPosition(_depotButton->getX() + _depotButton->getW() / 2 - _depotText->getW() / 2,
		_depotButton->getY() + _depotButton->getH() / 2 - _depotText->getH() / 2);

	//BOTON DE SALIR
	_exitButton = new ButtonUI(game, game->getTexture("ExitButton"), nullptr, { 0, 1, 1, 1 });
	_exitButton->setPosition(CAMERA_RESOLUTION_X - _exitButton->getW() - 12, 188 - 1 - _exitButton->getH());

	_exitButton->onUp([this](Game* game) { exit(game); });

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

	_catalogPanel->setItems(&_items, _zone);
	_depotPanel->setItems(&_items);
}

ShopMenu::~ShopMenu()
{
	_depotPanel->removeItems();
	_catalogPanel->removeItems();
	if (_dialoguePanel != nullptr) removeChild(_dialoguePanel);
	for (auto it = _items.begin(); it != _items.end(); it++)
	{
		delete *it;
	}
}


void ShopMenu::update(const double& deltaTime)
{
	PanelUI::update(deltaTime);

	if (_talking && _dialoguePanel->conversationEnd())
	{
		_talking = false;
		stopTalking();
	}
}

void ShopMenu::loadWeaponInfo()
{
	auto weaponInfo = WeaponManager::getAllWeaponInfo();
	for (auto it = weaponInfo.begin(); it != weaponInfo.end(); it++)
	{
		auto item = new ShopItem(_game, _game->getTexture((*it).second._iconName));

		bool sold = false;
		bool equiped = false;

		if ((*it).second._zone == -1)
		{
			equiped = true;
			sold = true;
		}

		item->setItemInfo({ (*it).second._zone, (*it).second._name, (*it).second._price ,(*it).second._damage, (*it).second._cadence, (*it).second._clip, (*it).first, (*it).second._iconName, (*it).second._rarityFrame, sold, equiped });
		_items.push_back(item);
	}
}

void ShopMenu::setPlayer(Player* ply)
{
	_player = ply;

	_catalogPanel->setPlayer(_player);
	_depotPanel->setPlayer(_player);
}

void ShopMenu::openShop(int zona)
{
	SDL_ShowCursor(true);
	if (zona != _zone)
		_zone = zona;
	_visible = true;
	_closed = false;
	_player->setActive(false);

	_game->getSoundManager()->playMusic("shop", true);

	_dialoguePanel->stopAtLastLineShown(true);
	_dialoguePanel->startDialogue({
		nullptr,
		"exampleVoice",
		"Ollivander",
		{"Espero que encuentres algo de tu agrado"},
		{ 2 },
		{ " ", " ", " ", " " }
		});
}

void ShopMenu::closeShop()
{
	_dialoguePanel->endDialogue();
	//_dialoguePanel->stopAtLastLineShown(false);

	_game->getSoundManager()->stopMusic();

	_player->setActive(true);
	SDL_ShowCursor(false);
	_closed = true;
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

	_dialoguePanel->startDialogue({
		nullptr,
		"exampleVoice",
		"Ollivander",
		{ "Quieres algo mas?"},
		{ 1 },
		{ " ", " ", " ", " " }
		});
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
}

void ShopMenu::openCatalogPanel(Game* game)
{
	disableMainMenu(game);

	_catalogPanel->openCatalog();

	_dialoguePanel->startDialogue({
		nullptr,
		"exampleVoice",
		"Ollivander",
		{ "Te gusta algo de lo que tengo?"},
		{ 0 },
		{ " ", " ", " ", " " }
		});
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
	_dialoguePanel->startDialogue({
		nullptr,
		"exampleVoice",
		"Ollivander",
		{ "He oido que la colmena esta experimentando con sustancias mutagenicas para crear super-anyas.",
		"Si esto es verdad... estamos jodidos.",
		"Pero bueno...",
		"Esperemos que solo sea un rumor."},
		{ 2, 1, 2, 0 },
		{ " ", " ", " ", " " }
		});
}

void ShopMenu::stopTalking()
{
	ableMainMenu(_game);
}

void ShopMenu::openDepotPanel(Game* game)
{
	disableMainMenu(game);

	_depotPanel->openDepotPanel();

	_dialoguePanel->startDialogue({
		nullptr,
		"exampleVoice",
		"Ollivander",
		{ "¡Equipate bien antes de salir ahi fuera!"},
		{ 0 },
		{ " ", " ", " ", " " }
		});
}

void ShopMenu::closeDepotPanel(Game * game)
{
	_depotPanel->closeDepotPanel();
	_dialoguePanel->endDialogue();

	ableMainMenu(game);
}

void ShopMenu::exit(Game* game)
{
	closeShop();
	setVisible(false);
}
