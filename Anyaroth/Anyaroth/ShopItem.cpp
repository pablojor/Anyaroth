#include "ShopItem.h"


ShopItem::ShopItem(Game* game, Texture* image, int xPos, int yPos) : ButtonUI(game, image, 0, {0, 1, 1, 1, 1})
{
	setPosition(xPos, yPos);
}

ShopItem::~ShopItem()
{
}

