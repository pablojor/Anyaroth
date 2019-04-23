#include "AidKit.h"

AidKit::AidKit(Game * game, Vector2D pos, int value) : Collectable(game, game->getTexture("AidKit"), pos, value, "AidKit")
{
	auto anim = addComponent<AnimatedSpriteComponent>();
	anim->addAnim(AnimatedSpriteComponent::Main, 6, true);
	anim->playAnim(AnimatedSpriteComponent::Main);
}