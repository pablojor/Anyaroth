#pragma once
#include "PanelUI.h"
#include "ButtonUI.h"
#include "ImageUI.h"
#include "TextUI.h"

class ShopInfoPanel : public PanelUI
{
private:
	ImageUI * _backImage = nullptr;

	TextUI* _nameText = nullptr;

	ImageUI* _damageImage = nullptr;
	TextUI* _damageText = nullptr;

	ImageUI* _distanceImage = nullptr;
	TextUI* _distanceText = nullptr;

	ImageUI* _cadenceImage = nullptr;
	TextUI* _cadenceText = nullptr;

	ImageUI* _priceImage = nullptr;
	TextUI* _priceText = nullptr;

	ButtonUI * _buyButton = nullptr;

public:
	ShopInfoPanel(Game* game, int xPos, int yPos);
	~ShopInfoPanel();
};

