#pragma once
#include "PanelUI.h"
#include "ImageUI.h"
#include "TextUI.h"

class ShopItem : public PanelUI
{
private:
	ImageUI* _gunImage = nullptr;
	TextUI* _gunInfo = nullptr;

public:
	ShopItem(Game* game);
	~ShopItem();

	void changeItemImage();
	void changeItemInfo();
};

