#include "ButtonUI.h"
#include "Game.h"


ButtonUI::ButtonUI(Game* game, Texture* image, const Callback& callback, Frames frames) : FramedImageUI(game, image)
{
	setFrames(frames);
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


bool ButtonUI::handleEvent(const SDL_Event& event)
{
	bool handle = false;
	if (_visible && _inputEnable)
	{
		if (mouseIsOver() || _selected)
		{
			SDL_Cursor* cursor;
			cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
			SDL_SetCursor(cursor);


			if ((event.type == SDL_MOUSEBUTTONDOWN && event.button.state == SDL_PRESSED) || event.type == SDL_CONTROLLERBUTTONDOWN)
			{
				if (event.button.button == SDL_BUTTON_LEFT || event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
				{
					_pressState = Down;
					if (_onDownCallback != nullptr) _onDownCallback(_game);
					handle = true;
				}
			}
			else if ((event.type == SDL_MOUSEBUTTONUP && _pressState == Down) || event.type == SDL_CONTROLLERBUTTONUP)
			{
				if (event.button.button == SDL_BUTTON_LEFT || event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
				{
					_pressState = Up;
					if (_onUpCallback != nullptr) _onUpCallback(_game);
					handle = true;
				}
			}
			else if (_positionState != Over)
			{
				if (_onOverCallback != nullptr) _onOverCallback(_game);
				handle = true;
			}
			_positionState = Over;
		}
		else
		{
			if (_positionState != Out)
			{
				if (_onOutCallback != nullptr) _onOutCallback(_game);
				SDL_Cursor* cursor;
				cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
				SDL_SetCursor(cursor);
				handle = true;
			}
			_positionState = Out;
			_pressState = None;
		}

	}
	return handle;
}

void ButtonUI::update(const double& deltaTime)
{
	if (_visible && _inputEnable)
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
}

void ButtonUI::setFrames(Frames frames)
{
	_onOutFrame = frames.onOut;;
	_onOverFrame = frames.onOver;
	_onDownFrame = frames.onDown;
	_onUpFrame = frames.onUp;
	_onInactiveFrame = frames.onInactive;
}

void ButtonUI::setVisible(bool a)
{
	SDL_Cursor* cursor;
	cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	SDL_SetCursor(cursor);

	_positionState = Out;
	_pressState = None;

	FramedImageUI::setVisible(a);
}

void ButtonUI::setInputEnable(bool b)
{
	_inputEnable = b;
	if (!_inputEnable)
	{
		_frame = _onInactiveFrame;
		_positionState = Out;
		_pressState = None;
	}
}