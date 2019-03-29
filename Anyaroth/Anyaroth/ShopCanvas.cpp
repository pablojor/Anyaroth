#include "ShopCanvas.h"
#include "Game.h"

ButtonUI* ShopCanvas::_shopButton = nullptr;
ButtonUI* ShopCanvas::_talkButton = nullptr;
ButtonUI* ShopCanvas::_depotButton = nullptr;
ButtonUI* ShopCanvas::_exitButton = nullptr;
DialoguePanel* ShopCanvas::_dialoguePanel = nullptr;
ShopPanel* ShopCanvas::_shopPanel = nullptr;

ShopCanvas::ShopCanvas(Game* game)
{
	_shopButton = new ButtonUI(game, game->getTexture("Button"), 5, 10, openShopPanel, { 0,1,2,3 });
	_talkButton = new ButtonUI(game, game->getTexture("Button"), 5, 30, startTalking, { 0,1,2,3 });
	_depotButton = new ButtonUI(game, game->getTexture("Button"), 5, 50, openDepotPanel, { 0,1,2,3 });
	_exitButton = new ButtonUI(game, game->getTexture("Button"), 5, 70, exit, { 0,1,2,3 });

	_dialoguePanel = new DialoguePanel(game, true);

	addUIElement(_shopButton);
	addUIElement(_talkButton);
	addUIElement(_depotButton);
	addUIElement(_exitButton);

	addUIElement(_dialoguePanel);

	_shopPanel = new ShopPanel(game);
	_shopPanel->setVisible(false);

	addUIElement(_shopPanel);

	//Inicializaciones
	_dialoguePanel->startDialogue({
		game->getTexture("DialogueFace"),
		"exampleVoice",
		"Jose Mar�a",
		{ "*Bzzt..Bip, bip..* Hey, �qu� tal?",
		"Aj�, con que programando... ya veo...",
		"�Pues sigue con eso, chaval! Deja de jugar tanto al Sekiro y ponte a estudiar de una maldita vez, escoria infrahumana (...) �Adew! *Bip*" },
		{ 0,1,2 },
		{ " ", " ", " ", " " }
		});
}

void ShopCanvas::ableMainMenu(Game * game)
{
	_shopButton->setVisible(true);
	_talkButton->setVisible(true);
	_depotButton->setVisible(true);
	_exitButton->setVisible(true);
}

void ShopCanvas::disableMainMenu(Game * game)
{
	_shopButton->setVisible(false);
	_talkButton->setVisible(false);
	_depotButton->setVisible(false);
	_exitButton->setVisible(false);
}

void ShopCanvas::openShopPanel(Game* game)
{
	disableMainMenu(game);
	_shopPanel->setVisible(true);
}

void ShopCanvas::closeShopPanel(Game * game)
{
	ableMainMenu(game);
	_shopPanel->setVisible(false);
}

void ShopCanvas::startTalking(Game* game)
{

}

void ShopCanvas::stopTalking(Game * game)
{

}

void ShopCanvas::openDepotPanel(Game* game)
{

}

void ShopCanvas::closeDepotPanel(Game * game)
{

}

void ShopCanvas::exit(Game* game)
{

}
