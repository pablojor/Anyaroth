#include "ImageUI.h"

ImageUI::ImageUI(Texture * image) : _image(image)
{
	destRect = { 0, 0, image->getW(), image->getH() };
	clipArea = destRect;
}

void ImageUI::render() const
{
	if (_visible) 
		_image->render(destRect, clipArea);
}

void ImageUI::setPosition(int x, int y)
{
	destRect.x = x;
	destRect.y = y;
}

void ImageUI::setSize(int w, int h)
{
	destRect.w = w;
	destRect.h = h;
}

void ImageUI::setClippingAreaSize(float w, float h)
{
	clipArea.w = destRect.w * w;
	clipArea.h = destRect.h * h;
}
