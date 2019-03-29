#include "DepotPanel.h"
#include "Player.h"
#include "ShopMenu.h"

DepotPanel::DepotPanel(Game* game, ShopMenu* shop, Player* ply) : _shop(shop), _player(ply), PanelUI(game)
{
	_exitButton = new ButtonUI(game, game->getTexture("Button"), ShopMenu::closeDepotPanel, { 0,1,2,3 });
	_exitButton->setPosition(5, 5);

	addChild(_exitButton);
}

void DepotPanel::openDepot()
{
	_visible = true;

	_shop->getDialoguePanel()->startDialogue({
	_game->getTexture("DialogueFace"),
	"exampleVoice",
	"Ollivander",
	{ "¡Cuido tus cosas como si fueran mías! ¡Por eso ni te preocupes!"},
	{ 0 },
	{ " ", " ", " ", " " }
		});
}

void DepotPanel::closeDepot()
{
	_visible = false;

	_shop->getDialoguePanel()->endDialogue();
}
