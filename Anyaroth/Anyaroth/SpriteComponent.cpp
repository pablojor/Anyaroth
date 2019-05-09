#include "SpriteComponent.h"
#include "GameObject.h"
#include "Camera.h"
#include "Game.h"

SpriteComponent::SpriteComponent(GameObject* obj) : RenderComponent(obj)
{
	_texture = obj->getComponent<Texture>();
	_transform = obj->getComponent<TransformComponent>();
}

void SpriteComponent::render(Camera* c) const
{
	if (_renderActive)
	{
		SDL_Rect destRect;
		destRect.w = _texture->getW() * _transform->getScale().getX();
		destRect.h = _texture->getH() * _transform->getScale().getY();
		destRect.x = _transform->getPosition().getX() - _transform->getAnchor().getX() * destRect.w - c->getCameraPosition().getX();
		destRect.y = _transform->getPosition().getY() - _transform->getAnchor().getY() * destRect.h - c->getCameraPosition().getY();

		SDL_Rect winRect = { destRect.x * GAME_RESOLUTION_X / c->getCameraSize().getX(), destRect.y * GAME_RESOLUTION_Y / c->getCameraSize().getY(),
							destRect.w * GAME_RESOLUTION_X / c->getCameraSize().getX() + 1, destRect.h * GAME_RESOLUTION_Y / c->getCameraSize().getY() + 1 }; //+1 para el tema del Zoom

		SDL_Point anchor = { _transform->getAnchor().getX() * winRect.w, _transform->getAnchor().getY() * winRect.h };

		_texture->render(winRect, _transform->getRotation(), anchor, (_flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE));
	}
}

void SpriteComponent::flip() 
{
	_flip = true;
}

void SpriteComponent::unFlip() 
{
	_flip = false;
}