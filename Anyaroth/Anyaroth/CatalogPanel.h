#pragma once
#include "PanelUI.h"
#include "ImageUI.h"
#include "ShopItem.h"
#include "ButtonUI.h"
#include "ShopInfoPanel.h"

#include <list>

class CatalogPanel : public PanelUI
{
	private:
		ImageUI* _frame = nullptr;
		ShopInfoPanel* _infoPanel = nullptr;
		ButtonUI* _exitButton = nullptr;

		//Estos items serán los que se muestren en la tienda
		list<ShopItem*> _items;

		ShopItem* _selectedItem = nullptr;
		ImageUI* _itemIndicator = nullptr;

	public:
		CatalogPanel(Game* game);
};

