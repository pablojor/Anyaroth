#include "AnimatedSpriteComponent.h"



AnimatedSpriteComponent::AnimatedSpriteComponent(TransformComponent* trans, Texture* _texture) : SpriteComponent(trans, _texture)
{

}


AnimatedSpriteComponent::~AnimatedSpriteComponent()
{

}

void AnimatedSpriteComponent::render() const
{
	SDL_Rect destRect;
	destRect.w = _texture->getFW() * _transform->getScale().getX();
	destRect.h = _texture->getFH() * _transform->getScale().getY();
	destRect.x = _transform->getPosition().getX() - _transform->getAnchor().getX() * destRect.w;
	destRect.y = _transform->getPosition().getY() - _transform->getAnchor().getY() * destRect.h;

	SDL_Point anchor = { _transform->getAnchor().getX() * destRect.w, _transform->getAnchor().getY() * destRect.h };

	_texture->renderFrame(destRect, distance(begin(animations), animations.find(currentAnim)), frame, _transform->getRotation(), anchor, (_flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE));
}

void AnimatedSpriteComponent::updateFrame() {
	// we update the frame every _freq ms
	if (SDL_GetTicks() - _lastTimeUpdated >= _freq) {
		frame = (frame + 1) % animations[currentAnim];
		_lastTimeUpdated = SDL_GetTicks();//time;
	}
}


void AnimatedSpriteComponent::addAnim(string name, int numFrames) 
{
	animations[name] = (uint)numFrames;
}

void AnimatedSpriteComponent::playAnim(string name) 
{
	currentAnim = name;
}