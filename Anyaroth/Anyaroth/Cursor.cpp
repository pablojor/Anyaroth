#include "Cursor.h"
#include "Texture.h"
#include "TransformComponent.h"
#include "AnimatedSpriteComponent.h"
#include "PlayState.h"
#include "Camera.h"

Cursor::Cursor(Game* game) : GameComponent(game)
{
	addComponent<Texture>(game->getTexture("GunCursor"));

	_transform = addComponent<TransformComponent>();
	_transform->setAnchor(0.5);

	_anim = addComponent<AnimatedSpriteComponent>();
	_anim->addAnim(AnimatedSpriteComponent::Idle, 1, false);

	_anim->playAnim(AnimatedSpriteComponent::Idle);
}

void Cursor::update(double time)
{
	GameComponent::update(time);

	Vector2D mousePos = getGame()->getCurrentState()->getMousePositionInWorld();
	_transform->setPosition(mousePos);
}