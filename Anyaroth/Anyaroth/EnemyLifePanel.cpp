#include "EnemyLifePanel.h"
#include "Game.h"
#include "Enemy.h"

EnemyLifePanel::EnemyLifePanel(Game* game) : PanelUI(game)
{
	_frame = new ImageUI(game, game->getTexture("HeadLifeBar"));	
	_lifeBar = new LifeBar(game, "HeadLifeBarMask");

	addChild(_frame);
	addChild(_lifeBar);

	setVisible(false);
	_lifeBar->setInUse(true);
}


EnemyLifePanel::~EnemyLifePanel()
{
}

void EnemyLifePanel::updateLifeBar(int life,  int maxLife)
{
	_lifeBar->updateLifeBar(life, maxLife);
}

void EnemyLifePanel::render() const
{
	for (auto it = _enemies.begin(); it != _enemies.end(); it++)
	{
		if (!(*it)->isDead())
		{
			Vector2D position = (*it)->getPositionOnCamera();

			_frame->setPosition((position.getX() - _frame->getW() / 2 + 9), position.getY() - _frame->getH() - 10);

			int maskPosX = _frame->getX() + _frame->getW() / 2 - _lifeBar->getImage()->getW() / 2;
			int maskPosY = _frame->getY() + _frame->getH() / 2 - _lifeBar->getImage()->getH() / 2;

			_lifeBar->updateLifeBar((*it)->getLife().getLife(), (*it)->getLife().getMaxLife());
			_lifeBar->setPosition(maskPosX, maskPosY);

			PanelUI::render();
		}		
	}
}
