#include "FramedImageUI.h"
#include "Game.h"

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
	{
		SDL_Rect winRect = { _destRect.x * GAME_RESOLUTION_X / CAMERA_RESOLUTION_X ,_destRect.y * GAME_RESOLUTION_Y / CAMERA_RESOLUTION_Y ,
		_destRect.w * GAME_RESOLUTION_X / CAMERA_RESOLUTION_X, _destRect.h * GAME_RESOLUTION_Y / CAMERA_RESOLUTION_Y };

		_image->renderFrame(winRect, 0, _frame);
	}
}
