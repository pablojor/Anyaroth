#include "BossPanel.h"
#include "Game.h"

BossPanel::BossPanel(Game * game) : PanelUI(game)
{
	_lifeBar = new LifeBar(game, "LifeBarMask");
	_lifeBar->setInUse(false);
	_bossName = new TextUI(game, "BossName", game->getFont("ARIAL12"), 12, 0, 0, { 255, 255, 255, 255 });

	_lifeBar->setPosition(CAMERA_RESOLUTION_X / 2 - _lifeBar->getW() / 2, CAMERA_RESOLUTION_Y - 80);
	_bossName->setPosition(CAMERA_RESOLUTION_X / 2 - _bossName->getW() / 2, _lifeBar->getY() - _bossName->getH() - 1);

	addChild(_lifeBar);
	addChild(_bossName);
}