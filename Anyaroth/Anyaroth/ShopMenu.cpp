#include "ShopMenu.h"
#include "Game.h"
#include "Player.h"

ButtonUI* ShopMenu::_shopButton = nullptr;
ButtonUI* ShopMenu::_talkButton = nullptr;
ButtonUI* ShopMenu::_depotButton = nullptr;
ButtonUI* ShopMenu::_exitButton = nullptr;
DialoguePanel* ShopMenu::_dialoguePanel = nullptr;
ShopPanel* ShopMenu::_shopPanel = nullptr;

ShopMenu::ShopMenu(Game* game) : PanelUI(game)
{
	int distanceBetweenButtons = 5,
		middleOfTheButtonPanel = 100;

	_talkButton = new ButtonUI(game, game->getTexture("Button"), startTalking, { 0,1,2,3 });
	_talkButton->setPosition(CAMERA_RESOLUTION_X / 2 - _talkButton->getW() / 2, 
							middleOfTheButtonPanel - (distanceBetweenButtons/2) - _talkButton->getH());

	_shopButton = new ButtonUI(game, game->getTexture("Button"), openShopPanel, { 0,1,2,3 });
	_shopButton->setPosition(CAMERA_RESOLUTION_X / 2 - _shopButton->getW() / 2, 
							_talkButton->getY() - _shopButton->getH() - distanceBetweenButtons);

	_depotButton = new ButtonUI(game, game->getTexture("Button"), openDepotPanel, { 0,1,2,3 });
	_depotButton->setPosition(CAMERA_RESOLUTION_X / 2 - _depotButton->getW() / 2, 
							middleOfTheButtonPanel + (distanceBetweenButtons/2));

	_exitButton = new ButtonUI(game, game->getTexture("Button"), exit, { 0,1,2,3 });
	_exitButton->setPosition(CAMERA_RESOLUTION_X / 2 - _exitButton->getW() / 2,
							_depotButton->getY() + _depotButton->getH() + distanceBetweenButtons);
		
	_dialoguePanel = new DialoguePanel(game, true);

	addChild(_shopButton);
	addChild(_talkButton);
	addChild(_depotButton);
	addChild(_exitButton);

	addChild(_dialoguePanel);

	_shopPanel = new ShopPanel(game);
	_shopPanel->setVisible(false);

	addChild(_shopPanel);

}

void ShopMenu::openShop()
{
	_visible = true;
	_player->setActive(false);
	open();
}

void ShopMenu::open()
{
	_dialoguePanel->startDialogue({
	_game->getTexture("DialogueFace"),
	"exampleVoice",
	"Jose Mar�a",
	{ "*Bzzt..Bip, bip..* Hey, �qu� tal?",
	"Aj�, con que programando... ya veo...",
	"�Pues sigue con eso, chaval! Deja de jugar tanto al Sekiro y ponte a estudiar de una maldita vez, escoria infrahumana (...) �Adew! *Bip*" },
	{ 0,1,2 },
	{ " ", " ", " ", " " }
		});
}

void ShopMenu::closeShop()
{
	_visible = false;
	_player->setActive(true);
	reset();
}

void ShopMenu::reset()
{
	_dialoguePanel->endDialogue();
}

void ShopMenu::ableMainMenu(Game * game)
{
	_shopButton->setVisible(true);
	_talkButton->setVisible(true);
	_depotButton->setVisible(true);
	_exitButton->setVisible(true);
}

void ShopMenu::disableMainMenu(Game * game)
{
	_shopButton->setVisible(false);
	_talkButton->setVisible(false);
	_depotButton->setVisible(false);
	_exitButton->setVisible(false);
}

void ShopMenu::openShopPanel(Game* game)
{
	disableMainMenu(game);
	_shopPanel->setVisible(true);
}

void ShopMenu::closeShopPanel(Game * game)
{
	ableMainMenu(game);
	_shopPanel->setVisible(false);
}

void ShopMenu::startTalking(Game* game)
{
	cout << "hablando" << endl;
}

void ShopMenu::stopTalking(Game * game)
{

}

void ShopMenu::openDepotPanel(Game* game)
{
	cout << "en almacen" << endl;
}

void ShopMenu::closeDepotPanel(Game * game)
{

}

void ShopMenu::exit(Game* game)
{
	cout << "cerrando" << endl;
}
