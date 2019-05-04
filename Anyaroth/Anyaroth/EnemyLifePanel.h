#pragma once
#include "PanelUI.h"
#include "LifeBar.h"
#include "TextUI.h"
#include "Enemy.h"
class EnemyLifePanel :
	public PanelUI
{
private:
	ImageUI* _frame = nullptr;
	LifeBar* _lifeBar = nullptr;
	Enemy* _enemy = nullptr;
public:
	EnemyLifePanel(Game* game,Enemy* enemy);
	~EnemyLifePanel();
	void updateLifeBar(int life1, int maxLife);
};

