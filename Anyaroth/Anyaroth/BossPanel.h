#pragma once
#include "PanelUI.h"
#include "LifeBar.h"
#include "TextUI.h"

class BossPanel : public PanelUI
{
private:
	ImageUI* _frame = nullptr;
	LifeBar* _lifeBar1 = nullptr;
	LifeBar* _lifeBar2 = nullptr;
	LifeBar* _lifeBar3 = nullptr;
	TextUI* _bossName = nullptr;

public:
	BossPanel(Game* game);
	~BossPanel() {}

	void updateLifeBar(int life1, int life2, int life3, int maxLife);
	void updateBossName(const string& name);
};