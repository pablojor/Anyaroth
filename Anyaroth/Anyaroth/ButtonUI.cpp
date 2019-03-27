#include "ButtonUI.h"
#include "Game.h"


ButtonUI::ButtonUI(Game* game, Texture* image, int xPos, int yPos, Callback* callback, uint frames[4]) : FramedImageUI(game, image, xPos, yPos)
{
	//_onOutFrame = frames[0];
	//_onOverFrame = frames[1];
	//_onDownFrame = frames[2];
	//_onUpFrame = frames[4];
	_frame = _onOutFrame;
	_onDownCallback = callback;
}

bool ButtonUI::mouseIsOver()
{
	SDL_Rect winRect = { _destRect.x * GAME_RESOLUTION_X / CAMERA_RESOLUTION_X ,_destRect.y * GAME_RESOLUTION_Y / CAMERA_RESOLUTION_Y ,
		_destRect.w * GAME_RESOLUTION_X / CAMERA_RESOLUTION_X, _destRect.h * GAME_RESOLUTION_Y / CAMERA_RESOLUTION_Y };

	Vector2D mousePos = _game->getCurrentState()->getMousePositionOnScreen();

	SDL_Point point = { mousePos.getX(), mousePos.getY() };

	return SDL_PointInRect(&point, &winRect);
}

void ButtonUI::update(const double& deltaTime)
{
	if (_positionState == Out) 
	{
		_frame = _onOutFrame;
	}
	else if (_positionState == Over)
	{
		if (_pressState == Down)
			_frame = _onDownFrame;
		else if (_pressState == Up)
			_frame = _onUpFrame;
		else if (_pressState == None)
			_frame = _onOverFrame;
	}
}

void ButtonUI::handleEvent(const SDL_Event& event)
{
	if (mouseIsOver()) 
	{
		_positionState = Over;

		if (event.type == SDL_MOUSEBUTTONDOWN && event.button.state == SDL_PRESSED)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				_pressState = Down;
				if (_onDownCallback != nullptr) _onDownCallback(_game);
			}
		}
		else if (event.type == SDL_MOUSEBUTTONUP)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				_pressState = Up;
				if (_onUpCallback != nullptr) _onUpCallback(_game);
			}
		}
	}
	else
	{
		_positionState = Out;
		_pressState = None;
	}
}

void ButtonUI::setFrames(uint onOut, uint onOver, uint onDown, uint onUp)
{
	_onOutFrame = onOut;
	_onOverFrame = onOver;
	_onDownFrame = onDown;
	_onUpFrame = onUp;
}
