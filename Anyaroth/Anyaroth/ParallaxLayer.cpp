#include "ParallaxLayer.h"
#include "Camera.h"


void ParallaxLayer::render() const
{
	_texture->render(_mainRect);
	if (_mainRect.x != 0)
	{
		SDL_Rect auxRect;
		_mainRect.x > 0 ? auxRect = {_mainRect.x - _mainRect.w, 0, _mainRect.w, _mainRect.h } : auxRect = { _mainRect.x + _mainRect.w, 0, _mainRect.w, _mainRect.h };
		_texture->render(auxRect);
	}
}

void ParallaxLayer::update()
{
	_leftDir ? _auxX -= _speed : _auxX += _speed;
	_mainRect.x = _auxX;

	if (_mainRect.x + _mainRect.w <= 0 || _mainRect.x - _mainRect.w >= 0)
		_mainRect.x = 0;
}
