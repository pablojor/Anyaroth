#include "DashViewer.h"
#include "Game.h"

DashViewer::DashViewer(Game * game, int xPos, int yPos) : ImageUI(game, game->getTexture("DashIcon"), xPos, yPos) {}

void DashViewer::render() const
{
	if (_visible)
	{
		SDL_Rect auxRect = _destRect;
		for (int i = 0; i < _dashNumber; i++)		
		{
			_image->render(auxRect, _clipArea);
			auxRect.x += _image->getW() + 2;
		}
	}
}