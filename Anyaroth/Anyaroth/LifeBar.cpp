#include "LifeBar.h"
#include "Game.h"


LifeBar::LifeBar(Game* game, Texture* texture, int xPos, int yPos) : ImageUI(game, texture, xPos, yPos)
{
}


void LifeBar::updateLifeBar(const int& life, const int& maxLife)
{
	float newWidthRatio = ((float(_image->getW()) * life) / float(maxLife)) / float(_image->getW());
	setClippingAreaSize(newWidthRatio, 1);
	setSize(_clipArea.w, _clipArea.h);
}

