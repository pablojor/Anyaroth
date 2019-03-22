#include "LifeBar.h"
#include "Game.h"

LifeBar::LifeBar(Game* game, int xPos, int yPos) : ImageUI(game, game->getTexture("MascaraBarraVida"), xPos, yPos) {}

void LifeBar::updateLifeBar(const int& life, const int& maxLife)
{
	float newWidthRatio = ((float(_image->getW()) * life) / float(maxLife)) / float(_image->getW());
	setClippingAreaSize(newWidthRatio, 1);
	setSize(_clipArea.w, _clipArea.h);

	if (life >= maxLife*0.75)
		_image->setColor(30, 235, 30);
	else if (life >= maxLife * 0.5)
		_image->setColor(235, 214, 30);
	else if (life >= maxLife * 0.25)
		_image->setColor(209, 104, 43);
	else
		_image->setColor(209, 43, 43);
}