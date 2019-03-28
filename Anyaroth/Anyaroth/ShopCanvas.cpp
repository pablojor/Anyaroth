#include "ShopCanvas.h"
#include "Game.h"


ShopCanvas::ShopCanvas(Game* game)
{
	_shopButton = new ButtonUI(game, game->getTexture("Button"), 5, 10, nullptr, { 0,1,2,3 });
	_talkButton = new ButtonUI(game, game->getTexture("Button"), 5, 30, nullptr, { 0,1,2,3 });
	_depotButton = new ButtonUI(game, game->getTexture("Button"), 5, 50, nullptr, { 0,1,2,3 });
	_exitButton = new ButtonUI(game, game->getTexture("Button"), 5, 70, nullptr, { 0,1,2,3 });

	_dialoguePanel = new DialoguePanel(game);

	addUIElement(_shopButton);
	addUIElement(_talkButton);
	addUIElement(_depotButton);
	addUIElement(_exitButton);

	addUIElement(_dialoguePanel);

	_shopPanel = new ShopPanel(game);

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

void ShopCanvas::openShopPanel()
{
}

void ShopCanvas::talk()
{
}

void ShopCanvas::openDepotPanel()
{
}

void ShopCanvas::exit()
{
}
