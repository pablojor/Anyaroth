#pragma once
#include "PanelUI.h"
#include "ButtonUI.h"
#include "AnimatedImageUI.h"
#include "ImageUI.h"
#include "TextUI.h"

class ShopInfoPanel : public PanelUI
{
	private:
		int margin = 8;

		AnimatedImageUI * _frame = nullptr;

		TextUI* _nameText = nullptr;

		ImageUI* _damageIcon = nullptr;
		ImageUI* _damageBar = nullptr;

		ImageUI* _clipIcon = nullptr;
		ImageUI* _clipBar = nullptr;

		ImageUI* _cadenceIcon = nullptr;
		ImageUI* _cadenceBar = nullptr;

		ImageUI* _priceIcon = nullptr;
		TextUI* _priceText = nullptr;

		int maxDamage = 6,
			maxClip = 6, //Cambiar
			maxCadence = 6;

	public:
		ShopInfoPanel(Game* game, int xPos, int yPos);

		virtual void update(double deltaTime);

		void openInfoPanel();
		void closeInfoPanel();
		void setChildrenVisibility(bool b);

		inline int getInfoPanelWidth() const { return 93; }
		inline int getInfoPanelHeight() const { return 102; }

		void setName(string name);
		void setDamage(int damage);
		void setClip(int clip);
		void setCadence(int cadence);
		void setPrice(int price);
};

