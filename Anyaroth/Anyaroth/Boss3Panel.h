#pragma once
#include "PanelUI.h"
#include "LifeBar.h"
#include "TextUI.h"

class Boss3Panel : public PanelUI
{
	private:
		ImageUI* _frame = nullptr;
		LifeBar* _lifeBar = nullptr;
		TextUI* _bossName = nullptr;

	public:
		Boss3Panel(Game* game);
		~Boss3Panel() {}

		void updateLifeBar(const int& life, const int& maxLife);
		void resetLifeBar(const int& life, const int& maxLife);
		void updateBossName(const string& name);
};

