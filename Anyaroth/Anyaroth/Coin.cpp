#include "Coin.h"
#include "AnimatedSpriteComponent.h"

Coin::Coin(Game* g, Texture* texture, Vector2D iniPos, int value) : Collectable(g, texture, iniPos, value, "Coin")
{
	auto anim = addComponent<AnimatedSpriteComponent>();
	anim->addAnim(AnimatedSpriteComponent::Coin::Main, 6, true);
	anim->playAnim(AnimatedSpriteComponent::Coin::Main);
}