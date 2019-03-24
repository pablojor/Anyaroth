#pragma once
#include "PanelUI.h"
#include "LifeBar.h"
#include "TextUI.h"

class BossPanel : public PanelUI
{
	private:
		ImageUI* _marco = nullptr;
		LifeBar* _lifeBar_1 = nullptr;
		LifeBar* _lifeBar_2 = nullptr;
		LifeBar* _lifeBar_3 = nullptr;
		TextUI* _bossName = nullptr;

	public:
		BossPanel(Game* game, string bossName);
		~BossPanel() {}

		void updateLifeBar(const int& life1, const int& life2, const int& life3, const int& maxLife);

		inline void updateBossName(const string& name) { _bossName->setText(name); }
};