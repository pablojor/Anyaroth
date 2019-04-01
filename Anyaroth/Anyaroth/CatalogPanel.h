#pragma once
#include "PanelUI.h"
#include "ImageUI.h"
#include "ShopItem.h"
#include "ButtonUI.h"
#include "ShopInfoPanel.h"
#include "CoinsCounter.h"

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

		list<ShopItem*> _items;

		ShopItem* _selectedItem = nullptr;
		ImageUI* _itemIndicator = nullptr;
		CoinsCounter* _playerMoney = nullptr;

		int itemsPerRow = 2;
		int itemsPerCol = 4; 
		int itemWidth;
		int itemHeight;
		int itemSize;

		bool _weaponSold = false;

		void reorderCatalog();

	public:
		CatalogPanel(Game* game);
		~CatalogPanel();

		void setPlayer(Player* ply);

		void setItems(list<ShopItem*>& list);
		void openCatalog();
		void updateCatalog(int zona);

		bool getWeaponSold() { return _weaponSold; }

		void selectItem(Game* game, ShopItem* item);
		void buyItem(Game* game);
};

