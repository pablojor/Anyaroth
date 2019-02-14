#include "AnimatedSpriteComponent.h"
#include "GameComponent.h"


AnimatedSpriteComponent::AnimatedSpriteComponent(GameComponent* obj) : SpriteComponent(obj), PhysicsComponent(obj), RenderComponent(obj), Component()
{

}


AnimatedSpriteComponent::~AnimatedSpriteComponent()
{

}

void AnimatedSpriteComponent::render() const
{
	SDL_Rect destRect;
	destRect.w = (_texture->getW() / _texture->getNumCols()) * _transform->getScale().getX();
	destRect.h = (_texture->getH() / _texture->getNumFils()) * _transform->getScale().getY();
	destRect.x = _transform->getPosition().getX() - _transform->getAnchor().getX() * destRect.w;
	destRect.y = _transform->getPosition().getY() - _transform->getAnchor().getY() * destRect.h;

	SDL_Point anchor = { _transform->getAnchor().getX() * destRect.w, _transform->getAnchor().getY() * destRect.h };

	_texture->renderFrame(destRect, distance(begin(_animations), _animations.find(_currentAnim)), _frame, _transform->getRotation(), anchor, (_flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE));
}

void AnimatedSpriteComponent::update() 
{
	// we update the frame every _freq ms
	if (SDL_GetTicks() - _lastTimeUpdated >= _freq) 
	{
		_frame = (_frame + 1) % _animations[_currentAnim];
		_lastTimeUpdated = SDL_GetTicks();//time;
	}
}


void AnimatedSpriteComponent::addAnim(string name, int numFrames)
{
	_animations[name] = (uint)numFrames;
}

void AnimatedSpriteComponent::playAnim(string name)
{
	_currentAnim = name;
}