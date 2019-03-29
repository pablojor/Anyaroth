#include "ShopPanel.h"
#include "Game.h"
#include "ShopMenu.h"


ShopPanel::ShopPanel(Game* game) : PanelUI(game)
{
	_exitButton = new ButtonUI(game, game->getTexture("Button"), ShopMenu::closeShopPanel, { 0,1,2,3 });
	_exitButton->setPosition(5, 5);

	addChild(_exitButton);
}

ShopPanel::~ShopPanel()
{
}

