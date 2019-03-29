#include "ShopMenu.h"
#include "Game.h"
#include "Player.h"

ButtonUI* ShopMenu::_shopButton = nullptr;
ButtonUI* ShopMenu::_talkButton = nullptr;
ButtonUI* ShopMenu::_depotButton = nullptr;
ButtonUI* ShopMenu::_exitButton = nullptr;

ShopPanel* ShopMenu::_shopPanel = nullptr;
DialoguePanel* ShopMenu::_dialoguePanel = nullptr;
DepotPanel* ShopMenu::_depotPanel = nullptr;

ShopMenu::ShopMenu(Game* game) : PanelUI(game)
{
	//----FONDO----//

	_imageBG = new ImageUI(game, game->getTexture("ShopBackground"), 0, 0);

	addChild(_imageBG);

	//-------------//


	//----BOTONES---//

	int distanceBetweenButtons = 6,
		middleOfTheButtonPanelX = CAMERA_RESOLUTION_X,
		middleOfTheButtonPanelY = 100;

	_talkButton = new ButtonUI(game, game->getTexture("Button"), startTalking, { 0,1,2,3 });
	_talkButton->setPosition(middleOfTheButtonPanelX / 2 - _talkButton->getW() / 2,
							middleOfTheButtonPanelY - (distanceBetweenButtons/2) - _talkButton->getH());

	_shopButton = new ButtonUI(game, game->getTexture("Button"), openShopPanel, { 0,1,2,3 });
	_shopButton->setPosition(middleOfTheButtonPanelX / 2 - _shopButton->getW() / 2,
							_talkButton->getY() - _shopButton->getH() - distanceBetweenButtons);

	_depotButton = new ButtonUI(game, game->getTexture("Button"), openDepotPanel, { 0,1,2,3 });
	_depotButton->setPosition(middleOfTheButtonPanelX / 2 - _depotButton->getW() / 2,
							middleOfTheButtonPanelY + (distanceBetweenButtons/2));

	_exitButton = new ButtonUI(game, game->getTexture("Button"), exit, { 0,1,2,3 });
	_exitButton->setPosition(middleOfTheButtonPanelX / 2 - _exitButton->getW() / 2,
							_depotButton->getY() + _depotButton->getH() + distanceBetweenButtons);

	addChild(_shopButton);
	addChild(_talkButton);
	addChild(_depotButton);
	addChild(_exitButton);

	//-----------//

	//----MOSTRADOR DE DINERO----//

	_playerMoney = new CoinsCounter(game, CAMERA_RESOLUTION_X - 30, 3);

	addChild(_playerMoney);

	//---------------------------//

	//----DISTINTAS FUNCIONALIDADES DE LA TIENDA----//

	_shopPanel = new ShopPanel(game);
	_shopPanel->setVisible(false);

	_dialoguePanel = new DialoguePanel(game, true);

	_depotPanel = new DepotPanel(game, _player);
	_depotPanel->setVisible(false);

	addChild(_shopPanel);
	addChild(_dialoguePanel);
	addChild(_depotPanel);

	//--------------------------------------------//

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
	disableMainMenu(game);
	cout << "hablando" << endl;
}

void ShopMenu::stopTalking(Game * game)
{
	ableMainMenu(game);
}

void ShopMenu::openDepotPanel(Game* game)
{
	disableMainMenu(game);
	_shopPanel->setVisible(true);
}

void ShopMenu::closeDepotPanel(Game * game)
{
	ableMainMenu(game);
	_shopPanel->setVisible(false);
}

void ShopMenu::exit(Game* game)
{
	cout << "cerrando" << endl;
}
