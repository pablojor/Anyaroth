#pragma once
#include "PanelUI.h"
#include "LifeBar.h"
#include "TextUI.h"

class BossPanel : public PanelUI
{
private:
	LifeBar* _lifeBar = nullptr;
	TextUI* _bossName = nullptr;

public:
	BossPanel(Game* game);
	~BossPanel() {}

	inline void updateLifeBar(const int& life, const int& maxLife) { _lifeBar->updateLifeBar(life, maxLife); }
	inline void updateBossName(const string& name) { _bossName->setText(name); }
};