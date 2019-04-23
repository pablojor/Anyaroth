#include "AmmoPackage.h"

AmmoPackage::AmmoPackage(Game * game, Vector2D pos, int value) : Collectable(game, game->getTexture("Ammo"), pos, value, "Ammo")
{
	auto anim = addComponent<AnimatedSpriteComponent>();
	anim->addAnim(AnimatedSpriteComponent::Main, 6, true);
	anim->playAnim(AnimatedSpriteComponent::Main);
}