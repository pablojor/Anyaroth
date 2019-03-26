#include "ShopItem.h"



ShopItem::ShopItem(Game * game) : PanelUI (game)
{
	_gunImage = new ImageUI();
	_gunInfo = new TextUI();

	addChild(_gunImage);
	addChild(_gunInfo);
}

ShopItem::~ShopItem()
{
}

void ShopItem::changeItemImage()
{
}

void ShopItem::changeItemInfo()
{
}
