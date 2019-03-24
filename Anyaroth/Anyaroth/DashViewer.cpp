#include "DashViewer.h"
#include "Game.h"

DashViewer::DashViewer(Game * game, int xPos, int yPos) : AnimatedImageUI(game, game->getTexture("DashIcon"), xPos, yPos) {}

void DashViewer::createAnims(const uint& lapse)
{
	addAnim(DashAnimations::Icon, 1);
	addAnim(DashAnimations::Cooldown, 81, false, lapse);

	playAnim(DashAnimations::Icon);
}

void DashViewer::startAnimCD()
{
	playAnim(DashAnimations::Cooldown);
}

void DashViewer::update(double time)
{
	AnimatedImageUI::update(time);

	if (_animations[_currentAnim].name = DashAnimations::Cooldown && _animations[_currentAnim].animationFinished)
		playAnim(DashAnimations::Icon);
}
