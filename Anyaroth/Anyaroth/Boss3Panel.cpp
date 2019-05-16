#include "Boss3Panel.h"
#include "Game.h"


Boss3Panel::Boss3Panel(Game* game) : PanelUI(game)
{
	_frame = new ImageUI(game, game->getTexture("Boss3LifeBar"));
	_frame->setPosition(CAMERA_RESOLUTION_X / 2 - _frame->getW() / 2, CAMERA_RESOLUTION_Y - _frame->getH() - 10);

	_lifeBar = new LifeBar(game, "Boss3LifeBarMask");
	_lifeBar->setInUse(true);

	int maskPosY = _frame->getY() + _frame->getH() / 2;
	int maskPosX = _frame->getX() + _frame->getW() / 2 - _lifeBar->getW() / 2;

	_lifeBar->setPosition(maskPosX, maskPosY);


	_bossName = new TextUI(game, " ", game->getFont("ARIAL12"), 12, 0, 0, { 255, 255, 255, 255 });
	_bossName->setPosition(CAMERA_RESOLUTION_X / 2 - _bossName->getW() / 2, _lifeBar->getY() - _bossName->getH() - 3);

	addChild(_frame);
	addChild(_lifeBar);
	addChild(_bossName);

	setVisible(false);
}

void Boss3Panel::updateLifeBar(int life, int maxLife)
{
	if (life > 0)
		_lifeBar->updateLifeBar(life, maxLife);
	else
		_lifeBar->setVisible(false);
}

void Boss3Panel::resetLifeBar(int life, int maxLife)
{
	_lifeBar->setVisible(true);

	_lifeBar->updateLifeBar(life, maxLife);
}

void Boss3Panel::updateBossName(const string& name)
{
	_bossName->setText(name);
	_bossName->setPosition(CAMERA_RESOLUTION_X / 2 - _bossName->getW() / 2, _lifeBar->getY() - _bossName->getH() - 3);
}