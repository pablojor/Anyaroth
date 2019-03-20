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
			SDL_Rect winRect = { auxRect.x * GAME_RESOLUTION_X / CAMERA_RESOLUTION_X ,auxRect.y * GAME_RESOLUTION_Y / CAMERA_RESOLUTION_Y ,
				auxRect.w * GAME_RESOLUTION_X / CAMERA_RESOLUTION_X, auxRect.h * GAME_RESOLUTION_Y / CAMERA_RESOLUTION_Y };

			_image->render(winRect, _clipArea);
			auxRect.x += _image->getW() + 2;
		}
	}
}