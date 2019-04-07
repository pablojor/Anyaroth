#pragma once
#include "PanelUI.h"
#include "ButtonUI.h"
#include "ImageUI.h"
#include "TextUI.h"

class ShopInfoPanel : public PanelUI
{
	private:
		int margin = 8;

		ImageUI * _frame = nullptr;

		TextUI* _nameText = nullptr;

		ImageUI* _damageIcon = nullptr;
		ImageUI* _damageBar = nullptr;

		ImageUI* _ammoIcon = nullptr;
		ImageUI* _ammoBar = nullptr;

		ImageUI* _cadenceIcon = nullptr;
		ImageUI* _cadenceBar = nullptr;

		ImageUI* _priceIcon = nullptr;
		TextUI* _priceText = nullptr;

		int maxDamage = 50,
			minDamage = 1,
			maxAmmo = 2000,
			minAmmo = 10,
			maxCadence = 1000,
			minCadence = 100;

	public:
		ShopInfoPanel(Game* game, int xPos, int yPos);

		inline int getInfoPanelWidth() const { return _frame->getW(); }
		inline int getInfoPanelHeight() const { return _frame->getH(); }

		void setName(string name);
		void setDamage(int damage);
		void setDistance(int distance);
		void setCadence(int cadence);
		void setPrice(int price);
};

