#include "LifeBar.h"
#include "Game.h"


LifeBar::LifeBar(Game* game, Texture* texture) : ImageUI(game, texture)
{
}

void LifeBar::render() const
{
	ImageUI::render();
}

void LifeBar::updateAspect()
{
	float newWidthRatio = ((float(_image->getW()) * *_life) / float(*_maxLife)) / float(_image->getW());
	setClippingAreaSize(newWidthRatio, 1);
	setSize(_clipArea.w, _clipArea.h);
}

void LifeBar::update()
{
	*_life -= 2;	//Temporal para comprobar que funciona
	updateAspect();
}

