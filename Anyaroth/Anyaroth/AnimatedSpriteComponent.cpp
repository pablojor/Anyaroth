#include "AnimatedSpriteComponent.h"
#include "GameComponent.h"
#include "Camera.h"


AnimatedSpriteComponent::AnimatedSpriteComponent(GameComponent* obj) : SpriteComponent(obj), PhysicsComponent(obj), RenderComponent(obj), Component()
{

}


AnimatedSpriteComponent::~AnimatedSpriteComponent()
{

}

void AnimatedSpriteComponent::render(Camera* c) const
{
	if (_active)
	{
		SDL_Rect destRect;
		destRect.w = (_texture->getW() / _texture->getNumCols()) * _transform->getScale().getX();
		destRect.h = (_texture->getH() / _texture->getNumFils()) * _transform->getScale().getY();
		destRect.x = _transform->getPosition().getX() - _transform->getAnchor().getX() * destRect.w - c->getCameraPosition().getX();
		destRect.y = _transform->getPosition().getY() - _transform->getAnchor().getY() * destRect.h - c->getCameraPosition().getY();

		SDL_Point anchor = { _transform->getAnchor().getX() * destRect.w, _transform->getAnchor().getY() * destRect.h };

		_texture->renderFrame(destRect, _currentAnim, _frame, _transform->getRotation(), anchor, (_flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE));
	}
}

void AnimatedSpriteComponent::update()
{
	// we update the frame every _freq ms
	if (SDL_GetTicks() - _lastTimeUpdated >= _freq)
	{
		if (_animations[_currentAnim].loop)
		{
			_frame = (_frame + 1) % _animations[_currentAnim].numFrames;
		}
		else if (!_animations[_currentAnim].animationFinished)
		{
			_frame++;

			if (_frame == _animations[_currentAnim].numFrames)
			{
				//cout << "animation finished!" << endl;
				_animations[_currentAnim].animationFinished = true;
				_frame = _animations[_currentAnim].numFrames - 1;
			}
		}


		_lastTimeUpdated = SDL_GetTicks();//time;
	}
}

void AnimatedSpriteComponent::playAnim(uint name)
{
	_animations[_currentAnim].animationFinished = false;

	if (_currentAnim != name)
	{
		_currentAnim = name;
		_frame = 0;
		//cout << "animation changed to: " << _currentAnim << endl << endl;
	}
}

void AnimatedSpriteComponent::addAnim(uint name, uint numFrames, bool loop)
{
	_animations.push_back({ name, numFrames, loop, false });
}

