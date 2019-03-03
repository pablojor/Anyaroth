#pragma once
#include "PanelUI.h"
#include "LifeBar.h"
#include "TextUI.h"
#include "CoinsCounter.h"
#include "AmmoViewer.h"
#include "WeaponryViewer.h"
#include "DashViewer.h"

class PlayerPanel :	public PanelUI
{
	private:
		LifeBar* _lifeBar;
		AmmoViewer* _ammoViewer;
		CoinsCounter* _coinsCounter;
		WeaponryViewer* _weaponryViewer;
		DashViewer* _dashViewer;

		////Temporal
		//int MAX_LIFE = 500;
		//int LIFE = 500;

	public:
		PlayerPanel() {};
		PlayerPanel(Game* game);
		~PlayerPanel();

		inline void updateLifeBar(const int& life, const int& maxLife) { _lifeBar->updateLifeBar(life, maxLife); }
		inline void updateAmmoViewer(const int& clip, const int& magazine) { _ammoViewer->updateAmmoViewer(clip, magazine); }
		inline void updateCoinsCounter(const int& cant) { _coinsCounter->updateCoinsCounter(cant); }
		inline void updateWeaponryViewer() { _weaponryViewer->updateWeaponryViewer(); }
		inline void updateDashViewer(const uint& cant) { _dashViewer->setDashes(cant); }

		/*void update()
		{
			LIFE -= 3; if (LIFE < 0) LIFE = 0;
			MAX_LIFE--; if (MAX_LIFE < 0) MAX_LIFE = 0;

			updateLifeBar(LIFE, MAX_LIFE);
			updateAmmoViewer(LIFE, MAX_LIFE);
			updateCoinsCounter(LIFE + MAX_LIFE);
			if (MAX_LIFE == 450 || MAX_LIFE == 375 || MAX_LIFE == 250) updateWeaponryViewer();
			if (MAX_LIFE % 100 == 0) updateDashViewer(MAX_LIFE / 100);

		}*/
};

