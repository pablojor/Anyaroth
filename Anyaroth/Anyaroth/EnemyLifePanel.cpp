#include "EnemyLifePanel.h"
#include "Game.h"


EnemyLifePanel::EnemyLifePanel(Game* game,Enemy* enemy) : PanelUI(game),_enemy(enemy)
{
	_frame = new ImageUI(game, game->getTexture("HeadLifeBar"));
	_frame->setPosition((enemy->getComponent<TransformComponent>()->getPosition().getX() - _frame->getW()*2), enemy->getComponent<TransformComponent>()->getPosition().getY() - _frame->getH() - 10);
	
	cout << _frame->getX() << " " << enemy->getComponent<TransformComponent>()->getPosition().getX() << endl;
	_lifeBar = new LifeBar(game, "HeadLifeBarMask");

	int maskPosY = _frame->getY() + _frame->getH() / 2 - _lifeBar->getH() / 2;
	int maskPosX = _frame->getX() + _frame->getW() / 2 - _lifeBar->getW() / 2;

	_lifeBar->setPosition(maskPosX, maskPosY);

	addChild(_frame);
	addChild(_lifeBar);

	setVisible(false);
	_lifeBar->setInUse(true);
}


EnemyLifePanel::~EnemyLifePanel()
{
}

void EnemyLifePanel::updateLifeBar( int life,  int maxLife)
{

	_lifeBar->updateLifeBar(life, maxLife);
}
