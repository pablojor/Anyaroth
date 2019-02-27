#include "ImageUI.h"

ImageUI::ImageUI(Texture * image) : _image(image)
{
	destRect = { 0, 0, image->getW(), image->getH() };
	clipArea = { 0, 0, 0, 0 };
}

void ImageUI::render() const
{
	if (_visible) 
	{
		_image->render(destRect, clipArea);
		UIElement::render();
	}
}

void ImageUI::setPosition(int x, int y)
{
	destRect.x = x;
	destRect.y = y;
	clipArea.x = x;
	clipArea.y = y;
}

void ImageUI::setSize(int w, int h)
{
	destRect.w = w;
	destRect.h = h;
}

void ImageUI::setClippingArea(int w, int h)
{
	clipArea.w = w;
	clipArea.h = h;
}
