#include "FramedImageUI.h"



FramedImageUI::FramedImageUI(Game* game, Texture* image, int xPos, int yPos) : ImageUI(game, image, xPos, yPos)
{
	_destRect.w = image->getW() / image->getNumCols();
	_destRect.h = image->getH() / image->getNumFils();
}


FramedImageUI::~FramedImageUI()
{
}

void FramedImageUI::render() const
{
	if (_visible)
		_image->renderFrame(_destRect, 0, _frame);
}
