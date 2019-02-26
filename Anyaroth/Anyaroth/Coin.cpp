#include "Coin.h"
#include "AnimatedSpriteComponent.h"

Coin::Coin(PlayState* play, Game* g, Texture* texture, Vector2D iniPos, int value) : Collectable(play, g, texture, iniPos, value, "Moneda")
{
	auto anim = addComponent<AnimatedSpriteComponent>();
	anim->addAnim(AnimatedSpriteComponent::Coin::Main, 6, true);
	anim->playAnim(AnimatedSpriteComponent::Coin::Main);

}