#include "ShopMenu.h"
#include "Game.h"
#include "Player.h"
#include "PlayStateHUD.h"

#include <json.hpp>

using namespace nlohmann;

ButtonUI* ShopMenu::_shopButton = nullptr;
ButtonUI* ShopMenu::_talkButton = nullptr;
ButtonUI* ShopMenu::_depotButton = nullptr;
ButtonUI* ShopMenu::_exitButton = nullptr;

CatalogPanel* ShopMenu::_catalogPanel = nullptr;
DialoguePanel* ShopMenu::_dialoguePanel = nullptr;
DepotPanel* ShopMenu::_depotPanel = nullptr;

Player* ShopMenu::_player = nullptr;

bool ShopMenu::_exit = false;

ShopMenu::ShopMenu(Game* game) : PanelUI(game)
{
	//----FONDO----//

	_imageBG = new ImageUI(game, game->getTexture("ShopBackground"), 0, 0);
	addChild(_imageBG);


	//----BOTONES---//

	int distanceBetweenButtons = 6,
		middleOfTheButtonPanelX = CAMERA_RESOLUTION_X,
		middleOfTheButtonPanelY = 100;

	_talkButton = new ButtonUI(game, game->getTexture("Button"), startTalking, { 0,1,2,3 });
	_talkButton->setPosition(middleOfTheButtonPanelX / 2 - _talkButton->getW() / 2,
							middleOfTheButtonPanelY - (distanceBetweenButtons/2) - _talkButton->getH());

	_shopButton = new ButtonUI(game, game->getTexture("Button"), openCatalogPanel, { 0,1,2,3 });
	_shopButton->setPosition(middleOfTheButtonPanelX / 2 - _shopButton->getW() / 2,
							_talkButton->getY() - _shopButton->getH() - distanceBetweenButtons);

	_depotButton = new ButtonUI(game, game->getTexture("Button"), openDepotPanel, { 0,1,2,3 });
	_depotButton->setPosition(middleOfTheButtonPanelX / 2 - _depotButton->getW() / 2,
							middleOfTheButtonPanelY + (distanceBetweenButtons/2));

	_exitButton = new ButtonUI(game, game->getTexture("Button"), exitBool, { 0,1,2,3 });
	_exitButton->setPosition(middleOfTheButtonPanelX / 2 - _exitButton->getW() / 2,
							_depotButton->getY() + _depotButton->getH() + distanceBetweenButtons);
	_exitButton->onUp(exit);

	addChild(_shopButton);
	addChild(_talkButton);
	addChild(_depotButton);
	addChild(_exitButton);


	//----MOSTRADOR DE DINERO----//

	_playerMoney = new CoinsCounter(game, CAMERA_RESOLUTION_X - 30, 3);

	addChild(_playerMoney);


	//----DISTINTAS FUNCIONALIDADES DE LA TIENDA----//

	_catalogPanel = new CatalogPanel(game);
	_catalogPanel->setVisible(false);

	_dialoguePanel = new DialoguePanel(game, true);

	_depotPanel = new DepotPanel(game);
	_depotPanel->setVisible(false);

	addChild(_catalogPanel);
	addChild(_dialoguePanel);
	addChild(_depotPanel);

	loadWeaponInfo();

	_catalogPanel->setItems(_items);
}

ShopMenu::~ShopMenu()
{
	for (auto it = _items.begin(); it != _items.end(); it++)
	{
		delete *it;
	}
}

void ShopMenu::loadWeaponInfo()
{
	ifstream file;
	json j;

	file.open(INFO_PATH + "weapon_info.json");
	if (file.is_open())
	{
		file >> j;

		for (json::iterator it = j.begin(); it != j.end(); ++it) 
		{
			json weapon = it.value();

			for (json::iterator typeWeapon = weapon.begin(); typeWeapon != weapon.end(); ++typeWeapon)
			{
				auto item = new ShopItem(_game, _game->getTexture(typeWeapon.value()["icon"].get<string>()));

				item->setItemInfo({ typeWeapon.value()["zona"], typeWeapon.key(), typeWeapon.value()["damage"], typeWeapon.value()["cadence"], typeWeapon.value()["range"], false, false });
				_items.push_back(item);
			}
		}
	}
	else
		cout << "Error al cargar " << INFO_PATH << "weapon_info.json" << endl;
}

void ShopMenu::setPlayer(Player* ply) 
{ 
	_player = ply;
	_playerMoney->updateCoinsCounter(_player->getBank());

	_catalogPanel->setPlayer(_player);
	_depotPanel->setPlayer(_player);
}

void ShopMenu::openShop(int zona)
{
	if (zona != _zona)
	{
		_zona = zona;
		_catalogPanel->updateCatalog(_zona);
	}
	_visible = true;
	_player->setActive(false);
	_exit = false;

	_dialoguePanel->startDialogue({
		_game->getTexture("DialogueFace"),
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
	_player->setActive(true);
}

void ShopMenu::ableMainMenu(Game * game)
{
	_shopButton->setVisible(true);
	_talkButton->setVisible(true);
	_depotButton->setVisible(true);
	_exitButton->setVisible(true);

	_dialoguePanel->startDialogue({
			game->getTexture("DialogueFace"),
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
	_talkButton->setVisible(false);
	_depotButton->setVisible(false);
	_exitButton->setVisible(false);

	_dialoguePanel->endDialogue();
}

void ShopMenu::openCatalogPanel(Game* game)
{
	disableMainMenu(game);
	_dialoguePanel->setInShop(false);

	_catalogPanel->openCatalog();
	_dialoguePanel->startDialogue({
			game->getTexture("DialogueFace"),
			"exampleVoice",
			"Ollivander",
			{ "Te gusta algo de lo que tengo?"},
			{ 0 },
			{ " ", " ", " ", " " }
	});
}

void ShopMenu::closeCatalogPanel(Game * game)
{
	_catalogPanel->setVisible(false);
	_dialoguePanel->endDialogue();

	ableMainMenu(game);
}

void ShopMenu::startTalking(Game* game)
{
	//disableMainMenu(game);
	_dialoguePanel->endDialogue();
	_dialoguePanel->startDialogue({
			game->getTexture("DialogueFace"),
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
	_dialoguePanel->endDialogue();
	ableMainMenu(_game);
}

void ShopMenu::openDepotPanel(Game* game)
{
	disableMainMenu(game);

	_depotPanel->setVisible(true);
	_dialoguePanel->startDialogue({
			game->getTexture("DialogueFace"),
			"exampleVoice",
			"Ollivander",
			{ "¡Equipate bien antes de salir ahi fuera!"},
			{ 0 },
			{ " ", " ", " ", " " }
	});
}

void ShopMenu::closeDepotPanel(Game * game)
{
	_depotPanel->setVisible(false);
	_dialoguePanel->endDialogue();

	ableMainMenu(game);
}

void ShopMenu::exitBool(Game* game)
{
	_exit = true;
}
void ShopMenu::exit(Game* game)
{
	if (_exit)
	{
		cout << "cerrando" << endl;
		closeShop();
		PlayStateHUD::closeShopMenu(game);
	}
}
