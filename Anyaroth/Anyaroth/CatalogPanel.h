#pragma once
#include "PanelUI.h"
#include "ImageUI.h"
#include "ShopItem.h"
#include "ButtonUI.h"
#include "ShopInfoPanel.h"

#include <list>

class Player;

class CatalogPanel : public PanelUI
{
	private:
		static Player* _player;
		static ButtonUI* _buyButton;
		static ShopInfoPanel* _infoPanel;

		ImageUI* _frame = nullptr;
		ButtonUI* _exitButton = nullptr;

		//Estos items serán los que se muestren en la tienda
		list<ShopItem*> _items;

		ShopItem* _selectedItem = nullptr;
		ImageUI* _itemIndicator = nullptr;

		int itemsPerRow = 2;
		int itemsPerCol = 4; 
		int itemWidth;
		int itemHeight;
		int itemSize;

		void reorderCatalog();

	public:
		CatalogPanel(Game* game);
		~CatalogPanel();

		void setPlayer(Player* ply) { _player = ply; }

		void setItems(list<ShopItem*>& list);
		void openCatalog();
		void updateCatalog(int zona);

		void selectItem(Game* game, ShopItem* item);
		void buyItem(Game* game);
};

