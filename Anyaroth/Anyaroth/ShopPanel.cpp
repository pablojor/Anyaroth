#include "ShopPanel.h"
#include "Game.h"


ShopPanel::ShopPanel(Game* game) : PanelUI(game)
{
	_backGroundImage = new ImageUI();

	addChild(_backGroundImage);
}

ShopPanel::~ShopPanel()
{
}
