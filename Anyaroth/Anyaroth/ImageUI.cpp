#include "ImageUI.h"
#include "Game.h"

ImageUI::ImageUI(Game* game, Texture* image) : UIElement(game), _image(image)
{
	_destRect = { 0, 0, image->getW(), image->getH() };
	_clipArea = _destRect;
}

void ImageUI::render() const
{
	if (_visible) 
		_image->render(_destRect, _clipArea);
}

void ImageUI::setPosition(int x, int y)
{
	_destRect.x = x;
	_destRect.y = y;
}

void ImageUI::setSize(int w, int h)
{
	_destRect.w = w;
	_destRect.h = h;
}

//Valores de 0 a 1
void ImageUI::setClippingAreaSize(float w, float h)
{
	_clipArea.w = _image->getW() * w;
	_clipArea.h = _image->getH() * h;
}
