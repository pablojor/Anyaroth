#include "AnimatedSpriteComponent.h"
#include "GameComponent.h"
#include "Camera.h"
#include "Game.h"

void AnimatedSpriteComponent::render(Camera* c) const
{
	if (_active)
	{
		SDL_Rect destRect;
		destRect.w = (_texture->getW() / _texture->getNumCols()) * _transform->getScale().getX();
		destRect.h = (_texture->getH() / _texture->getNumFils()) * _transform->getScale().getY();
		destRect.x = _transform->getPosition().getX() - _transform->getAnchor().getX() * destRect.w - c->getCameraPosition().getX();
		destRect.y = _transform->getPosition().getY() - _transform->getAnchor().getY() * destRect.h - c->getCameraPosition().getY();

		SDL_Rect winRect = { destRect.x * GAME_RESOLUTION_X / c->getCameraSize().getX() ,destRect.y * GAME_RESOLUTION_Y / c->getCameraSize().getY() ,
							destRect.w * GAME_RESOLUTION_X / c->getCameraSize().getX() + 1, destRect.h * GAME_RESOLUTION_Y / c->getCameraSize().getY() + 1 }; //+1 para el tema del Zoom

		SDL_Point anchor = { _transform->getAnchor().getX() * winRect.w, _transform->getAnchor().getY() * winRect.h };
		
		_texture->renderFrame(winRect, _currentAnim, _frame, _transform->getRotation(), anchor, (_flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE));
	}
}

void AnimatedSpriteComponent::update(double time)
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

void AnimatedSpriteComponent::playAnim(uint name)
{
	_animations[_currentAnim].animationFinished = false;

	if (_currentAnim != name)
	{
		_currentAnim = name;
		_frame = 0;
	}
}

void AnimatedSpriteComponent::addAnim(uint name, uint numFrames, bool loop, uint lapse)
{
	//double lapse = FRAME_RATE * numFrames;
	_animations.push_back({ name, numFrames, loop, false, lapse });
}