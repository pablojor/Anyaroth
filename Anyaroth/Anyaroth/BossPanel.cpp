#include "BossPanel.h"
#include "Game.h"

BossPanel::BossPanel(Game * game) : PanelUI(game)
{
	_marco = new ImageUI(game, game->getTexture("BossLifeBar"));
	_marco->setPosition(CAMERA_RESOLUTION_X / 2 - _marco->getW() / 2, CAMERA_RESOLUTION_Y - _marco->getH() - 10);

	_lifeBar_1 = new LifeBar(game, "BossLifeBarMask1");
	_lifeBar_2 = new LifeBar(game, "BossLifeBarMask2");
	_lifeBar_3 = new LifeBar(game, "BossLifeBarMask3");

	int maskPosY = _marco->getY() + _marco->getH() / 2;
	_lifeBar_1->setPosition(CAMERA_RESOLUTION_X / 2 + _lifeBar_1->getW() / 2 + 6, maskPosY);
	_lifeBar_2->setPosition(CAMERA_RESOLUTION_X / 2 - _lifeBar_2->getW() / 2, maskPosY);
	_lifeBar_3->setPosition(CAMERA_RESOLUTION_X / 2 - _lifeBar_3->getW() / 2 - 79, maskPosY);

	_bossName = new TextUI(game, " ", game->getFont("ARIAL12"), 12, 0, 0, { 255, 255, 255, 255 });
	_bossName->setPosition(CAMERA_RESOLUTION_X / 2 - _bossName->getW() / 2, _lifeBar_1->getY() - _bossName->getH() - 3);

	addChild(_marco);
	addChild(_lifeBar_1);
	addChild(_lifeBar_2);
	addChild(_lifeBar_3);
	addChild(_bossName);
}

void BossPanel::updateLifeBar(const int& life1, const int& life2, const int& life3, const int& maxLife)
{
	if (life1 > 0)
	{
		if (!_lifeBar_1->getInUse())
		{
			_lifeBar_1->setInUse(true);

			_lifeBar_2->setInUse(true);
			_lifeBar_2->updateLifeBar(life2, maxLife);
			_lifeBar_2->setInUse(false);

			_lifeBar_3->setInUse(true);
			_lifeBar_3->updateLifeBar(life3, maxLife);
			_lifeBar_3->setInUse(false);
		}

		_lifeBar_1->updateLifeBar(life1, maxLife);
	}
	else if (life2 > 0)
	{
		if (!_lifeBar_2->getInUse())
		{
			_lifeBar_1->setInUse(true);
			_lifeBar_1->updateLifeBar(life1, maxLife);
			_lifeBar_1->setInUse(false);

			_lifeBar_2->setInUse(true);

			_lifeBar_3->setInUse(true);
			_lifeBar_3->updateLifeBar(life3, maxLife);
			_lifeBar_3->setInUse(false);
		}

		_lifeBar_2->updateLifeBar(life2, maxLife);
	}
	else
	{
		if (!_lifeBar_3->getInUse())
		{
			_lifeBar_2->setInUse(true);
			_lifeBar_2->updateLifeBar(life2, maxLife);
			_lifeBar_2->setInUse(false);

			_lifeBar_3->setInUse(true);
		}

		_lifeBar_3->updateLifeBar(life3, maxLife);
	}
}

void BossPanel::updateBossName(const string& name) 
{ 
	_bossName->setText(name); 
	_bossName->setPosition(CAMERA_RESOLUTION_X / 2 - _bossName->getW() / 2, _lifeBar_1->getY() - _bossName->getH() - 3);
}
