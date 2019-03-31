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
		ButtonUI* _exitButton = nullptr;

		static ButtonUI* _buyButton;
		static ShopInfoPanel* _infoPanel;

		//Estos items serán los que se muestren en la tienda
		list<ShopItem*> _items;

		ShopItem* _selectedItem = nullptr;
		ImageUI* _itemIndicator = nullptr;

		int itemsPerRow = 2;
		int itemsPerCol = 4; 
		int itemWidth;
		int itemHeight;
		int itemSize;

	public:
		CatalogPanel(Game* game);
		~CatalogPanel();

		void setItems(list<ShopItem*>& list);
		void openCatalog();
		void updateCatalog(int zona);

		static void selectItem(Game* game);
		static void buyItem(Game* game);
};

