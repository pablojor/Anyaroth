#include "LifeBar.h"
#include "Game.h"

LifeBar::LifeBar(Game* game, string textName, int xPos, int yPos) : ImageUI(game, game->getTexture(textName), xPos, yPos) 
{
	_image->setColor(77, 77, 77);
}

void LifeBar::updateLifeBar(int life, int maxLife)
{
	if (inUse)
	{
		float newWidthRatio = ((float(_image->getW()) * life) / float(maxLife)) / float(_image->getW());
		setClippingAreaSize(newWidthRatio, 1);
		setSize(_clipArea.w, _clipArea.h);

		//Cambiar color de la barra dependiendo de la vida que tenga
		if (life >= maxLife * 0.75)
			_image->setColor(30, 235, 30);
		else if (life >= maxLife * 0.5)
			_image->setColor(235, 214, 30);
		else if (life >= maxLife * 0.25)
			_image->setColor(209, 104, 43);
		else
			_image->setColor(209, 43, 43);
	}
}

void LifeBar::setInUse(bool b)
{ 
	inUse = b;

	if(!inUse)
		_image->setColor(77, 77, 77);
}