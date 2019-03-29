#include "CatalogPanel.h"
#include "Game.h"
#include "ShopMenu.h"

CatalogPanel::CatalogPanel(Game* game, ShopMenu* shop) : _shop(shop), PanelUI(game)
{
	_exitButton = new ButtonUI(game, game->getTexture("Button"), ShopMenu::closeCatalogPanel, { 0,1,2,3 });
	_exitButton->setPosition(5, 5);

	addChild(_exitButton);
}

void CatalogPanel::openCatalog()
{
	_visible = true;

	_shop->getDialoguePanel()->startDialogue({
	_game->getTexture("DialogueFace"),
	"exampleVoice",
	"Ollivander",
	{ "Te gusta algo de lo que tengo?"},
	{ 0 },
	{ " ", " ", " ", " " }
		});
}

void CatalogPanel::closeCatalog()
{
	_visible = false;

	_shop->getDialoguePanel()->endDialogue();
}