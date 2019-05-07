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
		Enemy* enemy = (*it);
		if (!enemy->isDead())
		{
			checkEnemyState(enemy);
			PanelUI::render();
		}		
	}
}

void EnemyLifePanel::checkEnemyState(Enemy* enemy) const
{
	Vector2D position = enemy->getPositionOnCamera();
	auto texture = enemy->getComponent<Texture>();
	auto transform = enemy->getComponent<TransformComponent>();

	int worldWidth = (texture->getW() / texture->getNumCols()) * transform->getScale().getX();
	int winWidth = worldWidth * CAMERA_RESOLUTION_X / _game->getCurrentState()->getMainCamera()->getCameraSize().getX();

	_frame->setPosition((position.getX() - _frame->getW() / 2 + winWidth / 2), position.getY() - _frame->getH() - 10);

	int xPos = _frame->getX() + _frame->getW() / 2 - _lifeBar->getImage()->getW() / 2;
	int yPos = _frame->getY() + _frame->getH() / 2 - _lifeBar->getImage()->getH() / 2;

	_lifeBar->updateLifeBar(enemy->getLife().getLife(), enemy->getLife().getMaxLife());
	_lifeBar->setPosition(xPos, yPos);
}
