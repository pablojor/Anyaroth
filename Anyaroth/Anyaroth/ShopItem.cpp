#include "ShopItem.h"

ShopItem* ShopItem::_selected = nullptr;

ShopItem::ShopItem(Game* game, Texture* image, int xPos, int yPos) : ButtonUI(game, image)
{
	setPosition(xPos, yPos);
}

ShopItem::~ShopItem()
{
}

