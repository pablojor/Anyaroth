#include "AnimatedImageUI.h"



AnimatedImageUI::AnimatedImageUI(Game* game, Texture* image, int xPos, int yPos) : FramedImageUI(game, image, xPos, yPos)
{

}
AnimatedImageUI::~AnimatedImageUI()
{
}

void AnimatedImageUI::render() const
{
	if (_visible)
		_image->renderFrame(_destRect, _currentAnim, _frame);
	/*
		SDL_Rect destRect;
		destRect.w = (_texture->getW() / _texture->getNumCols()) * _transform->getScale().getX();
		destRect.h = (_texture->getH() / _texture->getNumFils()) * _transform->getScale().getY();
		destRect.x = _transform->getPosition().getX() - _transform->getAnchor().getX() * destRect.w - c->getCameraPosition().getX();
		destRect.y = _transform->getPosition().getY() - _transform->getAnchor().getY() * destRect.h - c->getCameraPosition().getY();

		SDL_Point anchor = { _transform->getAnchor().getX() * destRect.w, _transform->getAnchor().getY() * destRect.h };
		*/

}

void AnimatedImageUI::update(double time)
{
	_timer += time;

	if (_timer >= _animations[_currentAnim].lapse)
	{
		if (_animations[_currentAnim].loop)
			_frame = (_frame + 1) % _animations[_currentAnim].numFrames;

		else if (!_animations[_currentAnim].animationFinished)
		{
			_frame++;

			if (_frame == _animations[_currentAnim].numFrames)
			{
				_animations[_currentAnim].animationFinished = true;
				_frame = _animations[_currentAnim].numFrames - 1;
			}
		}
		_timer = 0;
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
	//double lapse = FRAME_RATE * numFrames;
	_animations.push_back({ name, numFrames, loop, false, lapse });
}
