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
	//_dialoguePanel->startDialogue({});
}

ShopCanvas::~ShopCanvas()
{
}
