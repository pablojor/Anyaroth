#include "AnimatedImageUI.h"
#include "Game.h"

AnimatedImageUI::AnimatedImageUI(Game* game, Texture* image, int xPos, int yPos) : FramedImageUI(game, image, xPos, yPos)
{
}
AnimatedImageUI::~AnimatedImageUI()
{
}

void AnimatedImageUI::render() const
{
	if (_visible)
	{
		SDL_Rect winRect = { _destRect.x * GAME_RESOLUTION_X / CAMERA_RESOLUTION_X ,_destRect.y * GAME_RESOLUTION_Y / CAMERA_RESOLUTION_Y ,
		_destRect.w * GAME_RESOLUTION_X / CAMERA_RESOLUTION_X, _destRect.h * GAME_RESOLUTION_Y / CAMERA_RESOLUTION_Y };

		_image->renderFrame(winRect, _currentAnim, _frame);
	}
}

void AnimatedImageUI::update(double deltaTime)
{
	_timer += deltaTime;

	if (_timer >= _animations[_currentAnim].lapse)
	{
		if (_animations[_currentAnim].loop)
			_frame = (_frame + (int)_timer / _animations[_currentAnim].lapse) % _animations[_currentAnim].numFrames;

		else if (!_animations[_currentAnim].animationFinished)
		{
			_frame += (int)_timer / _animations[_currentAnim].lapse;

			if (_frame >= _animations[_currentAnim].numFrames)
			{
				_animations[_currentAnim].animationFinished = true;
				_frame = _animations[_currentAnim].numFrames - 1;
			}
		}
		_timer -= _animations[_currentAnim].lapse*(int)_timer / _animations[_currentAnim].lapse;
	}
}

void AnimatedImageUI::playAnim(uint name)
{
	_animations[_currentAnim].animationFinished = false;

	if (_currentAnim != name)
	{
		_currentAnim = name;
		_frame = 0;
	}
}

void AnimatedImageUI::addAnim(uint name, uint numFrames, bool loop, uint lapse)
{
	_animations.push_back({ name, numFrames, loop, false, lapse });
}