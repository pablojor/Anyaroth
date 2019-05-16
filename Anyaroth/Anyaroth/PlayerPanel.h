#pragma once
#include "PanelUI.h"
#include "LifeBar.h"
#include "TextUI.h"
#include "CoinsCounter.h"
#include "AmmoViewer.h"
#include "WeaponryViewer.h"
#include "DashViewer.h"

class PlayerPanel : public PanelUI
{
	private:
		ImageUI* _lifeFrame = nullptr;
		TextUI* _deathText = nullptr;
		TextUI* _lifeText = nullptr;
		LifeBar* _lifeBar = nullptr;
		AmmoViewer* _ammoViewer = nullptr;
		CoinsCounter* _coinsCounter = nullptr;
		WeaponryViewer* _weaponryViewer = nullptr;
		DashViewer* _dashViewer = nullptr;

	public:
		PlayerPanel() {};
		PlayerPanel(Game* game);
		~PlayerPanel() {}

		void updateLifeBar(int life, int maxLife);
		inline void updateAmmoViewer(int clip, int magazine) { _ammoViewer->updateAmmoViewer(clip, magazine); }
		inline void updateCoinsCounter(int cant) { _coinsCounter->updateCoinsCounter(cant); }
		inline void updateWeaponryViewer(Texture* iconTex) { _weaponryViewer->updateWeaponryViewer(iconTex); }
		inline void updateDashViewer(const uint& n) { _dashViewer->createAnims(n); }

		inline void startAnimDashCD() { _dashViewer->startAnimCD(); }
		inline void resetDashViewer() { _dashViewer->reset(); }

		inline void showDeathText(bool show) { _deathText->setVisible(show); }
};