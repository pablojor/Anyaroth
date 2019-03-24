#include "AnimationUI.h"

AnimationUI::AnimationUI(Game* game, Texture* image, bool loop, uint numFrames, int xPos, int yPos, int initFrameX, int initFrameY, uint lapse) :
		_image(image), 
		_numFrames(numFrames), 
		_initFrameX(initFrameX), _frameY(initFrameY),
		_lapse(lapse), _loop(loop)
{
	_destRect = { xPos, yPos, _image->getW(), _image->getH()};
}

void AnimationUI::render() const
{
	if (_visible)
	{
		_image->renderFrame(_destRect, _frameY, _frameX);
	}
}

void AnimationUI::update(double time)
{
	_timer += time;
	if (_timer >= _lapse)
	{
		if (_loop)
			_frameX = (_frameX + 1) % _numFrames;

		else
		{
			_frameX++;

			if (_frameX == _numFrames)
				_frameX = _numFrames - 1;
		}
		_timer = 0;
	}
}

void AnimationUI::playAnim()
{
	_frameX = _initFrameX;
}
