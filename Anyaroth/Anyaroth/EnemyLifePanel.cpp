#include "EnemyLifePanel.h"
#include "Game.h"


EnemyLifePanel::EnemyLifePanel(Game* game,Enemy* enemy) : PanelUI(game),_enemy(enemy)
{
	//auto camera = _game->getCurrentState()->getMainCamera();
	_frame = new ImageUI(game, game->getTexture("HeadLifeBar"));
	auto pos = enemy->getPositionOnScreen();
	_frame->setPosition((enemy->getPositionOnScreen().getX() - _frame->getW() / 2), enemy->getPositionOnScreen().getY() - _frame->getH() - 10);
	
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

void EnemyLifePanel::render() const
{
	PanelUI::render();
}
