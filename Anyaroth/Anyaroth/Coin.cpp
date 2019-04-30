#include "Coin.h"
#include "AnimatedSpriteComponent.h"

Coin::Coin(Game* game, Vector2D pos, int value) : Collectable(game, game->getTexture("Coin"), pos, value, "Coin")
{
	auto anim = addComponent<AnimatedSpriteComponent>();
	anim->addAnim(AnimatedSpriteComponent::Main, 6, true);
	anim->playAnim(AnimatedSpriteComponent::Main);
}