#include "ShopPanel.h"
#include "Game.h"
#include "ShopCanvas.h"


ShopPanel::ShopPanel(Game* game) : PanelUI(game)
{
	_exitButton = new ButtonUI(game, game->getTexture("Button"), 5, 80, ShopCanvas::closeShopPanel, { 0,1,2,3 });

	addChild(_exitButton);
}

ShopPanel::~ShopPanel()
{
}

