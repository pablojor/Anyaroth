#include "ParallaxLayer.h"
#include "Camera.h"
#include "Game.h"


void ParallaxLayer::render() const
{
	SDL_Rect destRect = {	_mainRect.x * GAME_RESOLUTION_X / CAMERA_RESOLUTION_X ,_mainRect.y * GAME_RESOLUTION_Y / CAMERA_RESOLUTION_Y ,
							_mainRect.w * GAME_RESOLUTION_X / CAMERA_RESOLUTION_X, _mainRect.h * GAME_RESOLUTION_Y / CAMERA_RESOLUTION_Y };

	_texture->render(destRect);
	if (destRect.x != 0)
	{
		SDL_Rect auxRect;
		destRect.x > 0 ? auxRect = { destRect.x - destRect.w, 0, destRect.w, destRect.h } : auxRect = { destRect.x + destRect.w, 0, destRect.w, destRect.h };
		_texture->render(auxRect);
	}
}

void ParallaxLayer::update(double time)
{
	_leftDir ? _auxX -= _speed : _auxX += _speed;
	_mainRect.x = _auxX;

	if (_mainRect.x + _mainRect.w <= 0 || _mainRect.x - _mainRect.w >= 0)
		_mainRect.x = 0;
}