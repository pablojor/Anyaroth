#include "BossPanel.h"
#include "Game.h"

BossPanel::BossPanel(Game * game) : PanelUI(game)
{
	_frame = new ImageUI(game, game->getTexture("BossLifeBar"));
	_frame->setPosition(CAMERA_RESOLUTION_X / 2 - _frame->getW() / 2, CAMERA_RESOLUTION_Y - _frame->getH() - 10);

	_lifeBar1 = new LifeBar(game, "BossLifeBarMask1");
	_lifeBar2 = new LifeBar(game, "BossLifeBarMask2");
	_lifeBar3 = new LifeBar(game, "BossLifeBarMask3");

	int maskPosY = _frame->getY() + _frame->getH() / 2;
	_lifeBar1->setPosition(CAMERA_RESOLUTION_X / 2 + _lifeBar1->getW() / 2 + 6, maskPosY);
	_lifeBar2->setPosition(CAMERA_RESOLUTION_X / 2 - _lifeBar2->getW() / 2, maskPosY);
	_lifeBar3->setPosition(CAMERA_RESOLUTION_X / 2 - _lifeBar3->getW() / 2 - 79, maskPosY);

	_bossName = new TextUI(game, " ", game->getFont("ARIAL12"), 12, 0, 0, { 255, 255, 255, 255 });
	_bossName->setPosition(CAMERA_RESOLUTION_X / 2 - _bossName->getW() / 2, _lifeBar1->getY() - _bossName->getH() - 3);

	addChild(_frame);
	addChild(_lifeBar1);
	addChild(_lifeBar2);
	addChild(_lifeBar3);
	addChild(_bossName);

	setVisible(false);
}

void BossPanel::updateLifeBar(int life1, int life2, int life3, int maxLife)
{
	if (life1 > 0)
	{
		if (!_lifeBar1->getInUse())
		{
			_lifeBar1->setInUse(true);

			_lifeBar2->setInUse(true);
			_lifeBar2->updateLifeBar(life2, maxLife);
			_lifeBar2->setInUse(false);

			_lifeBar3->setInUse(true);
			_lifeBar3->updateLifeBar(life3, maxLife);
			_lifeBar3->setInUse(false);
		}

		_lifeBar1->updateLifeBar(life1, maxLife);
	}
	else if (life2 > 0)
	{
		if (!_lifeBar2->getInUse())
		{
			_lifeBar1->setInUse(true);
			_lifeBar1->updateLifeBar(life1, maxLife);
			_lifeBar1->setInUse(false);

			_lifeBar2->setInUse(true);

			_lifeBar3->setInUse(true);
			_lifeBar3->updateLifeBar(life3, maxLife);
			_lifeBar3->setInUse(false);
		}

		_lifeBar2->updateLifeBar(life2, maxLife);
	}
	else
	{
		if (!_lifeBar3->getInUse())
		{
			_lifeBar2->setInUse(true);
			_lifeBar2->updateLifeBar(life2, maxLife);
			_lifeBar2->setInUse(false);

			_lifeBar3->setInUse(true);
		}

		_lifeBar3->updateLifeBar(life3, maxLife);
	}
}

void BossPanel::updateBossName(const string& name) 
{ 
	_bossName->setText(name); 
	_bossName->setPosition(CAMERA_RESOLUTION_X / 2 - _bossName->getW() / 2, _lifeBar1->getY() - _bossName->getH() - 3);
}