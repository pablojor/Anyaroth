#include "ImageUI.h"
#include "Game.h"

ImageUI::ImageUI(Game* game, Texture* image, int xPos, int yPos) : UIElement(game), _image(image)
{
	_destRect = { xPos, yPos, image->getW(), image->getH() };
	_clipArea = { 0, 0, image->getW(), image->getH() };
}

void ImageUI::render() const
{
	if (_visible) 
	{
		SDL_Rect winRect = { _destRect.x * GAME_RESOLUTION_X / CAMERA_RESOLUTION_X ,_destRect.y * GAME_RESOLUTION_Y / CAMERA_RESOLUTION_Y ,
			_destRect.w * GAME_RESOLUTION_X / CAMERA_RESOLUTION_X, _destRect.h * GAME_RESOLUTION_Y / CAMERA_RESOLUTION_Y };

		_image->render(winRect, _clipArea);
	}
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

void ImageUI::setScale(float s)
{
	_destRect.w *= s;
	_destRect.h *= s;
}
